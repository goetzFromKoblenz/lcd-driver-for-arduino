/**
 * @file LcdDisplay.h
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

#include <arduino.h>



#ifndef LCDDISPLAY_H_
#define LCDDISPLAY_H_

class lcdDisplay
{
public:
	lcdDisplay();
	lcdDisplay(uint8_t DB4, uint8_t DB5, uint8_t DB6, uint8_t DB7, uint8_t E, uint8_t RS);
	void begin();
	void writeString(String outputString);
	void writeStringAtPos(String outputString, uint8_t row, uint8_t column);
	void sendData(uint8_t byteToSend);
	void sendCmd(uint8_t byteToSend);
	void clear();


private:
	void nibble(uint8_t byteToSend, bool isData);
	uint8_t LCD_DB4;
	uint8_t LCD_DB5;
	uint8_t LCD_DB6;
	uint8_t LCD_DB7;
	uint8_t LCD_E;
	uint8_t LCD_RS;
};

#endif /* LCDDISPLAY_H_ */
