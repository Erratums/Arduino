    
/*
 * PZEM-004T v3.0 Sample
 * Developed by Erratum Solutions
 * Contact us @ support@erratums.com
 * https://erratums.com
 * Date created: 18-Sep-2019
 */

#include "PZEM004Tv30.h"

// Use Software Serial for Arduino Uno
// Pin 11 as Rx and 15 as Tx { Ajmal }
PZEM004Tv30 pzem(11, 12);

void setup() {
  Serial.begin(115200);
}

void loop() {
  printValue(pzem.voltage(), F("Voltage"), F("V"));
  printValue(pzem.current(), F("Current"), F("A"));
  printValue(pzem.power(), F("Power"), F("W"));
  printValue(pzem.energy(), F("Energy"), F("kWh"));
  printValue(pzem.frequency(), F("Frequency"), F("Hz"));
  printValue(pzem.pf(), F("PF"), F(""));
  Serial.println();
  delay(2000);
}

void printValue(const float aValue, const __FlashStringHelper *aCaption, const __FlashStringHelper *aUnit) {
  if(!isnan(aValue)){
    Serial.print(aCaption); 
    Serial.print(F(": "));
    Serial.print(aValue); 
    Serial.println(aUnit);
  } else {
    Serial.print(F("Error Reading "));
    Serial.println(aCaption);
  }
}
