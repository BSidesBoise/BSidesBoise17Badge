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

### OLED Screen

Wire the NodeMCU to the OLED screen as follows:

| NodeMCU Pin | ESP8266 Pin | OLED Pin |
|-------------|-------------|----------|
| 3.3v        | 3.3v (any)  | Vdd      |
| GND         | GND         | GND      |
| D3          | GPIO0/Flash | SDA      |
| D5          | GPIO14/HSCLK| SCL      |

### TLC5940 LED Driver

Wire the NodeMCU to the TCL5940 LED driver as follows:

| NodeMCU Pin | ESP8266 Pin | TLC5940 Pin |
|-------------|-------------|-------------|
| D10         | GPIO1       | 26 (SIN)    |
| D9          | GPIO3       | 25 (SCLK)   |
| D8          | GPIO15      | 24 (XLAT)   |
| D7          | GPIO13      | 23 (BLANK)  |
| D6          | GPIO12      | 18 (GSCLK)  |

Wire the TLC5940 to LED's as follows:

| TLC5940 | LED |
|---------|-----|
|1 (OUT1) | 0 B |
|2 (OUT2) | 0 G |
|3 (OUT3) | 0 R |
|4 (OUT4) | 1 B |
|5 (OUT5) | 1 G |
|6 (OUT6) | 1 R |
|7 (OUT7) | 2 B |
|8 (OUT8) | 2 G |
|9 (OUT9) | 2 R |
|10(OUT10)| 3 B |
|11(OUT11)| 3 G |
|12(OUT12)| 3 R |
|13(OUT13)| 4 B |
|14(OUT14)| 4 G |
|15(OUT15)| 4 R |

Wire the remaining TLC5940 pins as follows (N/C == Not Connected). Pins that are
described in earlier sections are omitted from this table.

| TLC5940 | PWR/GND |
|---------|---------|
|16(XERR) | N/C     |
|17(SOUT) | N/C     |
|19(DCPRG)| 3.3v    |
|20(IREF) | 2k->GND | <- Determines current through all LED's. See note below.
|21(VCC)  | 3.3v    |
|22(GND)  | GND     |
|27(VPRG) | GND     |
|28(OUT0) | N/C     |

Note for IREF:
The IREF resistor value is what determines how much current is pumped through
all LED's connected to the TLC5940 when running at maximum. To set this value, 
follow the formula:
I =  (1.24/R)*31.5
where I is the max current through the LED's and R is the resistor value set. 
For example, if R == 2k, we'd get a max current of 19.53mA.

### Input Buttons

The badge will have 5 input buttons. Each button shall utilize the internal
pull-up resistors within the NodeMCU, so the following GPIO's should be 
connected to one side of the buttons, with the other side connected to ground.

| NodeMCU Pin | ESP8266 Pin |
|-------------|-------------|
| D1          | GPIO5       |
| D2          | GPIO4       |
| D4          | GPIO2       |
| S3          | GPIO10      |
| S2          | GPIO9       |

Building the firmware
---------------------
NOT COMPLETE YET

The POC is built using the Arduino IDE using the ESP8266 board libraries.
Docs are located [here.](https://arduino-esp8266.readthedocs.io/en/latest/)

1. Start the Arduino IDE (1.8.4 was used at the time of this writing)
1. Configure the sketchbook for the poc folder. 
    * Select File -> Preferences -> settings tab and change the "Sketchbook 
    location" to this poc folder.
1. Add the ESP8266 board
    * Select File -> Preferences -> settings tab and in the "Additional Boards
    Manager URLs" add 
    `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
1. Select the correct board
    * Select tools -> Board -> NodeMCU 1.0
1. 
