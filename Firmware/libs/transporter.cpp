#include "transporter.h"

Transporter::Transporter() {
#ifdef BAUD
	Serial.println("Added transporter on pins:\n");
	Serial.print("START/STOP: ");
	Serial.print(this->sleep_pin);
	Serial.print("\t");
	Serial.print("SENSOR: ");
	Serial.print(this->sensor_pin);
	Serial.print("\n\n");
#endif
}




void Transporter::init() {
	pinMode(this->sleep_pin, OUTPUT);
	pinMode(this->sensor_pin, INPUT_PULLUP);
}




void Transporter::run() {
	digitalWrite(this->sleep_pin, HIGH);
}

void Transporter::runWTHSensor() {
	this->run();
	while (digitalRead(this->sensor_pin)) {

	}
}

void Transporter::stop() {
	digitalWrite(this->sleep_pin, LOW);
}




bool Transporter::isSensor() {
	if (digitalRead(this->sensor_pin) == LOW)
		return true;
	return false;
}