//-----------------------------------------------------------------------------------------
// Controller.cpp
//
//
// 

#include "Controller.h"

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

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
	irrecv(IR_RECEIVE_PIN),
	ledStrip("LED")
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

	setupIO();

	debug();

	setupBluefruit(&ble);
	irrecv.enableIRIn(); // Start the receiver

}// end of Controller::init
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Controller::process
//
// this method is called every iteration in the main loop
//

void Controller::process(){

	//processBluefruit(&ble);
	if (ble.isConnected()) {
		ble.update(200);
		if (bleData[0] != 0) {
			// received a message
			//Serial.println(bleData);
			if (bleData[0] == '!') {
				handleBleControl(bleData);
			} else {
				handleBleMessage(bleData);
			}
			bleData[0] = 0;
		}
	}

	if( retreiveIR() ) handleIR();

	if(digitalRead(ENCODER_SW)) {
		digitalWrite(LED_BUILTIN, HIGH);
	} else {
		digitalWrite(LED_BUILTIN, LOW);
		Serial.println(F("enc sw"));
	}

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

/**************************************************************************/
/*!
    @brief  for messages not beginning with '!'
*/
/**************************************************************************/
void Controller::handleBleMessage(char* data) {
  Serial.println((char*) data);
  if (!strcmp((char*) data, "on")) {
    Serial.println(F("LEDS ON"));
	ledStrip.on();
	return;
  }
  if (!strcmp((char*) data, "off")) {
    Serial.println(F("LEDS OFF"));
	ledStrip.off();
	return;
  }
  if (!strcmp((char*) data, "touch")) {
    Serial.println(F("ENABLING TOUCH"));
	ledStrip.setMode(TOUCH_MODE);
	return;
  }
  if (!strcmp((char*) data, "sound")) {
    Serial.println(F("ENABLING SOUND"));
	ledStrip.setMode(REACT_MODE);
	return;
  }
}

/**************************************************************************/
/*!
    @brief  for messages beginning with '!'
*/
/**************************************************************************/
void Controller::handleBleControl(char* packetbuffer) {
  // Color
  if (packetbuffer[1] == 'C') {
    uint8_t red = packetbuffer[2];
    uint8_t green = packetbuffer[3];
    uint8_t blue = packetbuffer[4];
    Serial.print(F("RGB #: ")); 
    Serial.print(F("  red:"));
    Serial.print(red);
    Serial.print(F(" green:"));
    Serial.print(green);
    Serial.print(F(" blue:"));
    Serial.println(blue);
	ledStrip.setAndWriteColor(red, green, blue);
    return;
  }

  // Buttons
  if (packetbuffer[1] == 'B') {
    uint8_t buttnum = packetbuffer[2] - '0';
    boolean pressed = packetbuffer[3] - '0';
    Serial.print(F("Button ")); Serial.print(buttnum);
    if (pressed) {
      Serial.println(F(" pressed"));
    } else {
      Serial.println(F(" released"));
    }
    return;
  }

  // Accelerometer
  if (packetbuffer[1] == 'A') {
    float x, y, z;
    x = parsefloat(packetbuffer+2);
    y = parsefloat(packetbuffer+6);
    z = parsefloat(packetbuffer+10);
    Serial.print(F("Accel\t"));
    Serial.print(x); Serial.print('\t');
    Serial.print(y); Serial.print('\t');
    Serial.print(z); Serial.println();
    return;
  }

  // Magnetometer
  if (packetbuffer[1] == 'M') {
    float x, y, z;
    x = parsefloat(packetbuffer+2);
    y = parsefloat(packetbuffer+6);
    z = parsefloat(packetbuffer+10);
    Serial.print(F("Mag\t"));
    Serial.print(x); Serial.print('\t');
    Serial.print(y); Serial.print('\t');
    Serial.print(z); Serial.println();
    return;
  }

  // Gyroscope
  if (packetbuffer[1] == 'G') {
    float x, y, z;
    x = parsefloat(packetbuffer+2);
    y = parsefloat(packetbuffer+6);
    z = parsefloat(packetbuffer+10);
    Serial.print(F("Gyro\t"));
    Serial.print(x); Serial.print('\t');
    Serial.print(y); Serial.print('\t');
    Serial.print(z); Serial.println();
    return;
  }

  // Quaternions
  if (packetbuffer[1] == 'Q') {
    float x, y, z, w;
    x = parsefloat(packetbuffer+2);
    y = parsefloat(packetbuffer+6);
    z = parsefloat(packetbuffer+10);
    w = parsefloat(packetbuffer+14);
    Serial.print(F("Quat\t"));
    Serial.print(x); Serial.print('\t');
    Serial.print(y); Serial.print('\t');
    Serial.print(z); Serial.print('\t');
    Serial.print(w); Serial.println();
    return;
  }

  Serial.println(F("Unrecognized Command"));
}

//-----------------------------------------------------------------------------------------
// Controller::handleIR
//
// processes IR instructions from the remote input
//

void Controller::handleIR() {

	//if(remoteInput.value == 0x0) return;
	Serial.println(remoteInput.value, HEX);

	ledStrip.handleIR(remoteInput.value);

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

	pinMode(LED_BUILTIN, OUTPUT);
  
	pinMode(RED_LED, OUTPUT);
	pinMode(GREEN_LED, OUTPUT);
	pinMode(BLUE_LED, OUTPUT);

	pinMode(ENCODER_SW, INPUT);
	pinMode(ENCODER_DT, INPUT);
	pinMode(ENCODER_CLK, INPUT);

	pinMode(SOUND_SENSOR, INPUT);

}// end Controller::setupIO
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// debug
//

void Controller::debug() {

  Serial.println(F("SysChk...\n"));
  
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
