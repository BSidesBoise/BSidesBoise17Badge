#include "ESP8266WiFi.h"   
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
// Initialize the OLED display using brzo_i2c
// D3 -> SDA
// D5 -> SCL
// SSD1306Brzo display(0x3c, D3, D5);
// or
// SH1106Brzo  display(0x3c, D3, D5);

// 128X64 pixels screen.

// Initialize the OLED display using Wire library
SSD1306  display(0x3c, D3, D5);

void setup() {
  Serial.begin(115200);

  // Initialising the UI will init the display too.
  display.init();
  display.clear();

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
}
/*
void drawRectDemo() {
      // Draw a pixel at given position
    for (int i = 0; i < 10; i++) {
      display.setPixel(i, i);
      display.setPixel(10 - i, i);
    }
    display.drawRect(12, 12, 20, 20);

    // Fill the rectangle
    display.fillRect(14, 14, 17, 17);

    // Draw a line horizontally
    display.drawHorizontalLine(0, 40, 20);

    // Draw a line horizontally
    display.drawVerticalLine(40, 0, 20);
}
*/
void loop() {
  //Serial.println("scan start");
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  //Serial.println("scan done");

  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10); //We Get 5 lines of 24 characters at this font size

  String output = "";
  
  if (n == 0)
  {
    output = "No networks found";
    //Serial.println("no networks found");
  }
  else
  {
    if(n > 5)
      n = 5;
      
    //Serial.print(n);
    //Serial.println(" networks found");
    
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      //Serial.print(i + 1);
      //Serial.print(": ");
      //Serial.print(WiFi.SSID(i));

      String ssid = WiFi.SSID(i);     
      String data = " (";
      data.concat(WiFi.RSSI(i));
      data.concat(")");
      //Serial.print(" (");
      //Serial.print(WiFi.RSSI(i));
      //Serial.print(")");
      if(WiFi.encryptionType(i) == ENC_TYPE_NONE)
      {  
        //Serial.println("*");
        data.concat(" *");
      }
      else if(WiFi.encryptionType(i) == ENC_TYPE_WEP)
      {
        //Serial.println(" WEP");
        data.concat(" WEP");
      }
      else if(WiFi.encryptionType(i) == ENC_TYPE_TKIP)
      {
        //Serial.println(" TKIP");
        data.concat(" TKIP");
      }
      else if(WiFi.encryptionType(i) == ENC_TYPE_CCMP)
      {
        //Serial.println(" CCMP");
        data.concat(" CCMP");
      }
      else if(WiFi.encryptionType(i) == ENC_TYPE_AUTO)
      {
        //Serial.println(" AUTO");
        data.concat(" AUTO");
      }

      String line = ssid;
      line.concat(data);
      int ssid_size = ssid.length() - 3;
      
      Serial.println(display.getStringWidth(line));
      
      while(display.getStringWidth(line) > 128)
      {  
        ssid_size--;
        Serial.println(ssid_size);
        ssid.remove(ssid_size);
        ssid.concat("...");
        line = ssid;
        line.concat(data);
      }
      
      output.concat(line);
      output.concat("\n");
    }
  }
  
  //Serial.println("");
  display.drawString(0, 0, output);
  display.display();
  delay(1000);
}
