    
/*
 * NRF24L01 Joystick Sample
 * Developed by Erratum Solutions
 * Contact us @ support@erratums.com
 * https://erratums.com
 * Date created: 27-July-2019
 */

#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>

#define CE_PIN  9
#define CSN_PIN 10

byte up_button     = 2; // Boton A
byte down_button   = 4; // Boton C 
byte left_button   = 5; // Boton D 
byte right_button  = 3; // Boton B
byte start_button  = 6; // Boton F
byte select_button = 7; // Boton E
byte analog_button = 8; // Joystick Press
byte x_axis = A0;
byte y_axis = A1;

byte buttons[] = {
  up_button, 
  down_button, 
  left_button, 
  right_button, 
  start_button, 
  select_button, 
  analog_button
};

const uint64_t pipe = 0xE8E8F0F0E1LL;
RF24 radio(CE_PIN, CSN_PIN);
char msg[20] = "";

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  for(int iCntr; iCntr < 7; iCntr++) {
     pinMode(buttons[iCntr], INPUT);
     digitalWrite(buttons[iCntr], HIGH);  
  } 
  radio.begin();
  radio.openWritingPipe(pipe);
}

bool isButtonPressed(byte aButton, bool aWaitRelease = true) {
  if (digitalRead(aButton) == LOW) {
    if (aWaitRelease) {
      // Wait until button is released { Ajmal }
      while (digitalRead(aButton) == LOW) {
        delay(50);
      }
    }
    return true;
  }
  return false;
}

void loop() {
  if(isButtonPressed(up_button)) {
    char msg[] = "Up";
    radio.write(&msg, sizeof(msg));
    delay(300);
    Serial.println(F("UP Button Pressed"));
  } else if(isButtonPressed(down_button)) {
    char msg[] = "Down";
    radio.write(&msg, sizeof(msg));
    delay(300);
    Serial.println(F("Down Button Pressed"));
  } else if(isButtonPressed(left_button)) {
    char msg[] = "Left";
    radio.write(&msg, sizeof(msg));
    delay(300);
    Serial.println(F("Left Button Pressed"));
  } else if(isButtonPressed(right_button)) {
    char msg[] = "Right";
    radio.write(&msg, sizeof(msg));
    delay(300);
    Serial.println(F("Rigth Button Pressed"));
  } else if(digitalRead(start_button) == LOW) {
    char msg[] = "Start";
    radio.write(&msg, sizeof(msg));
    delay(300);
    Serial.println(F("Start Button Pressed"));
  } else if(isButtonPressed(select_button)) {
    char msg[] = "Select";
    radio.write(&msg, sizeof(msg));
    delay(300);
    Serial.println(F("Select Button Pressed"));
  } else if(isButtonPressed(analog_button)) {
    // char msg[] = "Analog: X = " + String(analogRead(x_axis)) + ", Y = " + String(analogRead(y_axis));
    char msg[] = "Analog Button";
    Serial.println(msg);
    radio.write(&msg, sizeof(msg));
    delay(300);
    Serial.println(F("Analog Button Pressed"));
  } else {
    int jposX = analogRead(x_axis);
    int jposY = analogRead(y_axis);

    if (jposX < 25) {
      char msg[] = "JSLeft";
      radio.write(&msg, sizeof(msg));
      delay(300);
      Serial.println(F("Joystick Left Pressed"));
    } else if (jposY < 25) {
      char msg[] = "JSDown";
      radio.write(&msg, sizeof(msg));
      delay(300);
      Serial.println(F("Joystick Down Pressed"));
    } else if (jposX > 990) {
      char msg[] = "JSRight";
      radio.write(&msg, sizeof(msg));
      delay(300);
      Serial.println(F("Joystick Right Pressed"));
    } else if (jposY > 990) {
      char msg[] = "JSUp";
      radio.write(&msg, sizeof(msg));
      delay(300);
      Serial.println(F("Joystick Up Pressed"));      
    }
  }
  
  // Serial.print("\n X = "),Serial.print(analogRead(x_axis)),Serial.print(" \n Y = "), Serial.print(analogRead(y_axis));
  // Serial.print(F(" "));
  delay(50);
}
