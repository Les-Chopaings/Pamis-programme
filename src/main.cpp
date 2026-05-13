#include <Arduino.h>
#include "MotorControl.h"
#include "ServoControl.h"
#include "pinConfig.h"
#include "VL53L7.h"
#include <stdlib.h>
#include <Affichage.h>
#include <Types.h>

ObjectifPos obj_pos = ObjectifPos(75*5,0);

bool obj_atteint = false;
int sensRotationservo = 1;
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
unsigned long last_asser = 0;
unsigned long last_evitement = 0;
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

float read_start = 0;
bool etat_start = false;

int i = 100;
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

  Position position ;
  Serial.println("Boot OK");

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
    delay(5000);
    etat_start = true;
  }

  if (etat_start){

  float distance = sqrt(pow((position.x),2) + pow((position.y),2));

  if (distance < 10){
    motorControl1( sensRotation_mot1, 255);
    motorControl2(sensRotation_mot2, 255);
  }

  if (i < 240 && now - lastPWMChange > 10){
      i += 2;
      lastPWMChange = now;
      // Serial.printf("valeur vitesse : %.d", i);
      // Serial.println();
    }

  if (!obj_atteint){

    
    go_forward(obj_pos, position, i, &obj_atteint);

    delay(30);

  }
  else{
      ledcWrite(CHANNEL_MOTOR_FWD1,0);
      ledcWrite(CHANNEL_MOTOR_REV1,0);
      ledcWrite(CHANNEL_MOTOR_FWD2,0);
      ledcWrite(CHANNEL_MOTOR_REV2,0);
  }


  if (now- last_evitement > 100){
    
    affichage_data(ligne, false);
    float moy = calcul_moy_ligne(ligne);
    // mini = find_minimum(ligne, mini);

    int maximum = ligne[0];

    for (int i = 1; i < 5; i++) {
        maximum = max(maximum, ligne[i]);
    } 

    print_ligne(ligne);
    Serial.println();
    Serial.printf("valeur moy : %.2f", moy);
    Serial.println();
    Serial.printf("maxligne : %.2d", maximum);
    Serial.println();


    if (moy < 70 && maximum - moy < 30){
      stop();
      i = 100;
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


  if (old_pos_mot1 != pos_mot1, old_pos_mot2 != pos_mot2, old_speed != speed, old_obstacle != obstacle, old_ligne != ligne, \
  old_position.x != position.x, old_position.y != position.y, old_position.teta != position.teta, now - last_show > 400){
    // dashboard(pos_mot1, pos_mot2, speed, obstacle, ligne, position);

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
  if (obj_atteint) {
    rotation_queue(&sensRotationservo, &rotation);
    delay(10);

    Serial.print(rotation);
    Serial.println();
    Serial.print(sensRotationservo);
    Serial.println();
  }

}
}
