
// Productivity Cube

// Include Libraries
#include "Arduino.h"
#include "Button.h"
#include "RGBLed.h"
#include "CubeClient.h"


// Pin Definitions
#define PUSHBUTTON_1_PIN_2	D2 // D2
#define PUSHBUTTON_2_PIN_2	D0 // D3
#define PUSHBUTTON_3_PIN_2	D1 // D4
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


const char* ssid   = "***"; //Enter SSID
const char* password = "***"; //Enter Password

CubeClient cubeClient(ssid, password);

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup()
{
  analogWriteRange(254);
  // Setup Serial which is useful for debugging
  // Use the Serial Monitor to view printed messages
  Serial.begin(9600);
  while (!Serial) ; // wait for serial port to connect. Needed for native USB
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

  if (pushButton_1.read() == 1) {
    rgbLed.setRGB(255,0,0);
    delay(1000);
    rgbLed.turnOff();
  }
  if (pushButton_2.read() == 1) {    
    rgbLed.setRGB(0,255,0);
    delay(1000);
    rgbLed.turnOff();
  }

  if (pushButton_3.read() == 1) {
    rgbLed.setRGB(0, 0, 255);
    delay(1000);
    rgbLed.turnOff();
    
  }

}
