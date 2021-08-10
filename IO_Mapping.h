
#ifndef _IO_MAPPING_H
#define _IO_MAPPING_H

#include <Arduino.h>

//-----------------------------------------------------------------------------------------

enum Inputs{

	IR_RECEIVE_PIN = 15,
	SOUND_SENSOR = A0,
	TOUCH_RECEIVE = 7,

	ENCODER_SW = A2,
	ENCODER_DT = A3,
	ENCODER_CLK = 12

};

enum Outputs {

	RED_LED = 5,
	GREEN_LED = 6,
	BLUE_LED = 9,

	TOUCH_TRANSMIT = 8,
    
};

// ELEGOO Infrared Remote
const unsigned long IR_ON           = 0xFFA25D;
const unsigned long IR_OFF          = 0xFFE21D;
const unsigned long IR_BRIGHTNESS   = 0xFFE01F;
const unsigned long IR_CYCLE_RED    = 0xFF22DD;
const unsigned long IR_CYCLE_GREEN  = 0xFF02FD;
const unsigned long IR_CYCLE_BLUE   = 0xFFC23D;
const unsigned long IR_WHITE        = 0xFF629D;
const unsigned long IR_FLASH        = 0xFF30CF;
const unsigned long IR_STROBE       = 0xFF18E7;
const unsigned long IR_STROBE2      = 0xFF4AB5;
const unsigned long IR_FADE         = 0xFF7A85;
const unsigned long IR_SMOOTH       = 0xFF10EF;
const unsigned long IR_SMOOTH2      = 0xFF42BD;
const unsigned long IR_REACT		= 0xFF38C7;
const unsigned long IR_TOUCH		= 0xFF5AA5;
const unsigned long IR_TOUCH2		= 0xFF52AD;
const unsigned long IR_ACCEL		= 0xFF9867;


/*   ELEGOO REMOTE LAYOUT
 *  ╔══════════╦══════════╦══════════╗
 *  ║   ON     ║	WHITE ║  OFF     ║
 *  ╠══════════╬══════════╬══════════╣
 *  ║  RED     ║   GRN    ║   BLU    ║
 *  ╠══════════╬══════════╬══════════╣
 *  ║ BRIGHT   ║          ║          ║
 *  ╠══════════╬══════════╬══════════╣
 *	║   	   ║  ACCEL   ║          ║
 *  ╠══════════╬══════════╬══════════╣
 *  ║  FLASH   ║  STROBE  ║ FADE     ║
 *  ╠══════════╬══════════╬══════════╣
 *  ║  SMOOTH  ║   REACT  ║ TOUCH    ║
 *  ╠══════════╬══════════╬══════════╣
 *	║  SMOOTH2 ║  STROBE2 ║  TOUCH2  ║
 *  ╚══════════╩══════════╩══════════╝
 */

//-----------------------------------------------------------------------------------------

#endif // _IO_MAPPING_H
