#include <Arduino.h>
#include "MotorControl.h"
#include "pinConfig.h"


unsigned long lastPWMChange = 0;
unsigned long lastPrint = 0;
int pwmValue = 0;
int step = 50;


void setup() {
  // put your setup code here, to run once:

  delay(2000);

  initPort();
  Serial.begin(115200);


}

void loop() {
  unsigned long now = millis();

  // --- Changement de PWM toutes les 2 secondes ---
  if (now - lastPWMChange >= 2000) {
    pwmValue += step;
    if (pwmValue > 250) pwmValue = 50;  // revient au début
    ledcWrite(CHANNEL_MOTOR_FWD1, pwmValue);
    ledcWrite(CHANNEL_MOTOR_REV1,0);
    lastPWMChange = now;
  }

  // --- Lecture et affichage toutes les 50 ms ---
  if (now - lastPrint >= 50) {
    int valeur = analogRead(A0);
    Serial.println(valeur);
    lastPrint = now;
  }
}

  // for(int i = 0; i<255;i++){
  //   ledcWrite(CHANNEL_MOTOR_FWD1,i);
  //   ledcWrite(CHANNEL_MOTOR_REV1,0);
  //   ledcWrite(CHANNEL_MOTOR_FWD2,i);
  //   ledcWrite(CHANNEL_MOTOR_REV2,0);
  //   ledcWrite(CHANNEL_MOTOR_FWD3,i);
  //   ledcWrite(CHANNEL_MOTOR_REV3,0);
  //   delay(10);
  // }
  // for(int i = 255; i>=0;i--){
  //   ledcWrite(CHANNEL_MOTOR_FWD1,i);
  //   ledcWrite(CHANNEL_MOTOR_REV1,0);
  //   ledcWrite(CHANNEL_MOTOR_FWD2,i);
  //   ledcWrite(CHANNEL_MOTOR_REV2,0);
  //   ledcWrite(CHANNEL_MOTOR_FWD3,i);
  //   ledcWrite(CHANNEL_MOTOR_REV3,0);
  //   delay(3);
  // }

  //   for(int i = 0; i<255;i++){
  //   ledcWrite(CHANNEL_MOTOR_FWD1,0);
  //   ledcWrite(CHANNEL_MOTOR_REV1,i);
  //   ledcWrite(CHANNEL_MOTOR_FWD2,i);
  //   ledcWrite(CHANNEL_MOTOR_REV2,0);
  //   ledcWrite(CHANNEL_MOTOR_FWD3,i);
  //   ledcWrite(CHANNEL_MOTOR_REV3,0);
  //   delay(3);
  // }
  // for(int i = 255; i>=0;i--){
  //   ledcWrite(CHANNEL_MOTOR_FWD1,0);
  //   ledcWrite(CHANNEL_MOTOR_REV1,i);
  //   ledcWrite(CHANNEL_MOTOR_FWD2,i);
  //   ledcWrite(CHANNEL_MOTOR_REV2,0);
  //   ledcWrite(CHANNEL_MOTOR_FWD3,i);
  //   ledcWrite(CHANNEL_MOTOR_REV3,0);
  //   delay(3);
  // }


  // for(int i = 0; i<255;i++){
  //   ledcWrite(CHANNEL_MOTOR_FWD1,0);
  //   ledcWrite(CHANNEL_MOTOR_REV1,i);
  //   ledcWrite(CHANNEL_MOTOR_FWD2,0);
  //   ledcWrite(CHANNEL_MOTOR_REV2,i);
  //   ledcWrite(CHANNEL_MOTOR_FWD3,0);
  //   ledcWrite(CHANNEL_MOTOR_REV3,i);
  //   delay(3);
  // }
  // for(int i = 255; i>=0;i--){
  //   ledcWrite(CHANNEL_MOTOR_FWD1,0);
  //   ledcWrite(CHANNEL_MOTOR_REV1,i);
  //   ledcWrite(CHANNEL_MOTOR_FWD2,0);
  //   ledcWrite(CHANNEL_MOTOR_REV2,i);
  //   ledcWrite(CHANNEL_MOTOR_FWD3,0);
  //   ledcWrite(CHANNEL_MOTOR_REV3,i);
  //   delay(3);
  // }

  // for(int i = 0; i<255;i++){
  //   ledcWrite(CHANNEL_MOTOR_FWD1,i);
  //   ledcWrite(CHANNEL_MOTOR_REV1,0);
  //   ledcWrite(CHANNEL_MOTOR_FWD2,0);
  //   ledcWrite(CHANNEL_MOTOR_REV2,i);
  //   ledcWrite(CHANNEL_MOTOR_FWD3,0);
  //   ledcWrite(CHANNEL_MOTOR_REV3,i);
  //   delay(3);
  // }
  // for(int i = 255; i>=0;i--){
  //   ledcWrite(CHANNEL_MOTOR_FWD1,i);
  //   ledcWrite(CHANNEL_MOTOR_REV1,0);
  //   ledcWrite(CHANNEL_MOTOR_FWD2,0);
  //   ledcWrite(CHANNEL_MOTOR_REV2,i);
  //   ledcWrite(CHANNEL_MOTOR_FWD3,0);
  //   ledcWrite(CHANNEL_MOTOR_REV3,i);
  //   delay(3);
  // }
// }