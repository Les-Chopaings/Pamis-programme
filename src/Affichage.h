#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <Arduino.h>
#include "pinConfig.h"
#include <Types.h>

void dashboard(int pos_mot1, int pos_mot2, int speed,bool obstacle,int ligne[8], Position position, Param param);

#endif