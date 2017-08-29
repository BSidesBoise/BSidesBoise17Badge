Building the POC
================

Building the hardware
---------------------
The NodeMCU is powered off USB (at least for the POC)

Wire the NodeMCU to the OLED screen as follows:

| NodeMCU Pin | OLED Pin |
|-------------|----------|
| 3v (any)    | Vdd      |
| GND         | GND      |
| D3          | SDA      |
| D5          | SCL      |

Wire the NodeMCU to the TCL5940 LED driver as follows:

| NodeMCU Pin | OLED Pin |
|-------------|----------|
|             |          |

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
1. 
