#include <WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         
#include <M5Stack.h>
#include <vector>

using namespace std;

#define TFT_GREY 0x5AEB


template <typename ArgType> void MirrorPrint(ArgType arg)
{
  Serial.print(arg);
  M5.Lcd.print(arg);
}


template <typename ArgType> void MirrorPrintln(ArgType arg)
{
  Serial.println(arg);
  M5.Lcd.println(arg);
}




void eraseConfig()
{
  //Note: WiFi and SPIFFS must have already been started
  WiFi.disconnect(true); 
  M5.Lcd.fillScreen(TFT_GREY);
  M5.Lcd.setCursor(0, 0, 2);
  MirrorPrintln("Erased Wifi info");
  while(1) delay(1000);
}





void setup() {
  Serial.begin(115200);
  M5.begin();

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;

  M5.Lcd.fillScreen(TFT_GREY);
  M5.Lcd.setCursor(0, 0, 2);
  M5.Lcd.setTextColor(TFT_WHITE,TFT_BLACK);  
  M5.Lcd.setTextSize(1);

  MirrorPrintln("If device is not online in a few seconds");
  MirrorPrintln("then connect to SSID: ");
  MirrorPrintln("ESP" + String(ESP_getChipId()));
 
  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point 
  //named after the chip ID
  //and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect()) {
    MirrorPrintln("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.restart();
    delay(5000);
  }

  //if you get here you have connected to the WiFi
  MirrorPrintln("connected to WiFi");
}

void loop() {

  M5.Lcd.fillScreen(TFT_GREY);
  M5.Lcd.setCursor(0, 0, 2);
  MirrorPrint("SSID: ");
  MirrorPrintln(WiFi.SSID());
  MirrorPrint("IP: ");
  MirrorPrintln(WiFi.localIP());
  
  //eraseConfig();
  
  while(1)
  {
    delay(1000);
  }
///////////////////////////////////////////////////////////////////////


}
