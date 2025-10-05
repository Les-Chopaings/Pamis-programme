#include <Arduino.h>
#include "MotorControl.h"
#include "pinConfig.h"
void setup() {
  // put your setup code here, to run once:

  delay(2000);

  initPort();
  Serial.begin(115200);


}

void loop() {
  // put your main code here, to run repeatedly:

 

  for(int i = 0; i<255;i++){
    ledcWrite(CHANNEL_MOTOR_FWD1,i);
    ledcWrite(CHANNEL_MOTOR_REV1,0);
    ledcWrite(CHANNEL_MOTOR_FWD2,i);
    ledcWrite(CHANNEL_MOTOR_REV2,0);
    ledcWrite(CHANNEL_MOTOR_FWD3,i);
    ledcWrite(CHANNEL_MOTOR_REV3,0);
    delay(3);
  }
  for(int i = 255; i>=0;i--){
    ledcWrite(CHANNEL_MOTOR_FWD1,i);
    ledcWrite(CHANNEL_MOTOR_REV1,0);
    ledcWrite(CHANNEL_MOTOR_FWD2,i);
    ledcWrite(CHANNEL_MOTOR_REV2,0);
    ledcWrite(CHANNEL_MOTOR_FWD3,i);
    ledcWrite(CHANNEL_MOTOR_REV3,0);
    delay(3);
  }

    for(int i = 0; i<255;i++){
    ledcWrite(CHANNEL_MOTOR_FWD1,0);
    ledcWrite(CHANNEL_MOTOR_REV1,i);
    ledcWrite(CHANNEL_MOTOR_FWD2,i);
    ledcWrite(CHANNEL_MOTOR_REV2,0);
    ledcWrite(CHANNEL_MOTOR_FWD3,i);
    ledcWrite(CHANNEL_MOTOR_REV3,0);
    delay(3);
  }
  for(int i = 255; i>=0;i--){
    ledcWrite(CHANNEL_MOTOR_FWD1,0);
    ledcWrite(CHANNEL_MOTOR_REV1,i);
    ledcWrite(CHANNEL_MOTOR_FWD2,i);
    ledcWrite(CHANNEL_MOTOR_REV2,0);
    ledcWrite(CHANNEL_MOTOR_FWD3,i);
    ledcWrite(CHANNEL_MOTOR_REV3,0);
    delay(3);
  }


  for(int i = 0; i<255;i++){
    ledcWrite(CHANNEL_MOTOR_FWD1,0);
    ledcWrite(CHANNEL_MOTOR_REV1,i);
    ledcWrite(CHANNEL_MOTOR_FWD2,0);
    ledcWrite(CHANNEL_MOTOR_REV2,i);
    ledcWrite(CHANNEL_MOTOR_FWD3,0);
    ledcWrite(CHANNEL_MOTOR_REV3,i);
    delay(3);
  }
  for(int i = 255; i>=0;i--){
    ledcWrite(CHANNEL_MOTOR_FWD1,0);
    ledcWrite(CHANNEL_MOTOR_REV1,i);
    ledcWrite(CHANNEL_MOTOR_FWD2,0);
    ledcWrite(CHANNEL_MOTOR_REV2,i);
    ledcWrite(CHANNEL_MOTOR_FWD3,0);
    ledcWrite(CHANNEL_MOTOR_REV3,i);
    delay(3);
  }

  for(int i = 0; i<255;i++){
    ledcWrite(CHANNEL_MOTOR_FWD1,i);
    ledcWrite(CHANNEL_MOTOR_REV1,0);
    ledcWrite(CHANNEL_MOTOR_FWD2,0);
    ledcWrite(CHANNEL_MOTOR_REV2,i);
    ledcWrite(CHANNEL_MOTOR_FWD3,0);
    ledcWrite(CHANNEL_MOTOR_REV3,i);
    delay(3);
  }
  for(int i = 255; i>=0;i--){
    ledcWrite(CHANNEL_MOTOR_FWD1,i);
    ledcWrite(CHANNEL_MOTOR_REV1,0);
    ledcWrite(CHANNEL_MOTOR_FWD2,0);
    ledcWrite(CHANNEL_MOTOR_REV2,i);
    ledcWrite(CHANNEL_MOTOR_FWD3,0);
    ledcWrite(CHANNEL_MOTOR_REV3,i);
    delay(3);
  }
}