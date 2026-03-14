#include <Arduino.h>
#include "transporter.h"

#include "transporter_sensors.cpp"



Transporter::Transporter(const int motor_pin_1, const int motor_pin_2) {
	this->motor_pin_1 = motor_pin_1;
	this->motor_pin_2 = motor_pin_2;

	pinMode(this->motor_pin_1, OUTPUT);
	pinMode(this->motor_pin_2, OUTPUT);

	this->direction = 0;
	this->is_pwm = 0;

	this->sensors = new TransporterSensors(0, {});
}

Transporter::Transporter(const int motor_pin_1, const int motor_pin_2, const int number_of_sensors, const Sensor* sensors) {
	this->motor_pin_1 = motor_pin_1;
	this->motor_pin_2 = motor_pin_2;

	pinMode(this->motor_pin_1, OUTPUT);
	pinMode(this->motor_pin_2, OUTPUT);

	this->direction = 0;
	this->is_pwm = 0;

	//Serial.println("Creating sensors:\n");
	this->sensors = new TransporterSensors(number_of_sensors, sensors);
}


Transporter::Transporter(const int motor_pin_1, const int motor_pin_2, const bool is_pwm, const int pwm_pin) {
	this->motor_pin_1 = motor_pin_1;
	this->motor_pin_2 = motor_pin_2;

	pinMode(this->motor_pin_1, OUTPUT);
	pinMode(this->motor_pin_2, OUTPUT);

	this->direction = 0;
	
	this->is_pwm = is_pwm;
	this->pwm_pin = pwm_pin;
	pinMode(this->pwm_pin, OUTPUT);

	this->sensors = new TransporterSensors(0, {});
}

Transporter::Transporter(const int motor_pin_1, const int motor_pin_2, const int number_of_sensors, const Sensor* sensors, const bool is_pwm, const int pwm_pin) {
	this->motor_pin_1 = motor_pin_1;
	this->motor_pin_2 = motor_pin_2;

	pinMode(this->motor_pin_1, OUTPUT);
	pinMode(this->motor_pin_2, OUTPUT);

	this->direction = 0;

	this->pwm_pin = pwm_pin;
	this->is_pwm = is_pwm;
	pinMode(this->pwm_pin, OUTPUT);

	this->sensors = new TransporterSensors(number_of_sensors, sensors);
}

Transporter::~Transporter() {
	delete[] this->sensors;
}



void Transporter::setDirection(const int direction) {
	if (direction == 0 || direction == 1)
		this->direction = direction;
	//Serial.print("Dir: ");
	//Serial.println(this->direction);
}

void Transporter::setDirection(const char direction) {
	switch (direction) {
	case 'r':
		this->direction = 1;
		break;
	case 'l':
		this->direction = 0;
		break;
	default:
		//this->direction = 0;
		break;
	}
	//Serial.print("Dir: ");
	//Serial.println(this->direction);
}

void Transporter::setPWM(const int pwm) {
	if (pwm <= 255 && pwm >= 0)
		this->pwm = pwm;
	analogWrite(pwm_pin, this->pwm);
}

void Transporter::setMotorPins(void) {
	switch (this->direction) {
	case 0:
		digitalWrite(this->motor_pin_1, LOW);
		digitalWrite(this->motor_pin_2, HIGH);
		Serial.println("left");
		break;
	case 1:
		digitalWrite(this->motor_pin_1, HIGH);
		digitalWrite(this->motor_pin_2, LOW);
		Serial.println("right");
		break;
	}
}



void Transporter::stop(void) {
	digitalWrite(this->motor_pin_1, LOW);
	digitalWrite(this->motor_pin_2, LOW);
}

void Transporter::run(void) {
	setMotorPins();
}

void Transporter::runWTHInterrupts(void) {
	setMotorPins();
	bool isRunning = true;

	while (isRunning) {
		for (uint8_t i = 0; i < (uint8_t)this->sensors->number_of_sensors; i++) {
			if (digitalRead(this->sensors->sensors[i].pin) == LOW) {
				isRunning = false;
				break;
			}
		}
	}
}



void Transporter::getSerialInfo() {
	Serial.print("*This transporter contain--> PINS: ");
	Serial.print(this->motor_pin_1);
	Serial.print("\t");
	Serial.println(this->motor_pin_2);
	Serial.print("Current direction: ");
	Serial.println(this->direction);

	Serial.println("->>list of sensors<<-");
	for (uint8_t i = 0; i < (uint8_t)this->sensors->number_of_sensors; i++) {
		Serial.print("NAME: ");
		Serial.print(this->sensors->sensors[i].name);
		Serial.print("\t");
		Serial.print("PIN: ");
		Serial.println(this->sensors->sensors[i].pin);
	}
}



void Transporter::addSensor(Sensor sensor) {
	this->sensors->addSensor(sensor);
}

bool Transporter::checkSensor(String sensor) {
	if (this->sensors->number_of_sensors > 0) {
		for (uint8_t i = 0; i < this->sensors->number_of_sensors; i++) {
			if (this->sensors->sensors[i].name == sensor) {
				if (digitalRead(this->sensors->sensors[i].pin) == LOW)
					return true;
			}
		}
	}
	return false;
}