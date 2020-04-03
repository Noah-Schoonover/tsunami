//-----------------------------------------------------------------------------------------
// LEDStrip.cpp
//
//

#include "LEDStrip.h"

//-----------------------------------------------------------------------------------------
// class LEDStrip
//
// 
// 

//-----------------------------------------------------------------------------------------
// LEDStrip::LEDStrip (constructor)
//

LEDStrip::LEDStrip(const char *pTag) :
	Object("LEDStrip", pTag),
	touchSensor("touchSensor", TOUCH_TRANSMIT, TOUCH_RECEIVE),
	stopwatch("Stopwatch")
{

	

}// end of LEDStrip::LEDStrip (constructor)
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// LEDStrip::update
//
// sets the PWM outputs to the specified values
// brightness values are inverted (subtracted from 255) for proper PWM control
//

void LEDStrip::update() {

	encoderValue = analogRead(POT_SENSOR);
	//Serial.println(encoderValue);

	switch(mode) {
		case NORMAL_MODE:
			break;
		case FLASH_MODE:
			handleFlash();
			break;
		case STROBE_MODE:
			handleStrobe();
			break;
		case STROBE2_MODE:
			handleStrobe2();
			break;
		case FADE_MODE:
			handleFade();
			break;
		case SMOOTH_MODE:
			handleSmooth();
			break;
		case SMOOTH2_MODE:
			handleSmooth2();
			break;
		case REACT_MODE:
			handleReact();
			break;
		case TOUCH_MODE:
			handleTouch();
			break;
		case TOUCH2_MODE:
			handleTouch2();
			break;
	}

}// end LEDStrip::update
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// LEDStrip::writeColor
//
// sets the PWM outputs to the specified values
//

void LEDStrip::writeColor(int pRed, int pGreen, int pBlue) {

	analogWrite(RED_LED, (float)pRed * brightness);
	analogWrite(GREEN_LED, (float)pGreen * brightness);
	analogWrite(BLUE_LED, (float)pBlue * brightness);

}// end LEDStrip::writeColor
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// LEDStrip::writeColor
//
// sets the PWM outputs to the stored red, green, and blue values
//

void LEDStrip::writeColor() {

	writeColor(red, green, blue);

}// end LEDStrip::writeColor
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// LEDStrip::setRandomColor
//
// sets the PWM outputs to the specified values
// brightness values are inverted (subtracted from 255) for proper PWM control
//

void LEDStrip::setRandomColor() {

	red = random(4) * 85;
	green = random(4) * 85;
	blue = random(4) * 85;

}// end LEDStrip::setRandomColor
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// LEDStrip::writeRandomColor
//
// sets the PWM outputs to the specified values
// brightness values are inverted (subtracted from 255) for proper PWM control
//

void LEDStrip::writeRandomColor() {

	setRandomColor();

	writeColor();

}// end LEDStrip::writeRandomColor
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// LEDStrip::setAndWriteColor
//
// sets the red, green, and blue variables and calls writeColor
//

void LEDStrip::setAndWriteColor(int pRed, int pGreen, int pBlue) {

	red = pRed;
	green = pGreen;
	blue = pBlue;

	writeColor(red, green, blue);

}// end LEDStrip::setAndWriteColor
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// LEDStrip::setMode
//
// sets the PWM outputs to the specified values
// brightness values are inverted (subtracted from 255) for proper PWM control
//

void LEDStrip::setMode(Modes pMode) {

	mode = pMode;

}// end LEDStrip::setMode
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// LEDStrip::cycleColor
//
// sets the red, green, and blue variables and calls writeColor
//

unsigned char LEDStrip::cycleColor(Colors pColor) {

	unsigned char *val = NULL;
	int temp;

	switch(pColor) {
	case RED:
		val = &red;
		break;
	case GREEN:
		val = &green;
		break;
	case BLUE:
		val = &blue;
		break;
	}

	temp = (int) *val;
	temp += INCREASE_VALUE;
	if(temp > 255)  temp = 0;
	*val = (unsigned char) temp;
	return *val;

}// end LEDStrip::cycleColor
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// LEDStrip::cycleBrightness
//
// cycles the brightness factor
//

void LEDStrip::cycleBrightness() {

	float newBrightness = brightness + 0.2;
	if(newBrightness > 1.0) newBrightness = 0.2;

	setBrightness(newBrightness);

}// end LEDStrip::cycleBrightness
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// LEDStrip::setBrightness
//
// sets the brightness factor
//

void LEDStrip::setBrightness(float pBrightness) {

	if(pBrightness >= 1.0) brightness = 1.0;
	else if(pBrightness <= 0.1) brightness = 0.1;
	else brightness = pBrightness;

	if(mode == NORMAL_MODE) writeColor();

}// end LEDStrip::setBrightness
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// LEDStrip::handleFlash
//
// handles the flash mode operation
//

void LEDStrip::handleFlash() {

	if(stopwatch.checkDone()) {
		writeRandomColor();
		stopwatch.start(encoderValue);
	}

}// end LEDStrip::handleFlash
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// LEDStrip::handleStrobe
//
// handles the strobe mode operation
//

int LEDStrip::handleStrobe() {

	if(stopwatch.checkDone()) {

		if(strobeState) {
			writeColor(0, 0, 0);
			stopwatch.start(encoderValue);

		} else {
			writeColor();
			stopwatch.start(20);
		}

		return strobeState = ++strobeState % 2;
		
	} else return 1;

}// end LEDStrip::handleStrobe
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// LEDStrip::handleStrobe2
//
// handles the strobe mode operation
//

void LEDStrip::handleStrobe2() {

	if(handleStrobe() == 0) setRandomColor();

}// end LEDStrip::handleStrobe2
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// LEDStrip::handlefade
//
// handles the fade mode operation
//

void LEDStrip::handleFade() {
	
	if(!stopwatch.checkDone()) return;

	stopwatch.start(encoderValue / 100);

	targetColor = targetColors[fadeCounter % 6];

	for (int j = 0; j < 3; j++){		// for r,g,b
		int step = 0;
		int dist = targetColor[j] - *(colors[j]); // +dist or -dist
		if(dist) step = dist / abs(dist); // either +1 or -1 or 0
		*(colors[j]) += step;
	}

	writeColor();

	if (red == targetColor[RED] && blue == targetColor[BLUE] && green == targetColor[GREEN]) {
		fadeCounter++;
	}

}// end LEDStrip::handlefade
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// LEDStrip::handleSmooth
//
// handles the Smooth mode operation
// returns the sin value so that it can be monitored by handleSmooth2()
//

float LEDStrip::handleSmooth() {

	if(!stopwatch.checkDone()) return 1;
	stopwatch.start(encoderValue/15);

	float x = smoothCounter = ++smoothCounter % 101;
	float a = PI/50.0;
	float y = 0.5 * ( sin(x*a) + 1 );

	int r = red * y;
	int g = green * y;
	int b = blue * y;

	writeColor(r, g, b);

	return y;

}// end LEDStrip::handleSmooth
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// LEDStrip::handleSmooth2
//
// handles the Smooth2 mode operation
// performs the same as handleSmooth() except when the sin return value from handleSmooth()
// reaches zero, the color is changed (each pulse is a random color)
//

void LEDStrip::handleSmooth2() {

	if(handleSmooth() < 0.0001) setRandomColor();

}// end LEDStrip::handleSmooth2
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// LEDStrip::handleReact
//
// handles the React mode operation
//

void LEDStrip::handleReact() {

	int soundValue = analogRead(SOUND_SENSOR);
	int scaledSound = ((float)soundValue / 1024.0) * 255.0;
	//if(soundValue > 100) Serial.println(soundValue);
	
	int temp = ((float) encoderValue / 1024.0) * 150;
	if(threshold != temp) {
		threshold = temp;
		Serial.println(threshold);
	}

	if(scaledSound > threshold) {
		//Serial.println(scaledSound);
		writeColor();
	} else {
		writeColor(0, 0, 0);
	}
}// end LEDStrip::handleReact
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// LEDStrip::handleTouch
//
// handles the Touch mode operation
//

void LEDStrip::handleTouch() {

	touchSensor.update(encoderValue);

	if(touchSensor.state == ON) {
		writeColor();
	} else {
		writeColor(0, 0, 0);
	}


}// end LEDStrip::handleTouch
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// LEDStrip::handleTouch2
//
// handles the Touch2 mode operation
//

void LEDStrip::handleTouch2() {

	touchSensor.update(encoderValue);

	if(touchSensor.state == ON && stopwatch.checkDone()) {
		writeRandomColor();
		stopwatch.start(50);
	}


}// end LEDStrip::handleTouch2
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// LEDStrip::~LEDStrip (destructor)
//
// This is declared as virtual in the header file. Virtual methods should always be
// used when polymorphic behavior is to be used, such as when a pointer of the Base class
// type is used to delete the object. The virtual method will call the overriden method of
// the derived class. Non-virtual methods result in undefined behavior in this case.
//

LEDStrip::~LEDStrip(){


}// end of LEDStrip::~LEDStrip (destructor)
//-----------------------------------------------------------------------------------------

//end of class LEDStrip
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------