//-----------------------------------------------------------------------------------------
// rgbRemote.ino
//
// For all Skoonie projects, the ino file does NOTHING except create the Controller object
// and start it up.
//
// See notes at the top of the Controller.cpp file for details pertaining to each project.
//

#include "Controller.h"

Controller *controller;

//-----------------------------------------------------------------------------------------
// setup
//
// This is the standard Arduino "setup" function which is called once on startup.
//

void setup() {

  Serial.begin(9600);
  Serial.println("---\nSerial Init");
  controller = new Controller();
  controller->init();

}// end of setup
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// loop
//
// This is the standard Arduino "loop" function which loops continuously after "setup"
// function has been executed.
//

void loop(void) {

  if( digitalRead(IR_RECEIVE_PIN) == HIGH) { digitalWrite(LED_BUILTIN, HIGH); }
  else { digitalWrite(LED_BUILTIN, LOW); }

  controller->process();

}// end of loop
//-----------------------------------------------------------------------------------------
