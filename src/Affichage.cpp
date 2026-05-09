#include "Affichage.h"
#include <Types.h>


void dashboard(
    int pos_mot1,
    int pos_mot2,
    int speed,
    bool obstacle,
    int ligne[8],
    Position position,
    Param param
)
{
    // Remet le curseur en haut
    
    Serial.print("\033[2J");
    Serial.print("\033[H");

    Serial.println("===== ROBOT STATUS =====");
    Serial.println();

    Serial.printf("Distance mot1 : %d mm\n", pos_mot1);
    Serial.printf("Distance mot2 : %d mm\n", pos_mot2);
    Serial.printf("Motor speed    : %d\n", speed);
    Serial.printf("Obstacle       : %s\n", obstacle ? "YES" : "NO");

    Serial.println();

    Serial.print("VL53L7 Line : ");

    for(int i = 0; i < 8; i++)
    {
        Serial.printf("%4d ", ligne[i]);
    }

    Serial.println('\n');

    Serial.println("Position Robot");
    Serial.printf("Position x : %.2f mm\n", position.x);
    Serial.printf("Position y : %.2f mm\n", position.y);
    Serial.printf("Angle : %.2f rad\n", position.teta);

    Serial.println();
}