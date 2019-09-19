    
/*
 * LCD Shield Sample
 * Developed by Erratum Solutions
 * Contact us @ support@erratums.com
 * https://erratums.com
 * Date created: 27-Aug-2019
 */

#include <Wire.h>
#include <LiquidCrystal.h>

// Interfacing pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  // Print a message to the LCD.
  lcd.setCursor(0, 0);
  lcd.print(F("LCD Key Shield"));
  lcd.setCursor(0, 1);
  lcd.print(F("Press Key:"));
}

void loop() {
  int iSwitch;
  iSwitch = analogRead(0);
  lcd.setCursor(10, 1);
  
  if (iSwitch < 60) {
    lcd.print ("Right ");
  } else if (iSwitch < 200) {
    lcd.print(F("Up    "));    
  } else if (iSwitch < 400){
    lcd.print(F("Down  "));    
  } else if (iSwitch < 600){
    lcd.print(F("Left  "));    
  } else if (iSwitch < 800){
    lcd.print(F("Select"));    
  }
}
