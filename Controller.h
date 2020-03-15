
#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "IO_Mapping.h"
#include <IRremote.h>
#include "LEDStrip.h"

//-----------------------------------------------------------------------------------------
// class Controller
//
// center of program functionality
//

class Controller{

	public:

		Controller();

		void init();

		void process();

		virtual ~Controller();

	protected:

		void setupIO();

		void debug();

		IRrecv irrecv;
		decode_results remoteInput;

		LEDStrip ledStrip;

		int retreiveIR();
		void handleIR();

};// end of class Controller  
//-----------------------------------------------------------------------------------------

#endif // _CONTROLLER_H