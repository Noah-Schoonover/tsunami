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
:	Object("Accelerometer", pTag),
	sensor(), // empty constructor for I2C
	stopwatch("Accelerometer Stopwatch")
{

	Serial.println("LIS3DH test!");

	if (! sensor.begin(0x18)) {   // change this to 0x19 for alternative i2c address
		Serial.println("Couldn't start");
		while (1) yield();
	}
	Serial.println("LIS3DH found!");

	sensor.setRange(LIS3DH_RANGE_2_G);   // 2, 4, 8 or 16 G!
	Serial.print("Range = "); Serial.print(2 << sensor.getRange());
	Serial.println("G");

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
		Serial.print("X: "); Serial.print(x);
		Serial.print("\tY: "); Serial.print(y);
		Serial.print("\tZ: "); Serial.println(z);
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