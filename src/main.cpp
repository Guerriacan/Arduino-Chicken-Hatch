#include <Arduino.h>
#include <EEPROM.h>
#include <OneButton.h>
#include <TimerOne.h>
#include <arduino-timer.h>

//pins
#define pinEnable 2
#define pinDirecA 3
#define pinDirecB 4

#define pinLightSensor A0
#define pinEndSwitchUp 7
#define pinEndSwitchDown 8

#define pinButtonUp 9
#define pinLedUp 12

#define pinButtonCenter 10
#define pinLedCenterRed 0
#define pinLedCenterGreen 13
#define pinLedCenterBlue 15

#define pinButtonDown 11
#define pinLedDown 16


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

//setup buttons
OneButton buttonUp(pinButtonUp, true, true);
OneButton buttonCenter(pinButtonCenter, true, true);
OneButton buttonDown(pinButtonDown, true, true);

void buttonsTick() {
  buttonUp.tick();
  buttonCenter.tick();
  buttonDown.tick();
}

void setup() {


  //unsigned int timeToClose = 0;
  //EEPROM.put(0, timeToClose);
  //Serial.begin(9600);
  //Serial.println(EEPROM.get(0, timeToClose));

  //setup timer
  Timer1.initialize(1000000/500);
  Timer1.attachInterrupt(buttonsTick);


  //set pins mode
  pinMode(pinEnable, OUTPUT);
  pinMode(pinDirecA, OUTPUT);
  pinMode(pinDirecB, OUTPUT);

  pinMode(pinLightSensor, INPUT);
  pinMode(pinEndSwitchUp, INPUT_PULLUP);
  pinMode(pinEndSwitchDown, INPUT_PULLUP);

  pinMode(pinLedUp, OUTPUT);

  pinMode(pinLedCenterRed, OUTPUT);
  pinMode(pinLedCenterGreen, OUTPUT);
  pinMode(pinLedCenterBlue, OUTPUT);

  pinMode(pinLedDown, OUTPUT);

  //set pins default state
  digitalWrite(pinEnable, LOW);
  digitalWrite(pinDirecA, LOW);
  digitalWrite(pinDirecB, LOW);

  digitalWrite(pinLedUp, LOW);

  digitalWrite(pinLedCenterRed, LOW);
  digitalWrite(pinLedCenterGreen, HIGH);
  digitalWrite(pinLedCenterBlue, LOW);

  digitalWrite(pinLedDown, LOW);
}

void loop() {
  
}
