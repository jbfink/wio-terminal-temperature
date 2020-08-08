#include <Arduino.h>
// Demo code for Grove - Temperature Sensor V1.1/1.2
// Loovee @ 2015-8-26
// note that the temperature sensor must be plugged into the right-hand Grove port.

#include"TFT_eSPI.h"
#include"Free_Fonts.h"
#include <math.h>
#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD
TFT_eSPI tft;

const int B = 4275;               // B value of the thermistor
const int R0 = 100000;            // R0 = 100k
const int pinTempSensor = A0;     // Grove - Temperature Sensor connect to A0
 
#if defined(ARDUINO_ARCH_AVR)
#define debug  Serial
#elif defined(ARDUINO_ARCH_SAMD) ||  defined(ARDUINO_ARCH_SAM)
#define debug  SerialUSB
#else
#define debug  Serial
#endif
float number; 
void setup()
{
    Serial.begin(9600);
  pinMode(WIO_5S_PRESS, INPUT_PULLUP);
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK); //Black background   
  number = 5.12;
}

 
void loop()
{
    tft.setFreeFont(FF10); //select Free, Mono, Oblique, 12pt.
    int a = analogRead(pinTempSensor);
 
    float R = 1023.0/a-1.0;
    R = R0*R;
 
    float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15; // convert to temperature via datasheet
 
    Serial.print("temperature = ");
    Serial.println(temperature);
    tft.drawNumber(temperature,70,80);
    // for some reason drawFloat doesn't work even though it is a float????
    delay(1000);
}