#ifndef VL53L7_H
#define VL53L7_H

#include <Arduino.h>

void init_VL53L7();
void affichage_data(int* ligne, bool show=false);
int find_minimum(int* ligne, int mini);
void print_ligne(int* ligne);


#endif