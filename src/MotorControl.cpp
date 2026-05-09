#include "MotorControl.h"
#include <Types.h>


void odometrieCalc(Position &position, Param &param, Roue roue);

void initPort(void){
    pinMode(PIN_MOTOR_FWD1,OUTPUT);
    pinMode(PIN_MOTOR_REV1,OUTPUT);
    pinMode(PIN_MOTOR_FWD2,OUTPUT);
    pinMode(PIN_MOTOR_REV2,OUTPUT);
    pinMode(PIN_OPTDIOD_mot_1, INPUT);
    pinMode(PIN_OPTDIOD_mot_2, INPUT);
    pinMode(PIN_OPTDIOD_start, INPUT);


    const int freq = 30000;
    const int resolution = 8;

    // configure LED PWM functionalitites
    ledcSetup(CHANNEL_MOTOR_FWD1, freq, resolution);
    ledcAttachPin(PIN_MOTOR_FWD1, CHANNEL_MOTOR_FWD1);

    ledcSetup(CHANNEL_MOTOR_REV1, freq, resolution);
    ledcAttachPin(PIN_MOTOR_REV1, CHANNEL_MOTOR_REV1);

    ledcSetup(CHANNEL_MOTOR_FWD2, freq, resolution);
    ledcAttachPin(PIN_MOTOR_FWD2, CHANNEL_MOTOR_FWD2);

    ledcSetup(CHANNEL_MOTOR_REV2, freq, resolution);
    ledcAttachPin(PIN_MOTOR_REV2, CHANNEL_MOTOR_REV2);
}

void motorControl1(int drirectionFWD, int speed){
    if(drirectionFWD){
        ledcWrite(CHANNEL_MOTOR_FWD1,speed);
        ledcWrite(CHANNEL_MOTOR_REV1,0);
    }
    else{
        ledcWrite(CHANNEL_MOTOR_FWD1,0);
        ledcWrite(CHANNEL_MOTOR_REV1,speed);
    }
}

void motorControl2(int drirectionFWD, int speed){
    if(drirectionFWD){
        ledcWrite(CHANNEL_MOTOR_FWD2,speed);
        ledcWrite(CHANNEL_MOTOR_REV2,0);
    }
    else{
        ledcWrite(CHANNEL_MOTOR_FWD2,0);
        ledcWrite(CHANNEL_MOTOR_REV2,speed);
    }
}


void read_fourche_optique(int* last_value_mot1, int* last_value_mot2, int* pos_mot1, int* pos_mot2, Param &param, Position &position){

    int value_mot1  = digitalRead(PIN_OPTDIOD_mot_1);
    int value_mot2  = digitalRead(PIN_OPTDIOD_mot_2);

    if (*last_value_mot1 !=value_mot1){
            *pos_mot1+=1;
            *last_value_mot1 = value_mot1;
            odometrieCalc(position,param, LEFT);
            
    }

    if (*last_value_mot2 !=value_mot2){
            *pos_mot2+=1;
            *last_value_mot2 = value_mot2;
            odometrieCalc(position, param, RIGTH);
    }
}


void odometrieCalc(Position &position, Param &param, Roue roue){
    switch (roue)
    {
        case LEFT:
                position.y += param.stepForrwardG * sin(position.teta); //Voir pour optimisation
                position.x += param.stepForrwardG * cos(position.teta); //Voir pour optimisation
                position.teta -= param.stepAngleG;
            break;
        case RIGTH:
                position.y += param.stepForrwardD * sin(position.teta); //Voir pour optimisation
                position.x += param.stepForrwardD * cos(position.teta); //Voir pour optimisation
                position.teta += param.stepAngleD;
            break;
        default:
            break;
    }
}