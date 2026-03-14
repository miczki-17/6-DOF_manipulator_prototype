#ifndef transporter_h
#define transporter_h

#include "transporter_sensors.h"


class Transporter {
	private:
		int motor_pin_1;
		int motor_pin_2;
		int direction;

		int pwm;
		int pwm_pin;
		bool is_pwm;

		TransporterSensors* sensors;

		void setMotorPins();

	public:
		Transporter(const int motor_pin_1, const int motor_pin_2);
		Transporter(const int motor_pin_1, const int motor_pin_2, const bool is_pwm, const int pwm_pin);
		Transporter(const int motor_pin_1, const int motor_pin_2, const int number_of_sensors, const Sensor* sensors);
		Transporter(const int motor_pin_1, const int motor_pin_2, const int number_of_sensors, const Sensor* sensors, const bool is_pwm, const int pwm_pin);
		~Transporter();

		void setDirection(const int direction);
		void setDirection(const char direction);
		void setPWM(const int pwm);

		void addSensor(const Sensor sensor);
		bool checkSensor(String sensor);

		void stop();
		void run();
		void runWTHInterrupts();

		void getSerialInfo();
};


#endif