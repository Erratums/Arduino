    
/*
 * Nano-NRF24L01 Remote Car Sample
 * Developed by Erratum Solutions
 * Contact us @ support@erratums.com
 * https://erratums.com
 * Date created: 27-July-2019
 */

#include <SPI.h>
#include <RF24.h>
#include <Servo.h> 
#include <nRF24L01.h>

#define motorLeft1 A1
#define motorLeft2 A0
#define motorRight1 A3
#define motorRight2 A2
#define servoPin 3

RF24 radio(10, 9); // CE, CSN
Servo Servo1;
bool isJoyStick;
int iJoyStickDelayCntr;

const byte address[6] = "00001";
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup() {  
  Serial.begin(9600);
  while (!Serial);

  isJoyStick = false;
  iJoyStickDelayCntr = 0;
  
  radio.begin();
  radio.openReadingPipe(0, pipe);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  Servo1.attach(servoPin); 

  pinMode(motorLeft1, OUTPUT);
  pinMode(motorLeft2, OUTPUT);
  pinMode(motorRight1, OUTPUT);
  pinMode(motorRight2, OUTPUT);
}

void loop() {
  if (radio.available()) {
    char text[32] = "Left";
    radio.read(&text, sizeof(text));

    /*if (strcmp(text, "Left") == 0) Servo1.write(0);
    else if (strcmp(text, "Down") == 0) Servo1.write(90);
    else if (strcmp(text, "Right") == 0) Servo1.write(180);*/

    if (strcmp(text, "Analog Button") == 0) stopMoving();
    else if (strcmp(text, "Up") == 0) moveForward();
    else if (strcmp(text, "Down") == 0) moveBackward();
    else if (strcmp(text, "Left") == 0) turnLeft();
    else if (strcmp(text, "Right") == 0) turnRight();
    else if (strcmp(text, "JSUp") == 0) {
      moveForward();
      isJoyStick = true;
      iJoyStickDelayCntr = 10;
    } else if (strcmp(text, "JSDown") == 0) {
      moveBackward();
      isJoyStick = true;
      iJoyStickDelayCntr = 10;
    } else if (strcmp(text, "JSLeft") == 0) {
      turnLeft();
      isJoyStick = true;
      iJoyStickDelayCntr = 10;
    } else if (strcmp(text, "JSRight") == 0) {
      turnRight();
      isJoyStick = true;
      iJoyStickDelayCntr = 10;
    }

    Serial.println(text);
  } else if (isJoyStick) {
      delay(50);
      if (iJoyStickDelayCntr > 0) {
        iJoyStickDelayCntr--;
      } else {
        stopMoving();
        isJoyStick = false;
      }
  }
}

void stopMoving() {
  digitalWrite(motorLeft1, LOW);
  digitalWrite(motorLeft2, LOW);
  digitalWrite(motorRight1, LOW);
  digitalWrite(motorRight2, LOW);
  Serial.println(F("Stopped"));
}

void moveForward() {
  digitalWrite(motorLeft1, HIGH);
  digitalWrite(motorLeft2, LOW);
  digitalWrite(motorRight1, HIGH);
  digitalWrite(motorRight2, LOW);
  Serial.println(F("Moving Forward"));
}

void moveBackward() {
  digitalWrite(motorLeft1, LOW);
  digitalWrite(motorLeft2, HIGH);
  digitalWrite(motorRight1, LOW);
  digitalWrite(motorRight2, HIGH);
  Serial.println(F("Moving Backward"));
}

void turnRight() {
  digitalWrite(motorLeft1, HIGH);
  digitalWrite(motorLeft2, LOW);
  digitalWrite(motorRight1, LOW);
  digitalWrite(motorRight2, LOW);
  Serial.println(F("Moving Right"));
}

void turnLeft() {
  digitalWrite(motorLeft1, LOW);
  digitalWrite(motorLeft2, LOW);
  digitalWrite(motorRight1, HIGH);
  digitalWrite(motorRight2, LOW);  
  Serial.println(F("Moving Left"));
}
