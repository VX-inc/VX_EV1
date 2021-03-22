/*!
 * @file BlueShift.cpp
 *
 * This library is written for the V.X. Inc. BlueShift headset to enable 
 * user applications.  This library includes references to hardware that 
 * may or may not be installed on the headset depending on the configuration.
 * 
 * Please insure that all devices that are referenced in code are attached to
 * the headset before use. 
 * 
 * This codebase is maintained at the following address. 
 * <https://github.com/VX-inc/VX_BlueShift-Application-Examples>.
 *
 * For more information about the hardware referenced, please visit
 * <https://www.vx-inc.com/>
 * 
 */

#include "Arduino.h"
#include "BlueShift.h"
#include "Wire.h"

#define BRIGHTNESS_PIN      11
#define WHITE_LED_PIN        5
#define FAR_RED_LED_PIN      6
#define I2C_EXPANDER_ADDR    0x20
#define UP_BUTTON_BIT        0
#define DOWN_BUTTON_BIT      4
#define ALS_PIN              A0

bool i2c_expander_connected = false;
int hold_time = 0;

bool BlueShift::init50005(uint16_t button_hold_time) {
  Wire.begin();
  Wire.beginTransmission(I2C_EXPANDER_ADDR );
  byte error = Wire.endTransmission();
  hold_time = button_hold_time;

  if (error == 0) {
    i2c_expander_connected = true;
    pinMode(BRIGHTNESS_PIN, OUTPUT);
    pinMode(WHITE_LED_PIN, OUTPUT);
    pinMode(FAR_RED_LED_PIN, OUTPUT);
    pinMode(ALS_PIN, INPUT);
  }
    return i2c_expander_connected;
  }
  
  
button_state_t BlueShift::buttonManager(void){
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
      if (upHoldTime < hold_time) { //long hold compare
		retVal = BUTTON_SHORT_UP;
      } else {
		retVal = BUTTON_LONG_UP;
      }
    }
  }

  if (!downButtonState && downButtonLastState && !upButtonState && !doubleButtonPressed) {
    downHoldTime = millis() - downHoldTime;
    if (downHoldTime > 50) {  //50ms debounce
      if (downHoldTime < hold_time) {  //long hold compare
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

  /* Integers from 0 to 10, 0 is off, 10 is full brightness */
  void BlueShift::setDisplayBrightness(uint8_t brightness) {
    if (brightness <= 10) {
      analogWrite(BRIGHTNESS_PIN, brightness * 10 + 15);
    }
  }

  /* Integers from 0 to 255, 0 is off, 255 is full brightness */
  void BlueShift::setWhiteLED(uint8_t brightness) {
    analogWrite(FAR_RED_LED_PIN, 0);
    analogWrite(WHITE_LED_PIN, brightness);
  }

  /* Integers from 0 to 255, 0 is off, 255 is full brightness */
  void BlueShift::setInfraredLED(uint8_t brightness) {
    analogWrite(WHITE_LED_PIN, 0);
    analogWrite(FAR_RED_LED_PIN, brightness);
  }

  bool BlueShift::upButtonPressed(void) {
    if (i2c_expander_connected) {
      Wire.requestFrom(I2C_EXPANDER_ADDR, 1);
      uint8_t readPacket;
      while (Wire.available()) {
        readPacket = Wire.read();
      }
      return !(0x01 & (readPacket >> UP_BUTTON_BIT));
    } else {
    return false;
	}
  }

  bool BlueShift::downButtonPressed(void) {
    if (i2c_expander_connected) {
      Wire.requestFrom(I2C_EXPANDER_ADDR, 1);
      uint8_t readPacket;
      while (Wire.available()) {
        readPacket = Wire.read();
      }
      return !(0x01 & (readPacket >> DOWN_BUTTON_BIT));
    } else {
    return false;
	}
  }

  uint16_t BlueShift::getALSValue(void) {
    return analogRead(ALS_PIN);
  }