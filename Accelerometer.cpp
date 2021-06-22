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

	if(stopwatch.checkDone()){

		sensors_event_t event;
		sensor.getEvent(&event);

		x = event.acceleration.x;
		y = event.acceleration.y;
		z = event.acceleration.z;

		/* Display the results (acceleration is measured in m/s^2) */
		// Serial.print("\tX: "); Serial.print(x);
		// Serial.print("\tY: "); Serial.print(y);
		// Serial.print("\tZ: "); Serial.print(z);
		// Serial.println(" m/s^2 "); Serial.println();

		stopwatch.start(30);
			
	}

}// end Accelerometer::update
//-----------------------------------------------------------------------------------------

//end of class Accelerometer
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------