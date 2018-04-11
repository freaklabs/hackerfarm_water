#include "chibi.h"
#define MY_ADDR 5

byte buf[20];

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
        uint16_t level;
        memcpy(&level, buf, sizeof(uint16_t));
        Serial.println(level);
      }
    }

}
