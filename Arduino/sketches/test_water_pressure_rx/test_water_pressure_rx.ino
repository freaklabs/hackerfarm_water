#include "chibi.h"

#define MY_ADDR 5

byte buf[20];

typedef struct
{
  float raw;
  float volts;
  float pressure;
} press_t;

void setup() 
{
    chibiInit();
    chibiSetShortAddr(MY_ADDR);
    Serial.begin(57600);
}

void loop() 
{
    if (chibiDataRcvd() == true)
    {
      byte len, rssi;
      if ((len = chibiGetData(buf)) != 0)
      {                
        press_t press;
        memcpy(&press.volts, buf, sizeof(float)*2);
        Serial.print(press.volts); Serial.print(",");
        Serial.println(press.pressure); 
      }
    }
}
