#ifndef transporter_h
#define transporter_h

#include <Arduino.h>
#include "../headers/transporter_config.h"


class Transporter {
private:
	const int sleep_pin = SLEEP_PIN;		// 0 --> sleep / stop	| output
	const int sensor_pin = SENSOR_PIN;		// 0 --> is signal		| input wth pullup


public:

	Transporter();

	void init();

	void run();
	void runWTHSensor();
	void stop();

	bool isSensor();

};


#endif
