#include <Arduino.h>
#include "MotorControl.h"
#include "ServoControl.h"
#include "pinConfig.h"
#include <stdlib.h>


unsigned long lastPWMChange = 0;
unsigned long lastPrint = 0;
unsigned long lasRotation = 0;
int sensRotation = 1;
int pwmValue = 0;
int rotation = 500;
int step = 50;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  delay(1000);

  delay(2000);
  initPort();
  initServo();

  Serial.println("Boot OK");

}

void loop() {
  unsigned long now = millis();

  // --- Changement de PWM toutes les 3 secondes ---
  if (now - lastPWMChange >= 3000) {
    pwmValue = abs(pwmValue - 150);
    if (pwmValue > 250) pwmValue = 50;  // revient au début
    ledcWrite(CHANNEL_MOTOR_FWD1, 0);
    ledcWrite(CHANNEL_MOTOR_REV1,0);
    ledcWrite(CHANNEL_MOTOR_FWD2, 0);
    ledcWrite(CHANNEL_MOTOR_REV2,0);
    lastPWMChange = now;
  }

  // --- Lecture et affichage toutes les 50 ms ---
  if (now - lastPrint >= 50) {
    int valeur = digitalRead(PIN_OPTDIOD1);
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
