#include <Arduino.h>
#include <seeed_graphics_base.h>
#include <seeed_line_chart.h>
#include <seeed_graphics_define.h>
// Code adapted from Seeed's Grove Temperature Demo (https://wiki.seeedstudio.com/Grove-Temperature_Sensor_V1.2/) and Linechart (https://github.com/Seeed-Studio/Seeed_Arduino_Linechart)

// note that the temperature sensor must be plugged into the right-hand Grove port on the Wio Terminal.

#include"TFT_eSPI.h"
#include <math.h>
#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD
TFT_eSPI tft;
#define max_size 50 //maximum size of data
doubles data; // initialising a doubles type to store data
TFT_eSprite spr = TFT_eSprite(&tft);  // Sprite 

const int B = 4275;               // B value of the thermistor
const int R0 = 100000;            // R0 = 100k
const int pinTempSensor = A0;     // Grove - Temperature Sensor connect to A0


// For non-blocking delay: https://dzone.com/articles/arduino-using-millis-instead-of-delay
//int period = 600000;
int period = 1000;
unsigned long time_now = 0;

void displayTemp() {
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
        .based_on(15.0) //Starting point of y-axis, must be a float. Set to 15C in summer. :D
        .show_circle(true) //drawing a cirle at each point, default is on.
        .value(data) //passing through the data to line graph
        .color(TFT_PURPLE) //Setting the color for the line
        .draw();

    spr.pushSprite(0, 0);
}

void setup()
{
    pinMode(WIO_5S_PRESS, INPUT_PULLUP);
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    tft.begin();
    tft.setRotation(3);
    spr.createSprite(TFT_HEIGHT, TFT_WIDTH);
}


void loop()
{
    if (millis() > time_now + period) {
        time_now = millis();
        displayTemp();

    }
    int currentState = digitalRead(LCD_BACKLIGHT);
    if (digitalRead(WIO_5S_PRESS) == LOW) {
        if (currentState == 0) {
            digitalWrite(LCD_BACKLIGHT, HIGH);
        }
        else if (currentState == 1) {
            digitalWrite(LCD_BACKLIGHT, LOW);
        }
    }
    delay(100); // for debouncing
}
