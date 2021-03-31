
/*!
 * @file EV-1.cpp
 *
 * This library is written for the V.X. Inc. EV-1 Dev Board to develop 
 * user applications. 
 * 
 * This codebase is maintained at the following address. 
 * <https://github.com/VX-inc/VX_EV1>.
 *
 * For more information about the hardware referenced, please visit
 * <https://www.vx-inc.com/>
 * 
 */

#include "EV-1.h"
#include "Arduino.h"

//EV-1 Defines
#define EV1_UP_BUTTON_PIN               6
#define EV1_DOWN_BUTTON_PIN             5

int button_hold_time = 0;

//////////// EV1 FUNCITONS ///////////////

void EV1::init(uint16_t button_time) {
  button_hold_time = button_time;
  pinMode(EV1_UP_BUTTON_PIN, INPUT);
  pinMode(EV1_DOWN_BUTTON_PIN , INPUT);
  }

  button_state_t EV1::buttonManager(void){
  bool upButtonState = upButtonPressed();
  bool downButtonState = downButtonPressed();
  static bool upButtonLastState = false;
  static bool downButtonLastState = false;
  static bool doubleButtonPressed = false;
  unsigned long upHoldTime;
  unsigned long downHoldTime;
  button_state_t retVal = BUTTON_NO_PRESS;

  if (upButtonState && !upButtonLastState) {
    upHoldTime = millis();
  }

  if (downButtonState && !downButtonLastState) {
    downHoldTime = millis();
  }


  if ((!downButtonState || !upButtonState) && downButtonLastState && upButtonLastState) {
    doubleButtonPressed = true;
	retVal = BUTTON_BOTH_PRESS;
  }

  if (!upButtonState && upButtonLastState && !downButtonState && !doubleButtonPressed) {
    upHoldTime = millis() - upHoldTime;
    if (upHoldTime > 50) {  //50ms debounce
      if (upHoldTime < button_hold_time) { //long hold compare
		retVal = BUTTON_SHORT_UP;
      } else {
		retVal = BUTTON_LONG_UP;
      }
    }
  }

  if (!downButtonState && downButtonLastState && !upButtonState && !doubleButtonPressed) {
    downHoldTime = millis() - downHoldTime;
    if (downHoldTime > 50) {  //50ms debounce
      if (downHoldTime < button_hold_time) {  //long hold compare
		retVal = BUTTON_SHORT_DOWN;
      } else {
		retVal = BUTTON_LONG_DOWN;
      }
    }
  }

  if (!downButtonState && !upButtonState){
    doubleButtonPressed = false;
  }

  upButtonLastState = upButtonState;
  downButtonLastState = downButtonState;

  return retVal;
}

  bool EV1::upButtonPressed(void) {
    return digitalRead(EV1_UP_BUTTON_PIN);
  }

  bool EV1::downButtonPressed(void) {
    return digitalRead(EV1_DOWN_BUTTON_PIN);
  }