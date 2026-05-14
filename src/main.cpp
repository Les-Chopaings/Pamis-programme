#include <Arduino.h>
#include "MotorControl.h"
#include "ServoControl.h"
#include "pinConfig.h"
#include "VL53L7.h"
#include <stdlib.h>
#include <Affichage.h>
#include <Types.h>

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

ObjectifPos obj_pos = ObjectifPos(700,0);

bool obj_atteint = false;
int sensRotationservo = 0;
unsigned long lastPWMChange = 0;
unsigned long lastPrint = 0;
unsigned long lasRotation = 0;
int sensRotation_mot1 = 1;
int sensRotation_mot2 = 1;
int pwmValue = 0;
int rotation = 1900;
int step = 50;

unsigned long msPrevious = 0;
unsigned long msNow = 0;

unsigned long msstart = 0;
unsigned long msend = 0;

unsigned long last_asser = 0;
unsigned long last_evitement = 0;
int pos_mot1 = 0;
int pos_mot2 = 0;
int speed = 0;

uint32_t ligne[8];
int mini = 200;
bool obstacle = false;

int old_pos_mot1 = 0;
int old_pos_mot2 = 0;
int old_speed = 250;
int old_obstacle = false;
int old_ligne[8];
Position old_position = Position();
int last_show = 0;

float read_start = 0;
bool etat_start = false;

Position position = Position();

volatile uint32_t mot1_rising_count = 0;
volatile uint32_t mot1_falling_count = 0;

volatile uint32_t mot2_rising_count = 0;
volatile uint32_t mot2_falling_count = 0;

volatile uint32_t lastInterruptMot1 = 0;
volatile uint32_t lastInterruptMot2 = 0;

const uint32_t DEBOUNCE_US = 3000; // 3 ms

volatile bool lastMot1State = false;
volatile bool lastMot2State = false;

void IRAM_ATTR isr_mot1()
{
    bool state = digitalRead(PIN_OPTDIOD_mot_1);

    // Ignore si l'état n'a pas changé
    if (state == lastMot1State)
    {
        return;
    }

    // Sauvegarde nouvel état
    lastMot1State = state;

    odometrieCalc(position, LEFT);

    if (state)
    {
        mot1_rising_count++;
    }
    else
    {
        mot1_falling_count++;
    }
}

void IRAM_ATTR isr_mot2()
{
    bool state = digitalRead(PIN_OPTDIOD_mot_2);

    // Ignore si l'état n'a pas changé
    if (state == lastMot2State)
    {
        return;
    }

    // Sauvegarde nouvel état
    lastMot2State = state;

    odometrieCalc(position, RIGTH);

    if (state)
    {
        mot2_rising_count++;
    }
    else
    {
        mot2_falling_count++;
    }
}


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  delay(1000);

  initPort();
  initServo();

  init_VL53L7();

  Position position;
  Serial.println("Boot OK");

  read_start = digitalRead(PIN_OPTDIOD_start);
  if (read_start){
    etat_start = true;
  }
  delay(2000);

  // Serial.printf("valeur param : %.2f, %.2f, %.2f, %.2f", param.stepAngleD, param.stepAngleG,param.stepForrwardD, param.stepForrwardG);
  // Serial.print("\033[2J");

  attachInterrupt(PIN_OPTDIOD_mot_1, isr_mot1, CHANGE);
  attachInterrupt(PIN_OPTDIOD_mot_2, isr_mot2, CHANGE);

}

void loop() {
  unsigned long now = millis();

  read_start = digitalRead(PIN_OPTDIOD_start);
  Serial.printf("value readstart = %.2f", read_start);
  Serial.println();


  if (read_start && !etat_start){
    delay(85000);
    etat_start = true;
  }

  if (etat_start){

  /*---Fonction qui incrémente la vitesse des moteurs*/
  if ((speed < 220) && ((now - lastPWMChange) > 10)){
      speed += 2;
      lastPWMChange = now;
      // Serial.printf("valeur vitesse : %.d", speed);
      // Serial.println();
    }

  /*---Fonction qui gère le mouvement du pami*/
  if (!obj_atteint && (now - last_asser) > 50){
    // Serial.printf("---AVANCE---");
    // Serial.println();
    go_forward(obj_pos, position, constrain(speed, 0, 255), &obj_atteint);
    
    last_asser = now;
    }
  else if(obj_atteint){
    Serial.printf("---STOP---");
    Serial.println();
    stop();
  }


  /*---Fonction qui vérifie si besoin de s'arrêter*/
  if ((now - last_evitement) > 50){

    affichage_data(ligne, false);
    std::sort(ligne, ligne+4);
    float med = ligne[2];
    // int maximum = *std::max_element(ligne, ligne+8);

    print_ligne(ligne);
    Serial.printf("---------valeur med : %.2f", med);
    Serial.println();
    // Serial.printf("max ligne : %.2d", maximum);
    // Serial.println();

    if (med > 1000){
      Serial.printf("ON SARRETE!!!");
      Serial.println();
      stop();
      speed = 0;
    }

    last_evitement=now;
  }

//   affichage_data(ligne, true);

//   msNow = millis();
//   if((msNow - msPrevious) > 5){
//     Serial.println("too slow");
//   }
//   msPrevious = msNow;

//   Serial.print("x : ");
//   Serial.print(position.x);
//   Serial.print(" y : ");
//   Serial.print(position.y);
//   Serial.print(" theta : ");
//   Serial.println(position.teta * RAD_TO_DEG);

//   Serial.print(mot1_rising_count);
//   Serial.print(" ");
//   Serial.print(mot1_falling_count);
//   Serial.print(" ");
//   Serial.print(mot2_rising_count);
//   Serial.print(" ");
//   Serial.println(mot2_falling_count);

  // --- Rotation du servo moteur ---
  if (obj_atteint) {
    Serial.printf("---FINI---");
    Serial.println();
    rotation_queue(&sensRotationservo, &rotation);
    delay(10);
    // Serial.print(rotation);
    // Serial.println();
    // Serial.print(sensRotationservo);
    // Serial.println();
  }

}
}
