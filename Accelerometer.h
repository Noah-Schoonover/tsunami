
#ifndef _ACCELEROMETER_H
#define _ACCELEROMETER_H

#include "Object.h"
#include "IO_Mapping.h"
#include "Stopwatch.h"
#include <Arduino.h>
#include "Adafruit_LIS3DH.h"

//-----------------------------------------------------------------------------------------
// class Accelerometer
//
// @brief  
//

class Accelerometer : public Object{

	public:

		Accelerometer(const char *pTag);

		void update();

		float x = 0;
		float y = 0;
		float z = 0;

		int getRange() { return 2 << sensor.getRange(); }

	private:

		Adafruit_LIS3DH sensor;

		Stopwatch stopwatch;

};// end of class Accelerometer
//-----------------------------------------------------------------------------------------

#endif // _ACCELEROMETER_H
