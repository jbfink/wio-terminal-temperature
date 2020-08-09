#include <Arduino.h>
// Demo code for Grove - Temperature Sensor V1.1/1.2
// Loovee @ 2015-8-26
// note that the temperature sensor must be plugged into the right-hand Grove port on the Wio Terminal.

#include"TFT_eSPI.h"
#include"Free_Fonts.h"
#include <math.h>
#include"seeed_line_chart.h" 
#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD
TFT_eSPI tft;
#define max_size 50 //maximum size of data
doubles data; //Initilising a doubles type to store data
TFT_eSprite spr = TFT_eSprite(&tft);  // Sprite 

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
void setup()
{
    Serial.begin(9600);
    pinMode(WIO_5S_PRESS, INPUT_PULLUP);
    tft.begin();
    tft.setRotation(3);
    spr.createSprite(TFT_HEIGHT, TFT_WIDTH);
    //tft.fillScreen(TFT_BLACK); //Black background   
}


void loop()
{
    // setting up thermometer
    int a = analogRead(pinTempSensor);
    float R = 1023.0/a-1.0;
    R = R0*R;
    float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15; // convert to temperature via datasheet
// 
    spr.fillSprite(TFT_WHITE);
    if (data.size() == max_size) {
        data.pop();//this is used to remove the first read variable
    }
    data.push(temperature); // put temperature in data stack

    //Settings for the line graph title
    auto header =  text(0, 0)
        .value("temp in C")
        .align(center)
        .valign(vcenter)
        .width(tft.width())
        .thickness(3);

    header.height(header.font_height() * 2);
    header.draw(); //Header height is the twice the height of the font

  //Settings for the line graph
    auto content = line_chart(20, header.height()); //(x,y) where the line graph begins
    content
        .height(tft.height() - header.height() * 1.5) //actual height of the line chart
        .width(tft.width() - content.x() * 2) //actual width of the line chart
        .based_on(0.0) //Starting point of y-axis, must be a float
        .show_circle(false) //drawing a cirle at each point, default is on.
        .value(data) //passing through the data to line graph
        .color(TFT_PURPLE) //Setting the color for the line
        .draw();

    spr.pushSprite(0, 0);
    //delay(1000);
    delay(600000);

}
