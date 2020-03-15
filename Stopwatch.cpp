//-----------------------------------------------------------------------------------------
// Stopwatch.cpp
//
//

#include "Stopwatch.h"

//-----------------------------------------------------------------------------------------
// class Stopwatch
//
// A class for timing.
//
// Call init with the desired end time.
// Call checkDone to see if the elapsed time since the last init has passed the number of
// milliseconds specified by pElapsedTimeTarget. If so, done will be set true and function
// will return true.
//
// Call init again to restart the timer with a new elapsed time target.
//
// Must call checkDone as frequently as the resolution required. If only called every
// 5 seconds, then done can only be set with an accuracy of 5 seconds.
// 


//-----------------------------------------------------------------------------------------
// Stopwatch::Stopwatch (constructor)
//

Stopwatch::Stopwatch(const char *pTag) :
	Object("Stopwatch", pTag)
{

}// end of Stopwatch::Stopwatch (constructor)
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Stopwatch::start
//
// Initializes, records the current time, stores the elapsed time target value
// pElapsedTimeTarget, and sets done to false.
//
// pElapsedTimeTarget is the number of milliseconds after startTime at which to set done
// true.
//

void Stopwatch::start(uint32_t pElapsedTimeTarget){

	startTime = millis();

	elapsedTimeTarget = pElapsedTimeTarget;

	done = false;

}// end of Stopwatch::start
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Stopwatch::checkDone
//
// Sets done true and returns true if the elapsed time since the last init has passed the
// number of milliseconds specified by pEndElapseTime.
//
// If done is already true, returns true immediately without checking the elapsed time.
//
// Must call checkDone as frequently as the resolution required. If only called every
// 5 seconds, then done can only be set with an accuracy of 5 seconds.
//

bool Stopwatch::checkDone(){

	if(done) { return(done); }

	if ((millis() - startTime) > elapsedTimeTarget) { done = true; }

	return(done);

}// end of Stopwatch::checkDone
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Stopwatch::forceDone
//
// Sets done true and returns true if the elapsed time since the last init has passed the
// number of milliseconds specified by pEndElapseTime.
//
// If done is already true, returns true immediately without checking the elapsed time.
//
// Must call checkDone as frequently as the resolution required. If only called every
// 5 seconds, then done can only be set with an accuracy of 5 seconds.
//

void Stopwatch::forceDone(){

	done = true;

}// end of Stopwatch::forceDone
//-----------------------------------------------------------------------------------------

//end of class Stopwatch
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
