#include "chibi.h"
//#include "saboten.h"

#define VCC 5.0
#define pressOffset 0.400
#define DEST_ADDR 5

#define SCALE_RATIO 290.0

typedef struct
{
  float raw;
  float volts;
  float pressure;
} press_t;

byte buf[20];
int pressSensorPin = A0;

void setup() 
{
//    sab.begin();
    chibiInit();
    Serial.begin(57600); 
}

void loop() 
{
    press_t press;
    press.raw = analogRead(pressSensorPin);   
    press.volts = press.raw * VCC / 1024.0;
    press.pressure = (press.volts - pressOffset) * SCALE_RATIO;   

    memcpy(buf, &press.volts, sizeof(float) *2);
    chibiTx(DEST_ADDR, buf, sizeof(float) * 2);
    
    Serial.print("Voltage:");
    Serial.print(press.volts, 3);
    Serial.print("V, ");
  
    Serial.print("Pressure:");
    Serial.print(press.pressure, 1);
    Serial.println(" KPa");

    delay(500);
}
