# VX_EV1

## Introduction
The V.X. EV-1 is a devleopment board designed to assist in the development of user applications on the V.X. Modular Augmented Reality System (MARS).  

Note that the EV-1 Library depends on the [MARS Libary](https://github.com/VX-inc/VX_MARS), please install this libary before trying to use this EV-1 Library.

[learn more here](https://www.vx-inc.com)

## Firmware Integration
The MARS has a dedicated application microcontroller (ATMEGA32U4) designed to allow the user to program system functionality specific to their needs. The microcontroller is programmable over USB through the main device USB-C port. 

  Microcontroller can interface with:
  * Backlight brightness control 
  * Modules
  * Ambient Light Sensor (ALS)
  * USB Serial Port

To get started, download the MARS library above.

## Application Examples

#EV-1 Example
This is an example sketch for use with the EV-1 Evaluation Board.  
This sketch requires the EV-1 board and at least 1 CNED Module.
This application demonstrates the following:
* Short button presses increase and decrease the display brightness
* Double button press switches to the ambient light sensor for CNED brightness control
* Serial port communication for system state

Please do not manipulate the individual ports without knowledge, this could cause damage to the hardware.
