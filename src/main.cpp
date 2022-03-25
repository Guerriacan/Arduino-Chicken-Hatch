#include <Arduino.h>

/*
  =======================================
  ==  Project name : Trappe Poule V2   ==
  ==        Author : Guerriacan        ==
  ==   Last Update : 19/10/2020 19:00  ==
  =======================================
*/

//====== ENABLE OR DISABLE DEBUG ======
//=====================================
#define DISABLE_DEBUG
//=====================================
//====== ENABLE OR DISABLE DEBUG ======

//============== DEBUG ================
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
//============== DEBUG ================

//============== PINOUT ===============
const byte PinEnable = 2;
const byte PinDirecA = 3;
const byte PinDirecB = 4;

const byte PinLightSensor = A0;
const byte PinButton = 6;
const byte PinEndSwitchUp = 7;
const byte PinEndSwitchDown = 8;
const byte PinBlocking = 9;
//============== PINOUT ===============

//============ VARIABLES ==============
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
//============ VARIABLES ==============

void stop()
{
  digitalWrite(PinEnable, LOW);
  delay(10);
  digitalWrite(PinDirecA, HIGH);
  digitalWrite(PinDirecB, LOW);
}

void run(bool way)
{
  if (way == 0)
  {
    digitalWrite(PinDirecA, LOW);
    digitalWrite(PinDirecB, HIGH);
    delay(10);
    digitalWrite(PinEnable, HIGH);
  }
  else
  {
    digitalWrite(PinDirecA, HIGH);
    digitalWrite(PinDirecB, LOW);
    delay(10);
    digitalWrite(PinEnable, HIGH);
  }
}

void setup()
{

  //============= PINMODE ===============
  pinMode(PinEnable, OUTPUT);
  pinMode(PinDirecA, OUTPUT);
  pinMode(PinDirecB, OUTPUT);

  pinMode(PinLightSensor, INPUT);

  pinMode(PinButton, INPUT_PULLUP);
  pinMode(PinEndSwitchUp, INPUT_PULLUP);
  pinMode(PinEndSwitchDown, INPUT_PULLUP);
  pinMode(PinBlocking, INPUT);
  //============= PINMODE ===============

  //============== DEBUG ================
  DEBUG_BEGIN;
  DEBUG_WAIT;

  DEBUG("=========================================");
  DEBUG("============ CONEXION ETABLIE ===========");
  DEBUG("========= TRAPPE OPERATIONNELLE =========");
  DEBUG("=========================================");
  DEBUG("");
  //============== DEBUG ================
}

//============== LOOP =================
void loop()
{
  DEBUG("============= DEBUT DE LOOP =============");
  DEBUG("=============  Variables :  =============");
  // LightSensorLevel = analogRead(PinLightSensor);
  DEBUG(LightSensorLevel);
  DEBUG(LastOpenClose);
  DEBUG("=========================================");
  CheckBlocking();
  Reset();
  DEBUG("============== FIN DE LOOP ==============");
  DEBUG("");
  DEBUG("");
  delay(5);
  if (AddToLOC == 1)
  {
    LastOpenClose++;
  }
}
//============== LOOP =================