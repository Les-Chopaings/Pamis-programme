#include "ServoControl.h"


// ✅ vraie création de l'objet
Servo monServo;

void initServo() {
    monServo.attach(4);

}

void setServoAngle(int angle) {
    monServo.write(angle);
}