
#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "IO_Mapping.h"
#include <IRremote.h>
#include "LEDStrip.h"
#include "Bluefruit.h"

//-----------------------------------------------------------------------------------------
// class Controller
//
// center of program functionality
//

class Controller {

	public:

		Controller();

		void init();

		void process();

	protected:

		void setupIO();

		IRrecv irrecv;
		decode_results remoteInput;

		LEDStrip ledStrip;

		int retreiveIR();
		void handleIR();
		void handleBleMessage(char* data);
		void handleBleControl(char* packetbuffer);

};// end of class Controller  
//-----------------------------------------------------------------------------------------

#endif // _CONTROLLER_H