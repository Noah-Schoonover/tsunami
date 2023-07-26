
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
		void updateAvg();

		int16_t x = 0;
		int16_t y = 0;
		int16_t z = 0;

		int32_t xavg = 0;
		int32_t yavg = 0;

		int getRange() { return 2 << sensor.getRange(); }

	private:

		Adafruit_LIS3DH sensor;

		static const uint8_t BUF_SIZE = 100;
		int16_t xbuf[BUF_SIZE]{};
		int16_t ybuf[BUF_SIZE]{};

		Stopwatch stopwatch;

};// end of class Accelerometer
//-----------------------------------------------------------------------------------------

#endif // _ACCELEROMETER_H
