//-----------------------------------------------------------------------------------------
// TouchSensor.cpp
//
//

#include "TouchSensor.h"

//-----------------------------------------------------------------------------------------
// class TouchSensor
//
// 
// 

//-----------------------------------------------------------------------------------------
// TouchSensor::TouchSensor (constructor)
//

TouchSensor::TouchSensor(int pTransmit, int pReceive) :
	sensor(pTransmit, pReceive),
	stopwatch()
{

	

}// end of TouchSensor::TouchSensor (constructor)
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// TouchSensor::update
//
// sets the PWM outputs to the specified values
// brightness values are inverted (subtracted from 255) for proper PWM control
//

void TouchSensor::update(int threshold) {

	if(stopwatch.checkDone()){

		value_prev = value;
		value =  sensor.capacitiveSensor(30);

		if(value > threshold) {
			//Serial.println(value);
			state = ON;
			stopwatch.start(50);
		} else {
			state = OFF;
		}
			
	}

}// end TouchSensor::update
//-----------------------------------------------------------------------------------------

//end of class TouchSensor
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------