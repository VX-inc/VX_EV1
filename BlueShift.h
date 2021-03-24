/*!
 * @file BlueShift.h
 *
 * This library is written for the VX Inc. BlueShift headset to enable 
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

#ifndef BlueShift_h
#define BlueShift_h
#include "Arduino.h"

enum button_state_t {
	BUTTON_NO_PRESS,
	BUTTON_SHORT_UP,
	BUTTON_LONG_UP,
	BUTTON_SHORT_DOWN,
	BUTTON_LONG_DOWN,
	BUTTON_BOTH_PRESS
};

class BlueShift
{
public:
	bool init50005(uint16_t);
	button_state_t buttonManager(void);
	void setDisplayBrightness(uint8_t brightness);
	void setWhiteLED(uint8_t brightness);
	void setInfraredLED(uint8_t brightness);
	bool upButtonPressed(void);	
	bool downButtonPressed(void);
    uint16_t getALSValue(void);
private:
};

#endif
