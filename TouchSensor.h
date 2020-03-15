
#ifndef _TOUCHSENSOR_H
#define _TOUCHSENSOR_H

#include "Object.h"
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

class TouchSensor : public Object{

	public:

		TouchSensor(const char *pTag, int pTransmit, int pReceive);

		void update(int threshold);

		Positions state = OFF;

		virtual ~TouchSensor();

	private:

		CapacitiveSensor sensor;
		long value_prev;
		long value;

		Stopwatch stopwatch;

};// end of class TouchSensor
//-----------------------------------------------------------------------------------------

#endif // _TOUCHSENSOR_H
