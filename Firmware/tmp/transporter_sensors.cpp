#include <Arduino.h>
#include "transporter_sensors.h"


TransporterSensors::TransporterSensors(int number_of_sensors, const Sensor* sensors)
	: sensors{ new Sensor[number_of_sensors] }, number_of_sensors{ number_of_sensors } {
	for (uint8_t i = 0; i < (uint8_t)this->number_of_sensors; i++) {
		this->sensors[i].name = sensors[i].name;
		this->sensors[i].pin = sensors[i].pin;
		pinMode(this->sensors[i].pin, INPUT_PULLUP);
		//Serial.print("INPUT_PULLUP->");
		//Serial.println(this->sensors[i].pin);
	}
}

/*TransporterSensors::TransporterSensors(int number_of_sensors)
	: sensors{ new Sensor[number_of_sensors] }, number_of_sensors{ number_of_sensors } {
	for (uint8_t i = 0; i < (uint8_t)this->number_of_sensors; i++) {
		this->sensors[i].name = "";
		this->sensors[i].pin = 0;
	}
}*/

TransporterSensors::~TransporterSensors() {
	delete[] this->sensors;
}



void TransporterSensors::addSensor(const Sensor _sensor) {
	Sensor* new_sensors = new Sensor[this->number_of_sensors + 1];

	for (uint8_t i = 0; i < (uint8_t)number_of_sensors; i++) {
		new_sensors[i].name = this->sensors[i].name;
		new_sensors[i].pin = this->sensors[i].pin;
	}

	new_sensors[number_of_sensors].name = _sensor.name;
	new_sensors[number_of_sensors].pin = _sensor.pin;
	this->number_of_sensors++;

	delete[] this->sensors;
	this->sensors = nullptr;
	this->sensors = new Sensor[this->number_of_sensors];

	for (uint8_t i = 0; i < (uint8_t)this->number_of_sensors; i++) {
		this->sensors[i].name = new_sensors[i].name;
		this->sensors[i].pin = new_sensors[i].pin;
	}

	pinMode(this->sensors[number_of_sensors - 1].pin, INPUT_PULLUP);

	//Serial.print("Added new sensor: PIN->");
	//Serial.print(this->sensors[number_of_sensors - 1].pin);
	//Serial.print(" NAME->");
	//Serial.println(this->sensors[number_of_sensors - 1].name);
	
	delete[] new_sensors;

}