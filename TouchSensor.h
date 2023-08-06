
#ifndef _TOUCHSENSOR_H
#define _TOUCHSENSOR_H

#include "IO_Mapping.h"
#include "Stopwatch.h"
#include "CapacitiveSensor.h"
#include <Arduino.h>

enum Positions {
	ON,
	OFF
};

//-----------------------------------------------------------------------------------------
// class TouchSensor
//
// @brief  
//

class TouchSensor {

	public:

		TouchSensor(int pTransmit, int pReceive);

		void update(int threshold);

		Positions state = OFF;

	private:

		CapacitiveSensor sensor;
		long value_prev;
		long value;

		Stopwatch stopwatch;

};// end of class TouchSensor
//-----------------------------------------------------------------------------------------

#endif // _TOUCHSENSOR_H
