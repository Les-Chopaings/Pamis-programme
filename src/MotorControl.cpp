// #include "MotorControl.h"


// void initPort(void){
//     pinMode(PIN_MOTOR_FWD1,OUTPUT);
//     pinMode(PIN_MOTOR_REV1,OUTPUT);
//     pinMode(PIN_MOTOR_FWD2,OUTPUT);
//     pinMode(PIN_MOTOR_REV2,OUTPUT);
//     pinMode(PIN_MOTOR_FWD3,OUTPUT);
//     pinMode(PIN_MOTOR_REV3,OUTPUT);


//     const int freq = 30000;
//     const int resolution = 8;

//     // configure LED PWM functionalitites
//     ledcSetup(CHANNEL_MOTOR_FWD1, freq, resolution);
//     ledcAttachPin(PIN_MOTOR_FWD1, CHANNEL_MOTOR_FWD1);

//     ledcSetup(CHANNEL_MOTOR_REV1, freq, resolution);
//     ledcAttachPin(PIN_MOTOR_REV1, CHANNEL_MOTOR_REV1);

//     ledcSetup(CHANNEL_MOTOR_FWD2, freq, resolution);
//     ledcAttachPin(PIN_MOTOR_FWD2, CHANNEL_MOTOR_FWD2);

//     ledcSetup(CHANNEL_MOTOR_REV2, freq, resolution);
//     ledcAttachPin(PIN_MOTOR_REV2, CHANNEL_MOTOR_REV2);

//     ledcSetup(CHANNEL_MOTOR_FWD3, freq, resolution);
//     ledcAttachPin(PIN_MOTOR_FWD3, CHANNEL_MOTOR_FWD3);

//     ledcSetup(CHANNEL_MOTOR_REV3, freq, resolution);
//     ledcAttachPin(PIN_MOTOR_REV3, CHANNEL_MOTOR_REV3);
// }

// void motorControl1(int drirectionFWD, int speed){
//     if(drirectionFWD){
//         ledcWrite(CHANNEL_MOTOR_FWD1,speed);
//         ledcWrite(CHANNEL_MOTOR_REV1,0);
//     }
//     else{
//         ledcWrite(CHANNEL_MOTOR_FWD1,0);
//         ledcWrite(CHANNEL_MOTOR_REV1,speed);
//     }
// }

// void motorControl2(int drirectionFWD, int speed){
//     if(drirectionFWD){
//         ledcWrite(CHANNEL_MOTOR_FWD2,speed);
//         ledcWrite(CHANNEL_MOTOR_REV2,0);
//     }
//     else{
//         ledcWrite(CHANNEL_MOTOR_FWD2,0);
//         ledcWrite(CHANNEL_MOTOR_REV2,speed);
//     }
// }

// void motorControl3(int drirectionFWD, int speed){
//     if(drirectionFWD){
//         ledcWrite(CHANNEL_MOTOR_FWD3,speed);
//         ledcWrite(CHANNEL_MOTOR_REV3,0);
//     }
//     else{
//         ledcWrite(CHANNEL_MOTOR_FWD3,0);
//         ledcWrite(CHANNEL_MOTOR_REV3,speed);
//     }
// }