/**
 * @file LcdDisplay.cpp
 * @date 03.03.2019
 * @author Goetz Hasselberg
 *
 * Copyright (c) 2019 Goetz Hasselberg. All rights reserved.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "LcdDisplay.h"

/* the default contructor provides pre-settings for esp8266/nodemcu boards
	D0 = GPIO 16 -> LCD DB4
	D1 = GPIO 5  -> LCD DB5
	D2 = GPIO 4  -> LCD DB6
	D3 = GPIO 0  -> LCD DB7
	D4 = GPIO 2  -> LCD E
	D5 = GPIO 14 -> LCD RS
	connect LCD R/W to GND
	leave LCD D0..D3 open
*/

lcdDisplay::lcdDisplay() : LCD_DB4(16), LCD_DB5(5), LCD_DB6(4), LCD_DB7(0), LCD_E(2), LCD_RS(14)
{
}

/* parameterized contructor for any other combination of port pins */
lcdDisplay::lcdDisplay(uint8_t DB4, uint8_t DB5, uint8_t DB6, uint8_t DB7, uint8_t E, uint8_t RS)
{
	LCD_DB4 = DB4;
	LCD_DB5 = DB5;
	LCD_DB6 = DB6;
	LCD_DB7 = DB7;
	LCD_E   = E;
	LCD_RS  = RS;
}

/* internal function to support 4-bit mode */
void lcdDisplay::nibble(uint8_t byteToSend, bool isData) // lower part of data byte RS = 0 -> cmd, RS = 1 -> data
{
	digitalWrite(LCD_DB4, (byteToSend >> 0) & 1);
	digitalWrite(LCD_DB5, (byteToSend >> 1) & 1);
	digitalWrite(LCD_DB6, (byteToSend >> 2) & 1);
	digitalWrite(LCD_DB7, (byteToSend >> 3) & 1);
	digitalWrite(LCD_RS, isData & 1);
	digitalWrite(LCD_E, HIGH);
	digitalWrite(LCD_E, LOW);
}

/* send a data byte (a character) to the display */
void lcdDisplay::sendData(uint8_t byteToSend)
{
	nibble(byteToSend >> 4, 1);
	nibble(byteToSend, 1);
	delayMicroseconds(50);
}

/* send a command to the display */
void lcdDisplay::sendCmd(uint8_t byteToSend)
{
	nibble(byteToSend >> 4, 0);
	nibble(byteToSend, 0);
	delay(2);
}

void lcdDisplay::clear()
{
	sendCmd(1);
}

/* initialization routine */
void lcdDisplay::begin()
{
	// wait till power for LCD display is up
	delay(30);

	// preset the port pins used
	pinMode(LCD_DB4, OUTPUT);
	pinMode(LCD_DB5, OUTPUT);
	pinMode(LCD_DB6, OUTPUT);
	pinMode(LCD_DB7, OUTPUT);
	pinMode(LCD_E, OUTPUT);
	pinMode(LCD_RS, OUTPUT);

	// set latch pin to incative state
	digitalWrite(LCD_E, LOW);

	// the good old sequence still works
	sendCmd(0x28);

	// display on
	sendCmd(0x0C);

	// entry mode
	sendCmd(0x06);

	// clear/home
	clear();
}

/* write characters at current position (may not fit into a single line) */
void lcdDisplay::writeString(String outputString)
{
	for (int i = 0; i < outputString.length(); i++)
	{
		sendData(outputString[i]);
	}
}

/* write characters to a certain position of a certain line 
   row can be 0..3 depending on the display
   column can be 0 to 39 also depending on the display 
*/
void lcdDisplay::writeStringAtPos(String outputString, uint8_t row, uint8_t column)
{
	
	// for the 4*20 character display, the starting positions are 0x80,0xC0,0x94,0xD4
	// calculate row offset
	uint8_t bufferPos = 0x80 + ((row & 1) * 0x40) + ((row & 2) * 0x0A);

	bufferPos += (column % 0x14);
	sendCmd(bufferPos);
	writeString(outputString);
}


