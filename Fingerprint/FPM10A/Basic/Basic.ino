    
/*
 * FPM10A Fingerprint Sensro Sample
 * Developed by Erratum Solutions
 * Contact us @ support@erratums.com
 * https://erratums.com
 * Date created: 27-July-2019
 */

#include <Adafruit_Fingerprint.h>

SoftwareSerial serialFinger(12, 13);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&serialFinger);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  delay(100);
  Serial.println(F("\nErratum Solutions\nFingerprint sensor"));

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println(F("Found fingerprint sensor!"));
  } else {
    Serial.println(F("Did not find fingerprint sensor :("));
    while (true) delay(100);
  }  
}

uint8_t getNextAvailableID() {
  uint8_t iCntr = 0;
  for (iCntr = 1; iCntr < 126; iCntr++) {
    switch (finger.loadModel(iCntr)) {
      case FINGERPRINT_OK:
        break;
      default:
        return iCntr;
    }
  }
}

void loop() {
  Serial.println();
  Serial.println(F("Place your finger"));
  Serial.println(F("................!"));
  
  while(getFingerprintIDez() == -1);
}

int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  Serial.println(F("Remove Finger"));
  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  {
    Serial.println(F("Ooh, that was too fast"));
    return -1;
  }

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  {
    Serial.println(F("No match found"));
    Serial.println(F("Do you want to register it now ?"));
    Serial.println(F("Type \"YES\" to register, \"NO\" to cancel"));
    while (!Serial.available());

    String sInput = Serial.readString();
    sInput.trim();
    // while(Serial.read());
    if (sInput.equals(F("YES"))) {
      Serial.println();
      registerFingerPrint();
    }
    return -2;
  }
  
  // found a match!
  Serial.print(F("Found ID #"));
  Serial.print(finger.fingerID); 
  Serial.print(F(" with confidence of ")); 
  Serial.println(finger.confidence);
  
  return finger.fingerID; 
}

uint8_t getFingerprintImage(bool isVerify) {
  int p = -1;
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      // Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!
  if (isVerify) p = finger.image2Tz(2);
  else p = finger.image2Tz(1);
  
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
}

uint8_t getFingerprintEnroll(uint8_t aID) {
  Serial.print(F("Waiting for valid finger to enroll. ID: ")); 
  Serial.println(aID);
  Serial.println(F("Place your finger"));

  int p = -1;
  p = getFingerprintImage(false);

  Serial.println(F("Remove finger"));
  delay(2000);
  
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }

  Serial.println(F("Place same finger again"));
  p = getFingerprintImage(true);
  
  // OK converted!
  Serial.print(F("Creating model for #"));  
  Serial.println(aID);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println(F("Prints matched!"));
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println(F("Communication error"));
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println(F("Fingerprints did not match"));
    return p;
  } else {
    Serial.println(F("Unknown error"));
    return p;
  }   
  
  Serial.print("ID "); 
  Serial.println(aID);
  p = finger.storeModel(aID);
  if (p == FINGERPRINT_OK) {
    Serial.println(F("Stored!"));
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println(F("Communication error"));
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println(F("Could not store in that location"));
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println(F("Error writing to flash"));
    return p;
  } else {
    Serial.println(F("Unknown error"));
    return p;
  }   
}

void registerFingerPrint() {
  Serial.println("Ready to enroll a fingerprint!");
  uint8_t iID = getNextAvailableID();
  if (iID > 125) {
    return;
  }
  
  while (!getFingerprintEnroll(iID));  
}
