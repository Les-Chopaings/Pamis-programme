#include <Arduino.h>
#include "MotorControl.h"
#include "ServoControl.h"
#include "pinConfig.h"
#include "VL53L7.h"
#include <stdlib.h>


unsigned long lastPWMChange = 0;
unsigned long lastPrint = 0;
unsigned long lasRotation = 0;
int sensRotation = 1;
int pwmValue = 0;
int rotation = 500;
int step = 50;
int time_data = 0;
int ligne[8];
int mini = 200;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  delay(1000);

  delay(2000);
  initPort();
  initServo();

  init_VL53L7();
  
  Serial.println("Boot OK");

}

void loop() {
  unsigned long now = millis();

  // --- Changement de PWM toutes les 3 secondes ---
  if (now - lastPWMChange >= 3000) {

    pwmValue = abs(pwmValue - 150);
    if (pwmValue > 250) pwmValue = 50;  // revient au début
    ledcWrite(CHANNEL_MOTOR_FWD1, 150);
    ledcWrite(CHANNEL_MOTOR_REV1,0);
    ledcWrite(CHANNEL_MOTOR_FWD2, 150);
    ledcWrite(CHANNEL_MOTOR_REV2,0);
    lastPWMChange = now;
  }

  if (now - time_data >= 10) {
    affichage_data(ligne, true);
    // Serial.print("valeur ligne:\t");
    // print_ligne(ligne);

    
    mini = find_minimum(ligne, mini);
    
    Serial.printf("minimum ligne : %d\n", mini);
    if (mini < 50){
      while (mini < 50){
        ledcWrite(CHANNEL_MOTOR_FWD1, 0);
        ledcWrite(CHANNEL_MOTOR_REV1,0);
        ledcWrite(CHANNEL_MOTOR_FWD2, 0);
        ledcWrite(CHANNEL_MOTOR_REV2,0);

        affichage_data(ligne, true);
        mini = find_minimum(ligne, mini);
      }
    }
    time_data = now;
  }


  // --- Lecture et affichage toutes les 50 ms ---
  if (now - lastPrint >= 50) {
    // Serial.println(valeur);
    lastPrint = now;
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
    
    Serial.println(rotation);
    setServoAngle(rotation);
    lasRotation = now;
  }
}
