# lcd-driver-for-arduino
Simple 6 wire HD44780 LCD driver library for ESP8266 or Arduino

For a small project using ESP-12E (NodeMcu) I needed an LCD display.
I had some of those displays around an also had written such code for 8031 and ATtiny before, so I decided to write a handy little class for it.

I know there are other projects around like this but usually they use I2C expanders or shift registers to save port pins.
My project did not need to many port pins because I was reading some I2C sensors, so I had a bunch of them left.

So, this driver needs no external hardware but uses 6 port pins.
You can use any combination of output pins you like, five of them can be shared with other functions such as I2C as long 
as they are used sequentially (not interrupt-driven).

This library provides the driver as a (C++) class.
Its member functions are
- 2 constructors (one uses default portpins D0..D5 for ESP/NodeMcu, the other one uses a parameter list to select the port pins)
- begin : initializes the module
- writeString : writes a character string to the current position on the display. 
  Works with char arrays (easy formatting using sprintf) and String types
- writeStringAtPos : writes a character string to a certain position in a certain display line
- clear : erases the display content

Two more low level functions
- sendData : writes a single character to the current position of the display (see display manual for character code table)
- sendCmd : sends a command character to the display (see display manual for such commands)

# concept
- The driver uses the 4-bit mode. It does not read the busy signal from the display, 
  it uses simple delays to give the display time to react to the commands. Therefore R/W of the display has to be tied to GND.
  This saves some code and one port pin.
- The driver uses incremental write, so every time a character is written, the (invisible) cursor advances to the next character.
  
# 5V display with 3.3V controller boards  
- Most displays are capable of being operated on 3.3V or less, but usually they need a negative voltage for 
  the display contrast in that case. Have a look at the data sheet of your display and see if it accepts input voltages below 3V as high level. 
  You may find this information under electrical characteristics or in the timing diagram for write operation. 
  If so, you can do the following:
  - power the display with 5V (with no Arduino/ESP hardware connected).
  - the voltage at the open inputs (DB4..DB7, E and RS) should be a little less than 5V.
  - connect a resistor of 10k between one of the input pins and GND and measure the voltage again. 
    The voltage at the input, let's call it U2, should be much less than 5V now.
  - use the formula R1 = ((5V - U2) * 10k) / U2 to determine the display's internal input pull-up resistor R1.
  - get a resistor of approx. 2.94 * R1 (next lower usual value) from your resistor collection, connect it one of the inputs and measure the voltage again. 
    Now it should be a little less than 3.3V. In my case 39k was the right value for a blue chinese 4 line display.
  - add a pull-down resistor of the calculated value to each of the 6 display inputs, measure again and now you should be
    ready to safely connect your arduino/ESP board.
  The display now still runs on 5V (supply voltage / contrast / backlight) according to the standard application.
  The controller (arduino/ESP) is running on 3.3V as usual!
  

