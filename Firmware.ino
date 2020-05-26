
// Productivity Cube

// Include Libraries
#include "Arduino.h"
#include "Button.h"
#include "RGBLed.h"
#include "CubeClient.h"
#include "SideChecker.h"
#include "conf.h"

// Pin Definitions
#define PUSHBUTTON_1_PIN_2	D0
#define PUSHBUTTON_2_PIN_2	D3
#define PUSHBUTTON_3_PIN_2	D8
#define RGBLED_PIN_R  D7
#define RGBLED_PIN_G  D6
#define RGBLED_PIN_B	D5

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

  rgbLed.setRGB(20, 0, 0);
  cubeClient.connect();

  rgbLed.setRGB(0, 20, 0);
  delay(1000);
  rgbLed.turnOff();
}


void loop()
{
  int side = sideChecker.getChangedSide();
  double prediction = 0;
  if (side != -1) {
    Serial.print("Side:");
    Serial.println(side);
    prediction = cubeClient.send(sideChecker.getSide(), NULL);
  }

  if (pushButton_1.onPress() == 1) {
    prediction = cubeClient.send(sideChecker.getSide(), 2);
  }
  if (pushButton_2.onPress() == 1) {
    prediction = cubeClient.send(sideChecker.getSide(), 3);
  }
  if (pushButton_3.onPress() == 1) {
    prediction = cubeClient.send(sideChecker.getSide(), 1);
  }

  // LED
  if (prediction > 0) {
    Serial.println(prediction);
    if (prediction <= 1.6) {
      rgbLed.setRGB(100, 0, 0);
    } else if (prediction <= 2.5) {
      rgbLed.setRGB(0, 0, 100);
    } else {
      rgbLed.setRGB(0, 100, 0);
    }
    delay (5000);
    rgbLed.turnOff();
  }
}
