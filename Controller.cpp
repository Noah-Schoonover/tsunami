//-----------------------------------------------------------------------------------------
// Controller.cpp
//
//
// 

#include "Controller.h"

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
// class Controller
//
// This class is the main Controller (as in MVC structure).
//

//-----------------------------------------------------------------------------------------
// Controller::Controller (constructor)
//

Controller::Controller() :
	ledStrip("LED Strip"),
	irrecv(RECEIVE_PIN)
{

}// end of Controller::Controller (constructor)
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Controller::init
//
// top-level init that handles basic initialization and calls initSelf for specific init
// Must be called after instantiation to complete setup.
//

void Controller::init(){

	Serial.begin(9600);

	setupIO();

	debug();

	irrecv.enableIRIn(); // Start the receiver

}// end of Controller::init
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Controller::process
//
// this method is called every iteration in the main loop
//

void Controller::process(){

	if( retreiveIR() ) handleIR();

	ledStrip.update();

	//analogSensorValue = analogRead(ANALOG_SENSOR);

}// end of Controller::process
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Controller::retreiveIR
//
// stores any IR instructions from the receiver into the remoteInput object
// returns 1 if results are ready/valid
// returns 0 if results are not ready/invalid
//

int Controller::retreiveIR() {

	if (irrecv.decode(&remoteInput)) return 1;
	else return 0;

}// end Controller::retreiveIR
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Controller::handleIR
//
// processes IR instructions from the remote input
//

void Controller::handleIR() {

	//if(remoteInput.value == 0x0) return;
	Serial.println(remoteInput.value, HEX);

	switch(remoteInput.value) {

	case IR_ON:
		ledStrip.writeColor();
		ledStrip.setMode(NORMAL_MODE);
		break;

	case IR_OFF:
		ledStrip.writeColor(0, 0, 0);
		ledStrip.setMode(NORMAL_MODE);
		break;

	case IR_WHITE:
		ledStrip.setAndWriteColor(255, 255, 255);
		//ledStrip.setMode(NORMAL_MODE);
		break;

	case IR_CYCLE_RED:
		ledStrip.cycleColor(RED);
		ledStrip.writeColor();
		break;

	case IR_CYCLE_GREEN:
		ledStrip.cycleColor(GREEN);
		ledStrip.writeColor();
		break;

	case IR_CYCLE_BLUE:
		ledStrip.cycleColor(BLUE);
		ledStrip.writeColor();
		break;

	case IR_BRIGHTNESS:
		//cycleBrightness();
		break;

	case IR_SPEED:
		//cycleSpeed();
		break;

	case IR_FLASH:
		ledStrip.setMode(FLASH_MODE);
		break;

	case IR_STROBE:
		ledStrip.setMode(STROBE_MODE);
		break;

	case IR_STROBE2:
		ledStrip.setMode(STROBE2_MODE);
		break;

	case IR_FADE:
		ledStrip.setMode(FADE_MODE);
		break;
 
	case IR_SMOOTH:
		ledStrip.setMode(SMOOTH_MODE);
		break;

	case IR_SMOOTH2:
		ledStrip.setMode(SMOOTH2_MODE);
		break;

	case IR_REACT:
		ledStrip.setMode(REACT_MODE);
		break;

	case IR_TOUCH:
		ledStrip.setMode(TOUCH_MODE);
		break;

	case IR_TOUCH2:
		ledStrip.setMode(TOUCH2_MODE);
		break;

	default:
		break;

	}

	remoteInput.value = 0x0;	// reset remoteInput in order to only catch new signals
	irrecv.resume(); // Receive the next value

}// end Controller::handleIR
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Controller::setupIO
//
// Sets up Input/Output pins.
//

void Controller::setupIO() {
  
	pinMode(RED_LED, OUTPUT);
	pinMode(GREEN_LED, OUTPUT);
	pinMode(BLUE_LED, OUTPUT);

	pinMode(SOUND_SENSOR, INPUT);
	pinMode(POT_SENSOR, INPUT);

}// end Controller::setupIO
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// debug
//

void Controller::debug() {

  Serial.println("System Check...\n");
  
}// end debug
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Controller::Controller (destructor)
//

Controller::~Controller(){

}// end of Controller::Controller (destructor)
//-----------------------------------------------------------------------------------------

//end of class Controller
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
