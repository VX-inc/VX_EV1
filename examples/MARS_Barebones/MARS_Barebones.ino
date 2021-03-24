/*!
 * @file BlueShift_ODN-50005.ino
 *
 * This is an example sketch for use with the barebones MARS Module.  
 * 
 * This sketch requires the base headset and at least 1 CNED installed.
 * 
 * This application demonstrates the following:
 * - Ambient light sensor for CNED brightness control
 * - Serial port communication for system state
 * 
 * Please do not manipulate the individual ports without knowledge, this could cause damage
 * to the hardware.
 * 
 * This codebase is maintained at the following address. 
 * <https://github.com/VX-inc/VX_BlueShift-Application-Examples>.
 *
 * For more information about the hardware referenced, please visit
 * <https://www.vx-inc.com/>
 * 
 */

#include <MARS.h>

MARS mars;                                 //Create base AR system object, for adjusting display brightness, and reading ambient light sensor.
int display_brightness = 4;                //Brightness scale 0-10, 0 is off, 10 is maximum brightness
bool als_controlled_brightness = false;    //Brightness for display automatically controlled by the ambient light sensor input, when false, brightness is controlled by the buttons.

void setup() {

  Serial.begin(9600);
  mars.init();                                     //Initalize the base hardware, display brightness and Ambient Light Sensor
  mars.setDisplayBrightness(display_brightness);   //Set the display brightness to the initial value

  Serial.println("MARS Barebones Example");
  
}

void loop() {
  ALSLoop();       //Handles reading the ambient light sensor and updating the display brightness
  delay(10);       //Loop to run a ~100Hz, 
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
