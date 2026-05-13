#include "ServoControl.h"


// ✅ vraie création de l'objet
Servo monServo;

void initServo() {
    monServo.attach(4);
    setServoAngle(2000);
}

void setServoAngle(int angle) {
    monServo.write(angle);
}

void rotation_queue(int* sensRotation, int* rotation){
    

    if (*sensRotation == 1){
      if (*rotation < 2200) {
        *rotation = *rotation + 10;
      }
      else {
        *sensRotation = -1;
      }
    }
    else {
      if (*rotation > 1900) {
        *rotation = *rotation - 10;
      }
      else {
        *sensRotation = 1;
      }
    }
    // Serial.println(*rotation);
    setServoAngle(*rotation);
  }