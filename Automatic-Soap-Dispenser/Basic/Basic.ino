    
/*
 * Ultrasonic Soap Dispenser Sample
 * Developed by Erratum Solutions
 * Contact us @ support@erratums.com
 * https://erratums.com
 * Date created: 18-April-2020
 */

const byte cPUMP_PIN = 5;
const byte cECHO_PIN = 6; // Echo Pin of Ultrasonic Sensor
const byte cPING_PIN = 7; // Trigger Pin of Ultrasonic Sensor
const byte cBUZZER_PIN = 9; // Connect your buzzer here 

long lFoundObject;
bool bFoundObject;

void setup() {
  Serial.begin(9600); // Starting Serial Terminal

  lFoundObject = 0;
  bFoundObject = false;
  
  pinMode(cECHO_PIN, INPUT);
  pinMode(cPUMP_PIN, OUTPUT);
  pinMode(cPING_PIN, OUTPUT);
  pinMode(cBUZZER_PIN, OUTPUT);

  digitalWrite(cPUMP_PIN, LOW);
}

void loop() {
  if (getDistance() < 10) {
    delay(500); // Wait for 1 sec and check distance again { Ajmal }
    if (getDistance() > 15) return;

    Serial.println(F("Object Found"));
    tone(cBUZZER_PIN, 1000);
    digitalWrite(cPUMP_PIN, HIGH);
    delay(100); // Wait for 0.5 sec { Ajmal }    
    digitalWrite(cPUMP_PIN, LOW);
    noTone(cBUZZER_PIN);
    delay(2000);

    // Wait for object to remove { Ajmal }
    while (getDistance() < 20) Serial.print('.');
  }
}

long getDistance() {
  digitalWrite(cPING_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(cPING_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(cPING_PIN, LOW);
  
  long lDuration = pulseIn(cECHO_PIN, HIGH);   
  return microsecondsToCentimeters(lDuration);  
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
