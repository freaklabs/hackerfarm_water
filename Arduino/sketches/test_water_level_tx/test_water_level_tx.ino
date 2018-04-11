#include "chibi.h"
#include "saboten.h"

#define VCC 3.3
#define DEST_ADDR 5

byte buf[20];
int pinLevelSensor = A0;
int pinLevelEnb = A3;

void setup() 
{
    pinMode(pinLevelEnb, OUTPUT);
    digitalWrite(pinLevelEnb, HIGH);
  
    sab.begin();
    chibiInit();
    Serial.begin(57600); 
    Serial.println("2018-02-28 Level Sensor Tx v1.0");
}

void loop() 
{
  
    uint16_t level;

    // average level readings over 10 readings
    float raw = analogRead(pinLevelSensor) * 5.004;
    level = round(raw);
    
    memcpy(buf, &level, sizeof(uint16_t));
    chibiTx(DEST_ADDR, buf, sizeof(uint16_t));

    Serial.print("Raw: "); 
    Serial.print(raw, 3);
    Serial.print(", Level:");
    Serial.print(level);
    Serial.println(" mm");

    delay(500);
}
