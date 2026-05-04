#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <ESP32Servo.h>

// déclaration (pas de création mémoire ici)
extern Servo monServo;

void initServo();
void setServoAngle(int angle);

#endif