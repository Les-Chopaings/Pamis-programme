#ifndef VL53L7_H
#define VL53L7_H

#include <Arduino.h>

void init_VL53L7();
void affichage_data(uint32_t* ligne, bool show=false);
int find_minimum(uint32_t* ligne, int mini);
void print_ligne(uint32_t* ligne);
int calcul_moy_ligne(uint32_t* ligne);

#endif