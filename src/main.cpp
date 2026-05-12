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

unsigned long msPrevious = 0;
unsigned long msNow = 0;
int pos_mot1 = 0;
int pos_mot2 = 0;
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

Position position = Position();


volatile bool mot1_state = false;
volatile bool mot2_state = false;

volatile uint32_t mot1_rising_count = 0;
volatile uint32_t mot1_falling_count = 0;

volatile uint32_t mot2_rising_count = 0;
volatile uint32_t mot2_falling_count = 0;

volatile uint32_t lastInterruptMot1 = 0;
volatile uint32_t lastInterruptMot2 = 0;

const uint32_t DEBOUNCE_US = 10; // 3 ms

void IRAM_ATTR isr_mot1()
{
    uint32_t now = micros();

    // anti-rebond
    if ((now - lastInterruptMot1) < DEBOUNCE_US)
    {
        return;
    }

    lastInterruptMot1 = now;

    bool state = digitalRead(PIN_OPTDIOD_mot_1);

    mot1_state = state;

    //odometrieCalc(position, LEFT);

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
    uint32_t now = micros();

    // anti-rebond
    if ((now - lastInterruptMot2) < DEBOUNCE_US)
    {
        return;
    }

    lastInterruptMot2 = now;

    bool state = digitalRead(PIN_OPTDIOD_mot_2);

    mot2_state = state;

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

  attachInterrupt(PIN_OPTDIOD_mot_1, isr_mot1, CHANGE);
  attachInterrupt(PIN_OPTDIOD_mot_2, isr_mot2, CHANGE);

}

void loop() {
  unsigned long now = millis();

  ledcWrite(CHANNEL_MOTOR_FWD1,200);
  ledcWrite(CHANNEL_MOTOR_REV1,0);
  ledcWrite(CHANNEL_MOTOR_FWD2,0);
  ledcWrite(CHANNEL_MOTOR_REV2,200);

  affichage_data(ligne, true);

  msNow = millis();
  if((msNow - msPrevious) > 5){
    Serial.println("too slow");
  }
  msPrevious = msNow;

  Serial.print("x : ");
  Serial.print(position.x);
  Serial.print(" y : ");
  Serial.print(position.y);
  Serial.print(" theta : ");
  Serial.println(position.teta * RAD_TO_DEG);





  Serial.print(mot1_rising_count);
  Serial.print(" ");
  Serial.print(mot1_falling_count);
  Serial.print(" ");
  Serial.print(mot2_rising_count);
  Serial.print(" ");
  Serial.println(mot2_falling_count);


  // if (old_pos_mot1 != pos_mot1, old_pos_mot2 != pos_mot2, old_speed != speed, old_obstacle != obstacle, old_ligne != ligne, \
  // old_position.x != position.x, old_position.y != position.y, old_position.teta != position.teta, now - last_show > 200){
  //   // dashboard(pos_mot1, pos_mot2, speed, obstacle, ligne, position, param);

  //   old_pos_mot1 = pos_mot1;
  //   old_pos_mot2 = pos_mot2;
  //   old_speed = speed;
  //   old_obstacle = obstacle;

  //   for(int i = 0; i < 8; i++)
  //   {
  //       old_ligne[i] = ligne[i];
  //   }
    
  //   old_position.x = position.x;
  //   old_position.y = position.y;
  //   old_position.teta = position.teta;

  //   last_show = now;
  // }


  // // --- Rotation du servo moteur ---
  // if (now - lasRotation >= 20) {
  //   if (sensRotation == 1) {
  //     if (rotation < 2200) {
  //       rotation = rotation + 1;
  //     }
  //     else {
  //       sensRotation = -1;
  //     }
  //   }
  //   else {
  //     if (rotation > 1600) {
  //       rotation = rotation - 1;
  //     }
  //     else {
  //       sensRotation = 1;
  //     }
  //   }
  //   // Serial.println(rotation);
  //   // setServoAngle(rotation);
  //   // lasRotation = now;
  // }


}
