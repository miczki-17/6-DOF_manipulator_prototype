#ifndef joint_h
#define joint_h

typedef struct {
	int id;
} joint_id;

typedef struct {
	int step;
	int dir;
	int contact;
} joint_pin;

typedef struct {
	int max_angle;
	int min_angle;
	int steps;
	double raw_angle;
	double angle;
} joint_angle;

typedef struct {
	int max_speed;
	int speed;
	int accel;
} joint_speed;

typedef struct {
	joint_id id;
	joint_pin pin;
	joint_angle angle;
	joint_speed speed;
} joint;

#endif