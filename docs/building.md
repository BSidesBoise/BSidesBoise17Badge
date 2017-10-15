Building the POC
================

Building the hardware & pin outs
-------------------------------
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

### LEDs
The following LED's are abbreviated as top or bottom, followed by left or right, 
then the color. For example, TLR would mean "Top Left Red".

Wire the NodeMCU to the LEDs as follows:

| LED | NodeMCU Pin |
|-----|-------------|
| TLR | S3          |
| TLG | D0          |
| TLB | D1          |
| TRR | D2          |
| TRG | D3          |
| TRB | D4          |
| BLR | D5          |
| BLG | D6          |
| BLB | D7          |
| BRR | D8          |
| BRG | RX          |
| BRB | TX          |

Building the firmware
---------------------
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
1. Upload the firmware
    * Open the [firmware](../firmware/LEDs/LEDs.ino) file using the Arduino IDE
    * Select the "Upload" button to compile and upload the firmware to the 
      NodeMCU
    * Note that the LED connected to D8 (Bottom Right) must be removed prior to
      programming.
