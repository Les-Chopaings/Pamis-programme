#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>
#include "pinConfig.h"

void initPort(void);
void motorControl1(int drirectionFWD, int speed);
void motorControl2(int drirectionFWD, int speed);
void motorControl3(int drirectionFWD, int speed);

#endif