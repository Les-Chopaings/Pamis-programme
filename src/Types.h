#ifndef TYPES_H
#define TYPES_H

#include <Arduino.h>

#define DIAMETERWHEELD 2.0
#define DIAMETERWHEELG 2.0
#define DISTANCEWHEEL 4.0
#define NUMBERSTEPBYROTATION 48

struct Position {
    float x = 0.0;
    float y = 0.0;
    float teta = 0.0;
};


#define STEPANGLED \
(((DIAMETERWHEELD) * 180) / ((NUMBERSTEPBYROTATION) * (DISTANCEWHEEL)))

#define STEPANGLEG \
(((DIAMETERWHEELG) * 180) / ((NUMBERSTEPBYROTATION) * (DISTANCEWHEEL)))

#define STEPAVANCED \
(((DIAMETERWHEELD) * (PI)) / ((NUMBERSTEPBYROTATION) * 2))

#define STEPAVANCEG \
(((DIAMETERWHEELG) * (PI)) / ((NUMBERSTEPBYROTATION) * 2))

#define COMPUTE_STEPANGLE(DIAMETER, DISTANCE) \
(((DIAMETER) * 180) / ((NUMBERSTEPBYROTATION) * (DISTANCE)))

#define COMPUTE_STEPAVANCE(DIAMETER) \
(((DIAMETER) * (PI)) / ((NUMBERSTEPBYROTATION) * 2))


struct Param {
    float stepAngleD = COMPUTE_STEPANGLE(DIAMETERWHEELD,DISTANCEWHEEL)*DEG_TO_RAD;
    float stepAngleG = COMPUTE_STEPANGLE(DIAMETERWHEELG,DISTANCEWHEEL)*DEG_TO_RAD;
    float stepForrwardD = COMPUTE_STEPAVANCE(DIAMETERWHEELD);
    float stepForrwardG = COMPUTE_STEPAVANCE(DIAMETERWHEELG);
};


enum Roue {
    LEFT,
    RIGTH
};


struct ObjectifPos
{
    float x;
    float y;

    // Constructeur
    ObjectifPos(float x_init, float y_init)
    {
        x = x_init;
        y = y_init;
    }
};

#endif