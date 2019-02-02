#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <WiFiManager.h>         
#include <vector>
#include <sstream>
#include <iomanip>
#include <Adafruit_GFX.h>                                  // Core graphics library
#include <Adafruit_ST7735.h>                               // Hardware-specific library
Adafruit_ST7735 tft = Adafruit_ST7735(16, 17, 23, 5, 9); // CS,A0,SDA,SCK,RESET


using namespace std;

#define TFT_GREY 0x5AEB


template <typename ArgType> void MirrorPrint(ArgType arg)
{
  Serial.print(arg);
  tft.print(arg);
}


template <typename ArgType> void MirrorPrintln(ArgType arg)
{
  Serial.println(arg);
  tft.println(arg);
}




void eraseConfig()
{
  //Note: WiFi and SPIFFS must have already been started
  WiFi.disconnect(true); 
  tft.fillScreen(TFT_GREY);
  tft.setCursor(0, 0);
  tft.setTextSize(2);
  MirrorPrintln("Erased Wifi info");
  while(1) delay(1000);
}





void setup() {
  Serial.begin(115200);

  tft.initR(INITR_18GREENTAB);                             // 1.44 v2.1
  tft.fillScreen(ST7735_BLACK);                            // CLEAR
  tft.setTextColor(0x5FCC);                                // GREEN
  tft.setRotation(1);                                      // 

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;

  //eraseConfig();

  

  MirrorPrintln("If device is not online in a few seconds");
  MirrorPrintln("then connect to SSID: ");

  stringstream as;
  as << "ESP" << hex << ESP.getEfuseMac();
  
  String auto_ssid(as.str().c_str());
  MirrorPrintln(auto_ssid);
  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point 
  //named after the chip ID
  //and goes into a blocking loop awaiting configuration
  wifiManager.setConnectTimeout(6);
  if (!wifiManager.autoConnect(auto_ssid.c_str())) {
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
