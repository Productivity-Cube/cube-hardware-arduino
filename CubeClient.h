#ifndef _CUBECLIENT_H_
#define _CUBECLIENT_H_


//button  class:
class CubeClient {
  public:
    CubeClient(const char* ssid, const char* password);
    void connect();
    
  private:
    const char* ssid;
    const char* password;
};

#endif //_CUBECLIENT_H_
