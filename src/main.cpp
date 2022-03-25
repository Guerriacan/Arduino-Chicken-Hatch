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
#define DEBUG_WAIT while(!Serial) {}
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


//============== SETUP ================
void setup() {


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
//============== SETUP ================
void Reset() {
    digitalWrite(PinEnable, LOW);
    delay(10);
    digitalWrite(PinDirecA, HIGH);
    digitalWrite(PinDirecB, LOW);
    SecurityTimer = 0;
    DEBUG("=============== RESET DONE ==============");
}

void Opening() {
    DEBUG("Check de l'ouverture...");
    StateEndSwitchUp = digitalRead(PinEndSwitchUp);
    if (StateEndSwitchUp == 1) {
        DEBUG("La trappe n'est pas ouverte");
        LastOpenClose = 0;
        AddToLOC = 1;
        digitalWrite(PinDirecA, LOW); //one way
        digitalWrite(PinDirecB, HIGH);
        delay(10);
        digitalWrite(PinEnable, HIGH); //enable on
        DEBUG("Ouverture...");
        while (StateEndSwitchUp == 1) {
            StateEndSwitchUp = digitalRead(PinEndSwitchUp);
            SecurityTimer ++;
            if (SecurityTimer >= 4000) {
                DEBUG("================ ERROR ==================");
                Reset();
                DEBUG("================ ERROR ==================");
                Closing();
                DEBUG("================ ERROR ==================");
                break;
            }
            delay(10);
        }
        DEBUG("Trappe ouverte !");
    }
    else {
        DEBUG("La trappe est deja ouverte !");
    }

}

void Closing() {
    DEBUG("Check de la fermeture...");
    StateEndSwitchDown = digitalRead(PinEndSwitchDown);
    if (StateEndSwitchDown == 1) {
        DEBUG("La trappe n'est pas fermee");
        LastOpenClose = 0;
        AddToLOC = 1;
        digitalWrite(PinDirecA, HIGH); //one way
        digitalWrite(PinDirecB, LOW);
        delay(10);
        digitalWrite(PinEnable, HIGH); //enable on
        DEBUG("Fermeture...");
        while (StateEndSwitchDown == 1) {
            StateEndSwitchDown = digitalRead(PinEndSwitchDown);
            SecurityTimer ++;
            if (SecurityTimer >= 2900) {
                DEBUG("================ ERROR ==================");
                Reset();
                DEBUG("================ ERROR ==================");
                Opening();
                DEBUG("================ ERROR ==================");
                break;
            }
            delay(10);
        }
        DEBUG("Trappe fermee !");
    }
    else {
        DEBUG("La trappe est deja fermee !");
    }
}

void CheckButton() {
    DEBUG("Check de l'etat du bouton...");
    StateButton = digitalRead(PinButton);
    if (StateButton == 0) {
        DEBUG("Bouton appuye");
        StateEndSwitchUp = digitalRead(PinEndSwitchUp);
        if (StateEndSwitchUp == 1) {
            Opening();
        }
        else {
            Closing();
        }
        LastOpenClose = 64990;
    }
    else {
        DEBUG("Bouton relache");
    }
}

void CheckLight() {
    DEBUG("Check si il fait jour/nuit...");
    LightSensorLevel = analogRead(PinLightSensor);
    if (LastOpenClose > 65000) {
        AddToLOC = 0;
        if (LightSensorLevel < LightOpenLevel) {
            DEBUG("Il fait jour");
            Opening();
        }
        else if (LightSensorLevel > LightCloseLevel) {
            DEBUG("Il fait nuit");
            Closing();
        }
    }
}

void CheckBlocking() {
    DEBUG("Check du mode de fonctionnement...");
    StateBlocking = digitalRead(PinBlocking);
    if (StateBlocking == 0) {
        DEBUG("Mode automatique");
        CheckLight();
    }
    else {
        DEBUG("Mode manuel");
        CheckButton();
    }
}

//============== LOOP =================
void loop() {
    DEBUG("============= DEBUT DE LOOP =============");
    DEBUG("=============  Variables :  =============");
    //LightSensorLevel = analogRead(PinLightSensor);
    DEBUG(LightSensorLevel);
    DEBUG(LastOpenClose);
    DEBUG("=========================================");
    CheckBlocking();
    Reset();
    DEBUG("============== FIN DE LOOP ==============");
    DEBUG("");
    DEBUG("");
    delay(5);
    if (AddToLOC == 1) {
        LastOpenClose++;
    }
}
//============== LOOP =================