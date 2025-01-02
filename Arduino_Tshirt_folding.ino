#include <Servo.h>

// Maak servo-objecten aan
Servo servoTL; 
Servo servoDL;
Servo servoTR;
Servo servoDR;

// Variabele om de hoek bij te houden
int angleTL = 170; // Startpositie voor linker bovenservo
int angleDL = 10;   // Startpositie voor linker onderservo
int angleTR = 10;   // Startpositie voor rechter bovenservo
int angleDR = 170; // Startpositie voor rechter onderservo

// Maak DC-motor componenten aan
int enable2 = 9;
int in3 = 7;
int in4 = 8;

// Knopconfiguratie
const int buttonPin = 2;  // De pin waarop de knop is aangesloten
int buttonState = 0;      // Variabele voor het lezen van de knopstatus

void setup() {
  // Koppel de servo's aan de respectieve pinnen
  servoTL.attach(5);
  servoDL.attach(3); 
  servoTR.attach(4);
  servoDR.attach(6);

  // Stel motorpinnen in als uitvoer
  pinMode(enable2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Stel de knop in als invoer met ingebouwde pull-up weerstand
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // Lees de status van de knop
  buttonState = digitalRead(buttonPin);

  // Controleer of de knop is ingedrukt (LOW = ingedrukt, vanwege pull-up)
  if (buttonState == LOW) {
    // Snelheid voor heen- en terugbeweging
    int delayForward = 10;   // Snelheid heen (hogere waarde = trager)
    int delayBackward = 5;  // Snelheid terug (lagere waarde = sneller)

    // Eerste cyclus: Beweging linkerflap
    for (angleTL = 170, angleDL = 10; angleTL >= 10; angleTL--, angleDL++) { 
      servoTL.write(angleTL); 
      servoDL.write(angleDL); 
      servoTR.write(10);      
      servoDR.write(170);    
      delay(delayForward);    
    }

    for (angleTL = 10, angleDL = 170; angleTL <= 170; angleTL++, angleDL--) { 
      servoTL.write(angleTL); 
      servoDL.write(angleDL); 
      servoTR.write(10);       
      servoDR.write(170);     
      delay(delayBackward);   
    }

    // Tweede cyclus: Beweging rechterflap
    for (angleTR = 10, angleDR = 170; angleTR <= 170; angleTR++, angleDR--) { 
      servoTR.write(angleTR); 
      servoDR.write(angleDR); 
      servoTL.write(170);     
      servoDL.write(10);       
      delay(delayForward);    
    }

    for (angleTR = 170, angleDR = 10; angleTR >= 10; angleTR--, angleDR++) { 
      servoTR.write(angleTR); 
      servoDR.write(angleDR); 
      servoTL.write(170);     
      servoDL.write(10);       
      delay(delayBackward);   
    }

    // Extra beweging: linkerflap beweegt met pauze
    for (angleTL = 170, angleDL = 10; angleTL >= 10; angleTL--, angleDL++) { 
      servoTL.write(angleTL); 
      servoDL.write(angleDL); 
      servoTR.write(10);       
      servoDR.write(170);     
      delay(delayForward);    
    }

    // Draai de DC-motor terwijl de linkerflap 5 seconden stilstaat
    analogWrite(enable2, 255);   // Start DC-motor op maximale snelheid
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(2000);                 // Pauze van 5 seconden waarin de motor draait
    digitalWrite(in3, LOW);      // Stop DC-motor
    digitalWrite(in4, LOW);

    for (angleTL = 10, angleDL = 170; angleTL <= 170; angleTL++, angleDL--) { 
      servoTL.write(angleTL); 
      servoDL.write(angleDL); 
      servoTR.write(10);       
      servoDR.write(170);     
      delay(delayBackward);   
    }
     analogWrite(enable2, 255);   // Start DC-motor op maximale snelheid
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(6000);                 // Pauze van 5 seconden waarin de motor draait
    digitalWrite(in3, LOW);      // Stop DC-motor
    digitalWrite(in4, LOW);
  }
}



