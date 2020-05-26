#include "CubeClient.h"

#include <Arduino.h>
#include "ESP8266WiFi.h"
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

CubeClient::CubeClient(
  const char* ssid_,
  const char* password_,
  String url_,
  String apiKey_
  ) : ssid(ssid_), password(password_), url(url_), apiKey(apiKey_)
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

double CubeClient::send(int side, int productivityRate) {
  String activity = "Off";
  switch (side) {
    case 0: 
      activity = "Call"; break;
    case 1: 
      activity = "Break"; break;
    case 2: 
      activity = "Meeting"; break;
    case 3: 
      activity = "Planning"; break;
    case 4: 
      activity = "Work"; break;
  }
  HTTPClient http;
  http.begin(url + "/api/events");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + apiKey);
  String payloadBody = "{\"user\": \"papipl\",\"activity\": \"" + activity + "\"" + (productivityRate == NULL ? "" : (",\"productivityRate\":" + String(productivityRate)))+"}";
  Serial.println(payloadBody);
  int httpCode = http.POST(payloadBody);
  Serial.println(httpCode);
  String payload = http.getString();
  Serial.println(payload);

  DynamicJsonDocument doc(1024);
  deserializeJson(doc, payload);

  double productivityPrediction = doc["productivityPrediction"]["prediction"];

  http.end();

  return productivityPrediction;
}
