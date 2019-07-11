/*
 * Arduino 4CH Relay Shield Basic Sample
 * Developed by Erratum Solutions
 * Contact us @ support@erratums.com
 * https://erratums.com
 * Date created: 12-July-2019
 */
 
const byte RELAY_1 = 7;
const byte RELAY_2 = 6;
const byte RELAY_3 = 5;
const byte RELAY_4 = 4;

const char cRELAY_STATE_UPDATED[] = "Relay state updated: Relay-";

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println(F("Initializing . . . !"));

  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, OUTPUT);

  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_2, LOW);
  digitalWrite(RELAY_3, LOW);
  digitalWrite(RELAY_4, LOW);
}

void loop() {
  // This is a sample application to toggle the relay state 
  delay(1000);
  digitalWrite(RELAY_1, !digitalRead(RELAY_1));
  Serial.print(cRELAY_STATE_UPDATED);
  Serial.println(RELAY_1);
  
  delay(1000);
  digitalWrite(RELAY_2, !digitalRead(RELAY_2));
  Serial.print(cRELAY_STATE_UPDATED);
  Serial.println(RELAY_2);
  
  delay(1000);
  digitalWrite(RELAY_3, !digitalRead(RELAY_3));
  Serial.print(cRELAY_STATE_UPDATED);
  Serial.println(RELAY_3);
  
  delay(1000);
  digitalWrite(RELAY_4, !digitalRead(RELAY_4));
  Serial.print(cRELAY_STATE_UPDATED);
  Serial.println(RELAY_4);  
}
