#ifndef _CUBECLIENT_H_
#define _CUBECLIENT_H_

#include <Arduino.h>
//button  class:
class CubeClient {
  public:
    CubeClient(const char* ssid, const char* password, String url_, String apiKey_);
    void connect();
    double send(int side, int productivityRate);
    
  private:
    const char* ssid;
    const char* password;
    const String url;
    const String apiKey;
};

#endif //_CUBECLIENT_H_
