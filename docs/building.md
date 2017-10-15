Building the POC
================

Building the hardware & pinouts
-------------------------------
The NodeMCU is powered off USB (at least for the POC) or by the Vin 5v input 
pin. Below is a simple diagram of the NodeMCU module and its pins which are
described in more detail in the tables following.

### Key:
* N/C  = Not Connected
* GND  = Ground
* 5v   = 5 Volt power input from battery
* 3.3v = 3.3 Volt power output to peripheral power rails.
* BTN  = Input pins connected to a user button (See button section below)
* SRN  = Output pins connected to OLED screen. (See OLED Screen section below)
* TLC  = Output pins connected to the LED Driver (See TLC5940 LED section below)

<pre>
        ------------
N/C  <- | A0    D0 | -> N/C
GND  <- | G     D1 | -> BTN
N/C  <- | VU    D2 | -> BTN
BTN  <- | S3    D3 | -> SRN
BTN  <- | S2    D4 | -> BTN
N/C  <- | S1    3V | -> 3.3v
N/C  <- | SC     G | -> GND
N/C  <- | S0    D5 | -> SRN
N/C  <- | SK    D6 | -> TLC
GND  <- | G     D7 | -> TLC
3.3v <- | 3V    D8 | -> TLC
N/C  <- | EN    RX | -> TLC
N/C  <- | RST   TX | -> TLC
GND  <- | G      G | -> GND
5v   <- | VIN   3V | -> 3.3v
        ------------
</pre>

For laying wiring the boards, please refer to the wiring diagram images:

https://gitlab.com/BSidesBoise/BSides_2017_Badge/blob/master/docs/Wiring_Reference_1.jpg

https://gitlab.com/BSidesBoise/BSides_2017_Badge/blob/master/docs/Wiring_Reference_2.jpg

https://gitlab.com/BSidesBoise/BSides_2017_Badge/blob/master/docs/Wiring_Reference_3.jpg


PLEASE READ AND FOLLOW THE FOLLOWING INSTRUCTIONS CAREFULLY:

1) The board is orientated so that the row numbers go from 1 at the top to 30 at the bottom.

2) The "top" of the NodeMCU is the side with the ESP8266 chip.

3) The NodeMCU shall be placed with the first pin at the top of the board, on the #9 row of the protoboard.

4) You MUST ensure that all wires leave the "a", "b", "i", and "j" columns of the protoboard empty so as to accomodate both the legit NodeMCU's and the Lolin clones.

5) You MUST ensure that the red LED pin is always the bottom-most (as referenced to the protoboard) pin of the three colors.  This means two of the LEDs on the right, will be in mirror orientation to the two on the left to keep the red LED pointed down.

6) You should clip your LED pins so that the LED will bump up against, or nearly bump up against the top of the project box, when inserted. This will ensure that the LEDs don't work their way out (they will naturally want walk out of the board due to the springy nature of their pins).

7) Please make sure you get the orientation of your diode correct (see above picture)

8) Please hook up the common cathode rail of the LEDs as per the image so that they are all commoned to one GND line on the left side of the board.

9) Please check out Justin's branch of code, and compile it for your device (making sure to comment/uncomment the S3 line that is correct for if you have a legit NodeMCU or a Lolin clone), then test each finished board to make sure it lights up correctly.

10) For the most part, the LEDs should be placed at the far extent of the board. The bottom two should be one row up, to make room for the common line connecting the rails on both sides of the board.


Here is the table of wiring directions which will help you, in conjunction with the above image:

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

As you complete wiring of boards, please update this spreadsheet: https://docs.google.com/spreadsheets/d/1iOaclNGcpSUEgD6lBblX5JUO6b4hM3gnfDJPsdBYcac/edit?usp=sharing


