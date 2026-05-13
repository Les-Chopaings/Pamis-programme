#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>
#include "pinConfig.h"
#include <Types.h>

void initPort(void);
void motorControl1(int drirectionFWD, int speed);
void motorControl2(int drirectionFWD, int speed);
void motorControl3(int drirectionFWD, int speed);
void read_fourche_optique(int* pos_mot1, int* pos_mot2, Position &position);
float Asservissement_angulaire(Position &position, ObjectifPos & obj_pos);
void odometrieCalc(Position &position, Roue roue);
void go_forward(ObjectifPos & obj_pos, Position &position, int speed, bool *obj_atteint);
void stop();
#endif