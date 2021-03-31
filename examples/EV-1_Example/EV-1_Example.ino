/*!
 * @file Ev-1_Example.ino
 *
 * This is an example sketch for use with the EV-1 Evaluation Board.  
 * 
 * This sketch requires the EV-1 board and at least 1 CNED Module.
 * 
 * This application demonstrates the following:
 * - Short button presses increase and decrease the display brightness
 * - Double button press switches to the ambient light sensor for CNED brightness control
 * - Serial port communication for system state
 * 
 * Please do not manipulate the individual ports without knowledge, this could cause damage
 * to the hardware.
 * 
 * This codebase is maintained at the following address. 
 * <https://github.com/VX-inc/VX_EV1>.
 * 
 * This codebase is dependant on having the MARS libary installed
 * <https://github.com/VX-inc/VX_MARS>
 *
 * For more information about the hardware referenced, please visit
 * <https://www.vx-inc.com/>
 * 
 */

#include <MARS.h> //The MARS libary must be installed as well
#include <EV-1.h>

#define BUTTON_HOLD_TIME_MS  1100          //Button hold time in milliseconds to indicate a long press

MARS mars;                                 //Create base AR system object, for adjusting display brightness, and reading ambient light sensor.
EV1 ev1;                                   //Create object for EV-1, contains buttons
int display_brightness = 4;                //Brightness scale 0-10, 0 is off, 10 is maximum brightness
bool als_controlled_brightness = false;    //Brightness for display automatically controlled by the ambient light sensor input, when false, brightness is controlled by the buttons.

void setup() {

  Serial.begin(9600);
  mars.init();                                     //Initalize the base hardware, display brightness and Ambient Light Sensor
  mars.setDisplayBrightness(display_brightness);   //Set the display brightness to the initial value

  Serial.println("EV-1 Example");
  ev1.init(BUTTON_HOLD_TIME_MS);                   //For use with the EV-1 evaluation board
  
}

void loop() {
  buttonLoop();    //Handles the button presses
  ALSLoop();       //Handles reading the ambient light sensor and updating the display brightness
  delay(10);       //Loop to run a ~100Hz, the loop should be run at at least 50Hz for button responsiveness.
}

void buttonLoop(void) {
  button_state_t buttonPressed = ev1.buttonManager(); //Gets the state of the button presses

  switch (buttonPressed) {
    case BUTTON_NO_PRESS:
      break;
    case BUTTON_SHORT_UP:
      Serial.println("Up button short press");
      if (!als_controlled_brightness) {
        turnUpBrightness();
      }
      break;
    case BUTTON_LONG_UP:
      Serial.println("Up button long press");
      break;
    case BUTTON_SHORT_DOWN:
      Serial.println("Down button short press");
      if (!als_controlled_brightness) {
        turnDownBrightness();
      }
      break;
    case BUTTON_LONG_DOWN:
      Serial.println("Down button long press");
      break;
    case BUTTON_BOTH_PRESS:
      Serial.println("Double button press");
      als_controlled_brightness = !als_controlled_brightness; //toggles if the ambient light sensor should be used as the brightness control
      if (als_controlled_brightness) {
        Serial.println("ALS Controlled Brightness");
      }
      if (!als_controlled_brightness) {
        Serial.println("Button Controlled Brightness");
      }
      break;
  }
}

void ALSLoop(void) {
  static float average_brightness = display_brightness;
  if (als_controlled_brightness) {
    static uint8_t lastBrightnessValue = 0;
    int alsValue = mars.getALSValue();                                   //Get the value of the ambient light sensor, scale from 0 to 1024 for 0-5V
    alsValue = map(alsValue, 0, 1024, 1, 10);                            //remaps the ambient light sensor output to a 1-10 range
    average_brightness = (0.99)*average_brightness + (0.01)*alsValue;    //Adds a fade to the ALS brightness adjustment
    display_brightness = (uint8_t) average_brightness;
    if (display_brightness != lastBrightnessValue) {                     //Sets the brightness only on a change in value, only needed to not spam the serial monitor
      setBrightness(display_brightness);
    }
    lastBrightnessValue = display_brightness;
  }
}

void setBrightness(uint8_t brightness) {
  Serial.print("Display Brightness: ");
  Serial.println(brightness);
  mars.setDisplayBrightness(brightness);
}

void turnUpBrightness(void) {
  if (display_brightness < 10)
  {
    display_brightness++;
  }
  setBrightness(display_brightness);
}

void turnDownBrightness(void) {
  if (display_brightness > 0)
  {
    display_brightness--;
  }
  setBrightness(display_brightness);
}
