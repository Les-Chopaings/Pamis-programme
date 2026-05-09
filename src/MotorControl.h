#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>
#include "pinConfig.h"
#include <Types.h>

void initPort(void);
void motorControl1(int drirectionFWD, int speed);
void motorControl2(int drirectionFWD, int speed);
void motorControl3(int drirectionFWD, int speed);
void read_fourche_optique(int* last_value_mot1, int* last_value_mot2, int* pos_mot1, int* pos_mot2, Param &param, Position &position);


#endif