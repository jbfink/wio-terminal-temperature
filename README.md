This is a little application for the wonderful bit of hardware from [Seeed](https://www.seeedstudio.com/), the [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html). Using a [Grove temperature sensor](https://wiki.seeedstudio.com/Grove-Temperature_Sensor_V1.2/), this prints out a line graph of the ambient temperature over time. It does this with a non-blocking delay using Arduino's [millis()](https://www.arduino.cc/reference/en/language/functions/time/millis/) function.

To use, acquire both a Wio Terminal and a Grove temperature sensor, plug the temperature sensor in to the *right hand* Grove port (left hand port is I2C specific), load this project in [PlatformIO's](https://platformio.org/) extension for [Visual Studio Code](https://code.visualstudio.com/) and enjoy! You can turn the display on and off by pressing in the joystick.

Note that I made this during a summer heatwave, so the scale is set at a floor of 15C. You can adjust this by setting the value of ```.based_on``` to whatever you'd like. It is set to take a reading every ten minutes and save fifty readings -- you can adjust this by setting ```period``` and ```max_size```.

Things to do or fix:

1) ~~The non-blocking delay unfortunately means the screen won't actually *draw* anything until the first sample is taken at the *end* of the periodicity -- e.g., if you have the timing set for ten minutes, you won't see anything drawn until that first ten minutes has passed.~~ Done! Push the top leftmost button (Button C) to take and plot an immediate sample. Note that the *first* time you do this you will have to press it twice.
2) Wio Terminal has an SD card slot; maybe at the same time that the graph is drawn also write to the card with the elapsed time and temperature.
3) There's *also* built-in Wifi (man, what does the Terminal *not* have? Seriously, this is a great little device) so perhaps use an NTP client to make proper timestamps for the SD log.
4) The Wio Terminal supports [CircuitPython](https://circuitpython.org/board/seeeduino_wio_terminal/)(!!!!!) so maybe reimplement this in CircuitPython sometime.
5) ~~An [Arduino IDE](https://www.arduino.cc/en/Main/Software) specific version.~~ Done! In the arduino-ide directory.

This uses a fair chunk of sample code for the temperature sensor and the line graph - thanks to Seeed for the easy-to-use demos. Everything written by me is licensed under the [MIT License](https://en.wikipedia.org/wiki/MIT_License). Please see LICENSE for details.
