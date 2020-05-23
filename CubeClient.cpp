#include "CubeClient.h"

#include <Arduino.h>
#include "ESP8266WiFi.h"

CubeClient::CubeClient(const char* ssid_, const char* password_) : ssid(ssid_), password(password_)
{

}

void CubeClient::connect() {
  // wifi

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(500);
     Serial.print("*");
  }
  
  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.print(WiFi.localIP());// Print the IP address
}
