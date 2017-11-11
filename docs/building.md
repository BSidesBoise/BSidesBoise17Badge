Building the Badge
==================

Building the hardware & pin outs
--------------------------------
The NodeMCU can be powered off USB or by battery via the Vin 5v input pin. 
__It's crucial__ that only one power source is connected at a time to prevent 
hardware damage.Below is a simple diagram of the NodeMCU module and its pins 
which are described in more detail in the tables following.

### Key:
* N/C  = Not Connected
* GND  = Ground
* 5v   = 5 Volt power input from battery
* 3.3v = 3.3 Volt power output to peripheral power rails.
* LED  = Output pins connected to the an LED (See LED section below)

<pre>
        ------------
N/C  <- | A0    D0 | -> LED
GND  <- | G     D1 | -> LED
N/C  <- | VU    D2 | -> LED
LED  <- | S3    D3 | -> LED
N/C  <- | S2    D4 | -> LED
N/C  <- | S1    3V | -> 3.3v
N/C  <- | SC     G | -> GND
N/C  <- | S0    D5 | -> LED
N/C  <- | SK    D6 | -> LED
GND  <- | G     D7 | -> LED
3.3v <- | 3V    D8 | -> LED
N/C  <- | EN    RX | -> LED
N/C  <- | RST   TX | -> LED
GND  <- | G      G | -> GND
5v   <- | VIN   3V | -> 3.3v
        ------------
</pre>

### Wiring
For laying wiring the boards, please refer to the wiring diagram images:

https://github.com/BSidesBoise/BSidesBoise17Badge/blob/master/docs/Wiring_Reference_1.jpg

https://github.com/BSidesBoise/BSidesBoise17Badge/blob/master/docs/Wiring_Reference_2.jpg

https://github.com/BSidesBoise/BSidesBoise17Badge/blob/master/docs/Wiring_Reference_3.jpg

__PLEASE READ AND FOLLOW THE FOLLOWING INSTRUCTIONS CAREFULLY__:

1) The board is orientated so that the row numbers go from 1 at the top to 30 at 
   the bottom.

1) The "top" of the NodeMCU is the side with the ESP8266 chip.

1) The NodeMCU shall be placed with the first pin at the top of the board, on 
   the #9 row of the protoboard.

1) You _MUST_ ensure that all wires leave the "a", "b", "i", and "j" columns of 
   the protoboard empty so as to accommodate all NodeMCU's hardware platforms.

1) You _MUST_ ensure that the red LED pin is always the bottom-most (as 
   referenced to the protoboard) pin of the three colors.  This means two of 
   the LEDs on the right, will be in mirror orientation to the two on the left 
   to keep the red LED pointed down.

1) You should clip your LED pins so that the LED will bump up against, or nearly 
   bump up against the top of the project box, when inserted. This will ensure 
   that the LEDs don't work their way out (they will naturally want walk out of 
   the board due to the springy nature of their pins).

1) Please make sure you get the orientation of your diode correct (see above 
   picture)

1) Please hook up the common cathode rail of the LEDs as per the image so that 
   they are all commoned to one GND line on the left side of the board.

1) Please check out the master branch of the repository, then follow the 
   instructions below and compile it for your device (making sure to 
   comment/uncomment the S3 line that is correct for if you have a legit 
   NodeMCU or a Lolin clone), then test each finished board to make sure it 
   lights up correctly.

1) For the most part, the LEDs should be placed at the far extent of the board. 
   The bottom two should be one row up, to make room for the common line 
   connecting the rails on both sides of the board.

Here is the table of wiring directions which will help you, in conjunction with 
the above image:

LED Position | NodeMCU Pin | Protoboard Row | LED Color 
-------------|-------------|----------------|----------
TL           | S3 (SD3)    | 12             | R
TL           | D0          | 9              | G
TL           | D1          | 10             | B
TR           | D2          | 11             | R
TR           | D3          | 12             | G
TR           | D4          | 13             | B
BL           | D5          | 16             | R
BL           | D6          | 17             | G
BL           | D7          | 18             | B
BR           | D8          | 19             | R
BR           | RX          | 20             | G
BR           | TX          | 21             | B

Building the firmware
---------------------
The POC is built using the Arduino IDE using the ESP8266 board libraries.
Docs are located [here.](https://arduino-esp8266.readthedocs.io/en/latest/)

1. Start the Arduino IDE (1.8.4 was used at the time of this writing)
1. Configure the sketchbook 
    * Select File -> Preferences -> settings tab and change the "Sketchbook 
    location" to this repository folder.
1. Add the ESP8266 board
    * Select File -> Preferences -> settings tab and in the "Additional Boards
    Manager URLs" add 
    `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
1. Install the board package
    * Select File -> Board -> Boards Manager and search for "NodeMCU" and select Install
1. Select the correct board
    * Select tools -> Board -> NodeMCU 1.0
1. Upload the firmware
    * Open the [firmware](../firmware/LEDs/LEDs.ino) file using the Arduino IDE
    * Select the "Upload" button to compile and upload the firmware to the 
      NodeMCU
