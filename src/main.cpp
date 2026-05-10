#include <Arduino.h>
#include "MotorControl.h"
#include "ServoControl.h"
#include "pinConfig.h"
#include "VL53L7.h"
#include <stdlib.h>
#include <Affichage.h>
#include <Types.h>

ObjectifPos obj_pos = ObjectifPos(1000,0);


unsigned long lastPWMChange = 0;
unsigned long lastPrint = 0;
unsigned long lasRotation = 0;
int sensRotation = 0;
int pwmValue = 0;
int rotation = 500;
int step = 50;

int checkpos = 0;
int pos_mot1 = 0;
int pos_mot2 = 0;
int last_value_mot1 = 0;
int last_value_mot2 = 0;
int speed = 0;

int ligne[8];
int mini = 200;
bool obstacle = false;

int old_pos_mot1 = 0;
int old_pos_mot2 = 0;
int old_speed = 250;
int old_obstacle = false;
int old_ligne[8];
Position old_position = Position();
int last_show = 0;

int read_start = 0;
bool etat_start = false;

Param param = Param();
Position position = Position();


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  delay(1000);

  delay(2000);
  initPort();
  initServo();

  init_VL53L7();
  
  Position position ;
  Serial.println("Boot OK");

  delay(2000);
  // Serial.printf("valeur param : %.2f, %.2f, %.2f, %.2f", param.stepAngleD, param.stepAngleG,param.stepForrwardD, param.stepForrwardG);
  // Serial.print("\033[2J");
  delay(2000);

}

void loop() {
  unsigned long now = millis();

  // if (now - read_start >= 100) {
  //   Serial.print("\033[2J");
  //   Serial.print("\033[H");
  //   int value_start  = digitalRead(PIN_OPTDIOD_start);
  //   Serial.printf("Value fourche optique  : %d \n", value_start);

  //   if (value_start == 1){
  //     ledcWrite(CHANNEL_MOTOR_FWD1, 0);
  //     ledcWrite(CHANNEL_MOTOR_REV1,200);
  //     ledcWrite(CHANNEL_MOTOR_FWD2, 0);
  //     ledcWrite(CHANNEL_MOTOR_REV2,200);
  //   }

  //   else {
  //     ledcWrite(CHANNEL_MOTOR_FWD1, 0);
  //     ledcWrite(CHANNEL_MOTOR_REV1,0);
  //     ledcWrite(CHANNEL_MOTOR_FWD2, 0);
  //     ledcWrite(CHANNEL_MOTOR_REV2,0);
  //   }
  // }


  // --- Changement de PWM toutes les 3 secondes ---
  if (now - lastPWMChange >= 100) {

    affichage_data(ligne, false);
    mini = find_minimum(ligne, mini);

    if (mini < 100){
      ledcWrite(CHANNEL_MOTOR_FWD1,0);
      ledcWrite(CHANNEL_MOTOR_REV1,0);
      ledcWrite(CHANNEL_MOTOR_FWD2,0);
      ledcWrite(CHANNEL_MOTOR_REV2,0);
      obstacle = true;
      speed = 0;
    }

    else{
      
      if (speed == 0){
        speed = 150;
      }

      Asservissement_angulaire(position, obj_pos, speed, sensRotation);

      // ledcWrite(CHANNEL_MOTOR_FWD1,0);
      // ledcWrite(CHANNEL_MOTOR_REV1,200);
      // ledcWrite(CHANNEL_MOTOR_FWD2,0);
      // ledcWrite(CHANNEL_MOTOR_REV2,200);

      obstacle = false;
    }

    lastPWMChange = now;
  }

  if (now - checkpos >= 1){
    read_fourche_optique(&last_value_mot1, &last_value_mot2, &pos_mot1, &pos_mot2, param, position);
  }


  if (old_pos_mot1 != pos_mot1, old_pos_mot2 != pos_mot2, old_speed != speed, old_obstacle != obstacle, old_ligne != ligne, \
  old_position.x != position.x, old_position.y != position.y, old_position.teta != position.teta, now - last_show > 200){
    // dashboard(pos_mot1, pos_mot2, speed, obstacle, ligne, position, param);

    old_pos_mot1 = pos_mot1;
    old_pos_mot2 = pos_mot2;
    old_speed = speed;
    old_obstacle = obstacle;

    for(int i = 0; i < 8; i++)
    {
        old_ligne[i] = ligne[i];
    }
    
    old_position.x = position.x;
    old_position.y = position.y;
    old_position.teta = position.teta;

    last_show = now;
  }


  // --- Rotation du servo moteur ---
  if (now - lasRotation >= 20) {
    if (sensRotation == 1) {
      if (rotation < 2200) {
        rotation = rotation + 1;
      }
      else {
        sensRotation = -1;
      }
    }
    else {
      if (rotation > 1600) {
        rotation = rotation - 1;
      }
      else {
        sensRotation = 1;
      }
    } 
    
    // Serial.println(rotation);
    // setServoAngle(rotation);
    // lasRotation = now;
  }


}
