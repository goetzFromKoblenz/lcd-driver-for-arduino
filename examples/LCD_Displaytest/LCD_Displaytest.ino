/*
    Name:       LCD_Displaytest.ino
    Created:	03.03.2019 17:07:36
    Author:     Goetz Hasselberg
	Simple display demo
*/

#include <LcdDisplay.h>

/* use this constructor if you have your display connected to D0..D5 of an ESP board */
// lcdDisplay myLcdDisplay; 

/* use this constructor to set port pins according to your own hardware
   you may use the appropriate port pin names your target supports */
lcdDisplay myLcdDisplay(16,5,4,0,2,14); // (DB4..DB7, E, RS);

// The setup() function runs once each time the micro-controller starts
void setup()
{
	Serial.begin(115200); // for debug output
	Serial.println("LCD display demo");

	myLcdDisplay.begin();

	char test1[20];
	sprintf(test1, "Line number%2d", 1);

	String test2("Line number 2");
	myLcdDisplay.writeStringAtPos(test1, 0, 0);
	myLcdDisplay.writeStringAtPos(test2, 1, 0);
	myLcdDisplay.writeStringAtPos("Line number 3", 2, 0);
	myLcdDisplay.writeStringAtPos("Line number 4", 3, 0);
	delay(4000); // just stop here for a while before the main loop clears the display
}

// Add the main program code into the continuous loop() function
void loop()
{
	delay(1000);
	myLcdDisplay.clear();
	for (int i = 0; i < 10; i++)
	{
		myLcdDisplay.sendData(0x30 + i);
		delay(1000);
	}
}

