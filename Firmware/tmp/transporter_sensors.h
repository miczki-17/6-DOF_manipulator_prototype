#ifndef transporter_sensors_h
#define transporter_sensors_h

typedef struct {
	String name;
	int pin;
} Sensor;

class TransporterSensors {
	public:
		Sensor* sensors;
		int number_of_sensors;


		TransporterSensors(int number_of_sensors, const Sensor* sensors);
		//TransporterSensors(int number_of_sensors);
		~TransporterSensors();

		void addSensor(const Sensor _sensor);
};


#endif