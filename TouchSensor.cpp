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

TouchSensor::TouchSensor(const char *pTag, int pTransmit, int pReceive) :
	Object("TouchSensor", pTag),
	sensor(pTransmit, pReceive),
	stopwatch("Stopwatch")
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
			Serial.println(value);
			state = ON;
			stopwatch.start(50);
		} else {
			state = OFF;
		}
			
	}

}// end TouchSensor::update
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// TouchSensor::~TouchSensor (destructor)
//
// This is declared as virtual in the header file. Virtual methods should always be
// used when polymorphic behavior is to be used, such as when a pointer of the Base class
// type is used to delete the object. The virtual method will call the overriden method of
// the derived class. Non-virtual methods result in undefined behavior in this case.
//

TouchSensor::~TouchSensor(){


}// end of TouchSensor::~TouchSensor (destructor)
//-----------------------------------------------------------------------------------------

//end of class TouchSensor
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------