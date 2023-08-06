
#ifndef _STOPWATCH_H
#define _STOPWATCH_H

#include <arduino.h>

//-----------------------------------------------------------------------------------------
// class Stopwatch
//
// @brief  A class for timing
//

class Stopwatch {

	public:

		Stopwatch();

		void start(uint32_t pElapsedTimeTarget);

		bool checkDone();
		void forceDone();

	private:

		uint32_t startTime, elapsedTimeTarget;

		bool done = true;

};// end of class Stopwatch
//-----------------------------------------------------------------------------------------

#endif // _STOPWATCH_H
