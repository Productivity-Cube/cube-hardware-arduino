#include "SideChecker.h"
#include<Wire.h>
#include "Arduino.h"

#define RAD_TO_DEG 57.2957795
int minVal=265;
int maxVal=402;
double x;
double y;
double z;

const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

SideChecker::SideChecker(int numberOfSides) {
  this->numberOfSides = numberOfSides;
}

void SideChecker::init() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

}


int SideChecker::whichBucket(int n) {
    int perSide = (360 / this->numberOfSides) / 2;
    if (355 < n) {
      return 0;
    }
    
    return (n * this->numberOfSides) / 360;
}

int previousSide = 0;
unsigned long timeOfSwitchFromLastSide = 0;
bool wasSwitched = false;
int timeToAcceptSwitchSide = 5000;

int SideChecker::getSide() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);
   
  x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

//  Serial.print(x);
//  Serial.print(",");
//  Serial.print(y);
//  Serial.print(",");
//  Serial.println(z);
   
//  Serial.print("AngleX= ");
//  Serial.println(x);
//   
//  Serial.print("AngleY= ");
//  Serial.println(y);
//   
//  Serial.print("AngleZ= ");
//  Serial.println(z);
//  Serial.println("-----------------------------------------");

  if ((x > 70 && x < 100) || (x > 230 && x < 290)) {
    return this->numberOfSides;
  }

  delay(100);
  return whichBucket(y);
}

int SideChecker::getChangedSide() {
  int side = getSide();

  if (side != previousSide) {
    timeOfSwitchFromLastSide = millis();
    previousSide = side;
    wasSwitched = false;
  }

  if (millis() - timeOfSwitchFromLastSide > timeToAcceptSwitchSide && !wasSwitched) {
    timeOfSwitchFromLastSide = -1;
    wasSwitched = true;

    return side;
  }

  return -1;
}
