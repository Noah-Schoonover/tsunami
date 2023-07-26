//-----------------------------------------------------------------------------------------
// Accelerometer.cpp
//
//

#include "Accelerometer.h"

//-----------------------------------------------------------------------------------------
// class Accelerometer
//
// 
// 

//-----------------------------------------------------------------------------------------
// Accelerometer::Accelerometer (constructor)
//

Accelerometer::Accelerometer(const char *pTag) 
:	Object(pTag),
	sensor(), // empty constructor for I2C
	stopwatch("AccSW")
{

	Serial.print(F("acc.."));

	if (! sensor.begin(0x18)) {   // change this to 0x19 for alternative i2c address
		Serial.println(F("err"));
		while (1) yield();
	}
	Serial.println(F("found"));

	sensor.setRange(LIS3DH_RANGE_2_G);   // 2, 4, 8 or 16 G!
	Serial.print(F("R=")); Serial.print(2 << sensor.getRange());
	Serial.println(F("G"));

}// end of Accelerometer::Accelerometer (constructor)
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Accelerometer::update
//
//

void Accelerometer::update() {

	sensor.read();      // get X Y and Z data at once

	x = sensor.x;
	y = sensor.y;
	z = sensor.z;

	// Then print out the raw data
	if (false) {
		Serial.print(F("X: ")); Serial.print(x);
		Serial.print(F("\tY: ")); Serial.print(y);
		Serial.print(F("\tZ: ")); Serial.println(z);
	}
			
}// end Accelerometer::update
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Accelerometer::updateAvg
//
//

void Accelerometer::updateAvg() {

	update();

	memmove(xbuf + 1, xbuf, sizeof(int16_t) * (BUF_SIZE - 1));
	xbuf[0] = x;
	xavg = 0;
	for (size_t i = 0; i < BUF_SIZE; i++) { xavg += xbuf[i]; }
	xavg = xavg / BUF_SIZE;

	// Serial.print("xavg: "); Serial.print(xavg); Serial.print("     xbuf: "); 
	// for(size_t i = 0; i < BUF_SIZE; i++) {
	// 	Serial.print(xbuf[i]); Serial.print("   ");
	// }
	// Serial.println();

	/////////////////

	memmove(ybuf + 1, ybuf, sizeof(int16_t) * (BUF_SIZE - 1));
	ybuf[0] = y;
	yavg = 0;
	for (size_t i = 0; i < BUF_SIZE; i++) { yavg += ybuf[i]; }
	yavg = yavg / BUF_SIZE;

	// Serial.print("yavg: "); Serial.print(yavg); Serial.print("     ybuf: "); 
	// for(size_t i = 0; i < BUF_SIZE; i++) {
	// 	Serial.print(ybuf[i]); Serial.print("   ");
	// }
	// Serial.println();
	
			
}// end Accelerometer::updateAvg
//-----------------------------------------------------------------------------------------

//end of class Accelerometer
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------