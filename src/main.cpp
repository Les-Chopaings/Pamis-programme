 /**
 ******************************************************************************
 * @file    VL53L7CX_HelloWorld.ino
 * @author  STMicroelectronics
 * @version V1.0.0
 * @date    16 January 2023
 * @brief   Arduino test application for STMicroelectronics VL53L7CX
 *          proximity sensor satellite based on FlightSense.
 *          This application makes use of C++ classes obtained from the C
 *          components' drivers.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2021 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/*
 * To use these examples you need to connect the VL53L7CX satellite sensor directly to the Nucleo board with wires as explained below:
 * pin 1 (GND) of the VL53L7CX satellite connected to GND of the Nucleo board
 * pin 2 (IOVDD) of the VL53L7CX satellite connected to 3V3 pin of the Nucleo board
 * pin 3 (AVDD) of the VL53L7CX satellite connected to 5V pin of the Nucleo board
 * pin 4 (PWREN) of the VL53L7CX satellite connected to pin A5 of the Nucleo board
 * pin 5 (LPn) of the VL53L7CX satellite connected to pin A3 of the Nucleo board
 * pin 6 (SCL) of the VL53L7CX satellite connected to pin D15 (SCL) of the Nucleo board
 * pin 7 (SDA) of the VL53L7CX satellite connected to pin D14 (SDA) of the Nucleo board
 * pin 8 (I2C_RST) of the VL53L7CX satellite connected to pin A1 of the Nucleo board
 * pin 9 (INT) of the VL53L7CX satellite connected to pin A2 of the Nucleo board
 */

/* Includes ------------------------------------------------------------------*/
#include <Arduino.h>
#include <Wire.h>
#include <vl53l7cx_class.h>


#ifdef ARDUINO_SAM_DUE
  #define DEV_I2C Wire1
#else
  #define DEV_I2C Wire
#endif
#define SerialPort Serial

#define LPN_PIN A3

#define I2C_RST_PIN A6
#define PWREN_PIN A5

void print_result(VL53L7CX_ResultsData *Result);

// Components.
VL53L7CX sensor_vl53l7cx_top(&DEV_I2C, LPN_PIN, I2C_RST_PIN);

char report[256];
int data[4];

/* Setup ---------------------------------------------------------------------*/
void setup()
{

  // Enable PWREN pin if present
  if (PWREN_PIN >= 0) {
    pinMode(PWREN_PIN, OUTPUT);
    digitalWrite(PWREN_PIN, HIGH);
    delay(10);
  }

  // Initialize serial for output.
  SerialPort.begin(115200);

  // Initialize I2C bus.
  DEV_I2C.begin();

  // Configure VL53L7CX component.
  sensor_vl53l7cx_top.begin();

  sensor_vl53l7cx_top.init_sensor();

  sensor_vl53l7cx_top.vl53l7cx_set_ranging_frequency_hz(60);

  // Start Measurements
  sensor_vl53l7cx_top.vl53l7cx_start_ranging();
}

void loop()
{
  VL53L7CX_ResultsData Results;
  uint8_t NewDataReady = 0;
  uint8_t status;

  do {
    status = sensor_vl53l7cx_top.vl53l7cx_check_data_ready(&NewDataReady);
  } while (!NewDataReady);

  if ((!status) && (NewDataReady != 0)) {
    status = sensor_vl53l7cx_top.vl53l7cx_get_ranging_data(&Results);
    print_result(&Results);
  }

  delay(100);
}

void print_result(VL53L7CX_ResultsData *Result)
{
  int8_t i, j, k, l;

  //SerialPort.print("\n\n");

  for (j = 4; j <= 8; j += 4)
  {
    //SerialPort.print("\n");

    for (l = 0; l < VL53L7CX_NB_TARGET_PER_ZONE; l++)
    {
      for (k = 2; k >= 1; k--)
      {
        if (Result->nb_target_detected[j+k]>0)
        {
          data[2*(j/8) + 2 - k] = (long)Result->distance_mm[(VL53L7CX_NB_TARGET_PER_ZONE * (j+k)) + l];
        }
        else
        {
          data[2*(j/8) + 2 - k] = 0;
        }
      }
    }
  }

//   for (i = 0; i < 4; i++){
//     SerialPort.print("i: ");
//     SerialPort.print(data[i]);
//     SerialPort.print("\n");
//   }
    float minDist = 100000;

    for (int i = 0; i < 4; i++)
    {
        if (data[i] != 0 && data[i] < minDist)
        {
            minDist = data[i];
        }
    }
  //std::sort(data, data+4);
  //SerialPort.print("mediane des valeurs: ");
  SerialPort.println(minDist);

  //SerialPort.print("\n");
}

