//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

//=====[Defines]===============================================================

#define HEADLAMP_ON_LEVEL 0.8
#define HEADLAMP_OFF_LEVEL 0.2
#define DAYLIGHT_LEVEL 0.8
#define DUSK_LEVEL 0.6
#define TIME_INCREMENT_MS 20
#define WAIT_TIME_LIGHTS_OFF 2000
#define WAIT_TIME_LIGHTS_ON 1000

//=====[Declaration of public data types]======================================

typedef enum {
  WAIT,
  BUTTON_PRESSED,
  BUTTON_RELEASED
} ignitionButtonState_t;

//=====[Declaration and initialization of public global objects]===============

DigitalIn ignitionButton(BUTTON1);
DigitalIn driverSeatButton(D2);

DigitalOut engineLed(LED2);
DigitalOut leftHeadlight(D3);
DigitalOut rightHeadlight(D4);

AnalogIn potentiometer(A0);
AnalogIn LDR(A1);

ignitionButtonState_t ignitionButtonState;

//=====[Declaration and initialization of public global variables]=============

int timeElap = 0;

//=====[Declarations (prototypes) of public functions]=========================

void inputsInit();
void outputsInit();

void engineUpdate();
void headlightUpdate();
bool engineButtonUpdate();
bool driverSitting();

//=====[Main function, the program entry point after power on or reset]========

int main()
{
  inputsInit();
  outputsInit();
  while (true) {
      engineUpdate();
      if (engineLed) {
      headlightUpdate();
      }
      else if (leftHeadlight) {
          leftHeadlight = OFF;
          rightHeadlight = OFF;
      }
      delay(TIME_INCREMENT_MS);
  }
}

//=====[Implementations of public functions]===================================

void inputsInit()
{
  ignitionButton.mode(PullDown);
  driverSeatButton.mode(PullDown);
  ignitionButtonState = WAIT;
}

void outputsInit()
{
  engineLed = OFF;
  leftHeadlight = OFF;
  rightHeadlight = OFF;
}

void engineUpdate(){ //THE DELAY WILL FUCK WITH TESTING
 if (engineButtonUpdate()) {
     if (!engineLed) {
         if (driverSitting()) {
             engineLed = ON;
         }
     }
     else {
         engineLed = OFF;
     }
 }
}

bool engineButtonUpdate(){
  switch(ignitionButtonState){
      case WAIT :
          if(ignitionButton){
              ignitionButtonState = BUTTON_PRESSED;
          }
      break;
      case BUTTON_PRESSED :
          if(!ignitionButton){
              ignitionButtonState = BUTTON_RELEASED;
          }
      break;
      case BUTTON_RELEASED :
          ignitionButtonState = WAIT;
          return true;
      break;
  }
  return false;
}


void headlightUpdate(){
  float readP = potentiometer.read(); //headlights are turned on
  if(readP >= HEADLAMP_ON_LEVEL){
      leftHeadlight = ON;
      rightHeadlight = ON;
  }
  else if(readP <= HEADLAMP_OFF_LEVEL){ //headlights are turned off
      leftHeadlight = OFF;
      rightHeadlight = OFF;
  }
  else{ //Headlights are set to auto
      float readLDR = LDR.read();//Get the analog signal from the LDR
      if(readLDR >= DAYLIGHT_LEVEL){
          timeElap = timeElap + TIME_INCREMENT_MS;
          if (timeElap >= WAIT_TIME_LIGHTS_OFF){
          leftHeadlight = OFF;
          rightHeadlight = OFF;
          timeElap = 0;
          }
      }
      else if(readLDR <= DUSK_LEVEL){ 
          timeElap = timeElap + TIME_INCREMENT_MS;
          if (timeElap >= WAIT_TIME_LIGHTS_ON) {
               leftHeadlight = ON;
               rightHeadlight = ON;
               timeElap = 0;
          }
      }
      else {
          timeElap = 0;
      }
  }
}

bool driverSitting(){
if(driverSeatButton){
  return true;
}
  return false;
}
