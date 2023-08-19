#include <Arduino.h>

//debug
//define to true to enable debug
#if true

#define DEBUG_BEGIN Serial.begin(9600)
#define DEBUG_WAIT \
  while (!Serial)  \
  {                \
  }
#define DEBUG(x) Serial.println(x)

#else

#define DEBUG_BEGIN
#define DEBUG_WAIT
#define DEBUG(x)

#endif


//pins
#define pinEnable = 2;
#define pinDirecA = 3;
#define pinDirecB = 4;

#define pinLightSensor = A0;
#define pinEndSwitchUp = 7;
#define pinEndSwitchDown = 8;

#define pinButtonUp = 9;
#define pinButtonUpLed = 12;

#define pinButtonCenter = 10;
#define pinButtonCenterRed = 13;
#define pinButtonCenterGreen = 14;
#define pinButtonCenterBlue = 15;

#define pinButtonDown = 11;
#define pinButtonDownLed = 16;


//variables
int LightOpenLevel = 500;
int LightCloseLevel = 900;

int SecurityTimer = 0;
int LightSensorLevel = 0;
word LastOpenClose = 64990;
boolean AddToLOC = 1;

boolean StateButton = 0;
boolean StateEndSwitchUp = 0;
boolean StateEndSwitchDown = 0;
boolean StateBlocking = 0;


void setup()
{
  //set pins mode
  pinMode(pinEnable, OUTPUT);
  pinMode(pinDirecA, OUTPUT);
  pinMode(pinDirecB, OUTPUT);

  pinMode(pinLightSensor, INPUT);
  pinMode(pinEndSwitchUp, INPUT_PULLUP);
  pinMode(pinEndSwitchDown, INPUT_PULLUP);

  pinMode(pinButtonUp, INPUT_PULLUP);
  pinMode(pinButtonUpLed, OUTPUT);

  pinMode(pinButtonCenter, INPUT_PULLUP);
  pinMode(pinButtonCenterRed, OUTPUT);
  pinMode(pinButtonCenterGreen, OUTPUT);
  pinMode(pinButtonCenterBlue, OUTPUT);

  pinMode(pinButtonDown, INPUT_PULLUP);
  pinMode(pinButtonDownLed, OUTPUT);

  //set pins default state
  digitalWrite(pinEnable, LOW);
  digitalWrite(pinDirecA, LOW);
  digitalWrite(pinDirecB, LOW);

  digitalWrite(pinButtonUpLed, LOW);

  digitalWrite(pinButtonCenterRed, LOW);
  digitalWrite(pinButtonCenterGreen, LOW);
  digitalWrite(pinButtonCenterBlue, LOW);

  digitalWrite(pinButtonDownLed, LOW);
}


void loop()
{

}
