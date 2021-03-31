
/*!
 * @file EV-1.h
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

#include"Arduino.h"

enum button_state_t {
	BUTTON_NO_PRESS,
	BUTTON_SHORT_UP,
	BUTTON_LONG_UP,
	BUTTON_SHORT_DOWN,
	BUTTON_LONG_DOWN,
	BUTTON_BOTH_PRESS
};

class EV1
{
public:
    void init(uint16_t);
	button_state_t buttonManager(void);
	bool upButtonPressed(void);	
	bool downButtonPressed(void);
private:
};