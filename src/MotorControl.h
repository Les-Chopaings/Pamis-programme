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
void Asservissement_angulaire(Position &position, ObjectifPos & obj_pos, int speed, int sensRotation);
void odometrieCalc(Position &position, Roue roue);

#endif