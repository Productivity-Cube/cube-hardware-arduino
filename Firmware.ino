
// Productivity Cube

// Include Libraries
#include "Arduino.h"
#include "Button.h"
#include "RGBLed.h"
#include "CubeClient.h"
#include "SideChecker.h"
#include "conf.h"

// Pin Definitions
#define PUSHBUTTON_1_PIN_2	D3
#define PUSHBUTTON_2_PIN_2	D8
#define PUSHBUTTON_3_PIN_2	D0
#define RGBLED_PIN_R  D5 
#define RGBLED_PIN_G  D7 
#define RGBLED_PIN_B	D6 

// Global variables and defines
#define rgbLed_TYPE COMMON_ANODE
// object initialization
Button pushButton_1(PUSHBUTTON_1_PIN_2);
Button pushButton_2(PUSHBUTTON_2_PIN_2);
Button pushButton_3(PUSHBUTTON_3_PIN_2);
RGBLed rgbLed(RGBLED_PIN_R, RGBLED_PIN_G, RGBLED_PIN_B, rgbLed_TYPE);

const char* ssid   = CONFIG_SSID;
const char* password = CONFIG_PASSWORD; //Enter Password
const String url = CONFIG_URL; //Backend url
const String apiKey = CONFIG_API_KEY; //Backend API KEY

CubeClient cubeClient(ssid, password, url, apiKey);
SideChecker sideChecker(5);

void setup()
{
  sideChecker.init();
  analogWriteRange(254);
  Serial.begin(9600);
  while (!Serial);
  Serial.println("start");

  pushButton_1.init();
  pushButton_2.init();
  pushButton_3.init();
  rgbLed.turnOff();

  rgbLed.setRGB(0,20,0);
  cubeClient.connect();
  
  rgbLed.setRGB(0,0,20);
  delay(1000);
  rgbLed.turnOff();
}


void loop()
{
  sideChecker.getSide();
  if (pushButton_1.onPress() == 1) {
    cubeClient.send();
    rgbLed.setRGB(255,0,0);
    delay(400);
    rgbLed.turnOff();
  }
  if (pushButton_2.onPress() == 1) {
    rgbLed.setRGB(0,255,0);
    delay(400);
    rgbLed.turnOff();
  }
  if (pushButton_3.onPress() == 1) {
    rgbLed.setRGB(0,0, 255);
    delay(400);
    rgbLed.turnOff();
  }
}
