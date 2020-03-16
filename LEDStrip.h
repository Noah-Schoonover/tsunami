
#ifndef _LEDSTRIP_H
#define _LEDSTRIP_H

#include "Object.h"
#include "IO_Mapping.h"
#include "Stopwatch.h"
#include "TouchSensor.h"
#include <Arduino.h>

enum Colors {
	RED,
	GREEN,
	BLUE
};

enum Modes {
	NORMAL_MODE,
	FLASH_MODE,
	STROBE_MODE,
	STROBE2_MODE,
	FADE_MODE,
	SMOOTH_MODE,
	SMOOTH2_MODE,
	REACT_MODE,
	TOUCH_MODE,
	TOUCH2_MODE
};

enum ModeSpeeds {
	SLOW_SPEED,
	MEDIUM_SPEED,
	FAST_SPEED
};

//-----------------------------------------------------------------------------------------
// class LEDStrip
//
// @brief  
//

class LEDStrip : public Object{

	public:

		LEDStrip(const char *pTag);

		void update();

		void setMode(Modes pMode);

		void writeColor(int pRed, int pGreen, int pBlue);
		void writeColor();
		void setRandomColor();
		void writeRandomColor();
		
		void setAndWriteColor(int pRed, int pGreen, int pBlue);

		unsigned char cycleColor(Colors pColor);
		void setBrightness(float pBrightness);
		void cycleBrightness();
		
		void handleFlash();
		int handleStrobe();
		void handleStrobe2();
		void handleFade();
		float handleSmooth();
		void handleSmooth2();
		void handleReact();
		void handleTouch();
		void handleTouch2();

		virtual ~LEDStrip();

	private:

		Modes mode = NORMAL_MODE;
		ModeSpeeds modeSpeed = SLOW_SPEED;

		// 255 is on, 0 is off
		unsigned char red = 255;
		unsigned char green = 255;
		unsigned char blue = 255;

		const unsigned char INCREASE_VALUE = 51;
		float brightness = 1.0;

		int potValue = 0;
		int threshold = 0;

		Stopwatch stopwatch;

		TouchSensor touchSensor;

		unsigned char *colors[3] = {&red, &green, &blue};
		unsigned char *targetColor;
		unsigned char targetColors[6][3] = {
			{255, 0, 0},
			{255, 255, 0},
			{0, 255, 0},
			{0, 255, 255},
			{0, 0, 255},
			{255, 0, 255}
		};

		int fadeCounter = 0;
		int smoothCounter = 0;
		int strobeState = 0;

};// end of class LEDStrip
//-----------------------------------------------------------------------------------------

#endif // _LEDSTRIP_H
