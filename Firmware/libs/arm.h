#ifndef ARM_H
#define ARM_H

#include "../headers/arm_config.h"
#include "../headers/joint.h"

#ifndef AccelStepper_h
#include <AccelStepper.h>
#endif

#ifndef MultiStepper_h
#include <MultiStepper.h>
#endif


// before these things ( bottom ) have to use init_arm() method
// 
// for move the robot you have to tell setPoint() method and set points( x, y, z )
// after that you tell solve() for solve cinematics		and next tell external method move()


//typedef struct {
	//double x;
	//double y;
	//double z;
//} Pos;


class ARM {

	public:

		ARM();
		joint joints[JOINTS_NUM]{
			// JOINT0
			{
				{ JOINT0 },
				{ 18, 22, 14 },
				{ MAX_ANGLE - 90, MIN_ANGLE - 90, 0, 0, 0 },
				{ MAX_SPEED, SPEED_FAST, FAST_ACCEL }
			},

			// JOINT1
			{ 
				{ JOINT1 },
				{ 19, 21, 27 },
				{ MAX_ANGLE, MIN_ANGLE, 0, 0, 0 },
				{ MAX_SPEED, SPEED_MID, MID_ACCEL }
			},

			// JOINT2
			{
				{ JOINT2 },
				{ 23, 33, 16 },
				{ MAX_ANGLE - 180, MIN_ANGLE - 180, 0, 0, 0 },
				{ MAX_SPEED, SPEED_MID, FAST_ACCEL }
			},

			// JOINT3
			{
				{ JOINT3 },
				{ 5, 32, 17 },
				{ MAX_ANGLE - 90, MIN_ANGLE - 90, 0, 0, 0 },
				{ MAX_SPEED, SPEED_FAST, FAST_ACCEL }
			},

			// JOINT4
			{
				{ JOINT4 },
				{ 13, 2, 25 },
				{ MAX_ANGLE - 90, MIN_ANGLE - 90, 0, 0, 0 },
				{ MAX_SPEED, SPEED_FAST, FAST_ACCEL }
			},

			// JOINT5
			{
				{ JOINT5 },
				{ 12, 4, 26 },
				{ MAX_ANGLE, MIN_ANGLE, 0, 0, 0 },
				{ MAX_SPEED, SPEED_FAST, FAST_ACCEL }
			}
		};

		bool solve();
		void setPoint(double x, double y, double z);
		void setEffectorOrientation(double rot_matrix[3][3]);
		void setEffectorIntoLowGround(const bool isLowGround);
		void getPos( double &x, double &y, double &z );


		void move(MultiStepper& steppers);
		void moveWTHAccel(AccelStepper* steppers);

	private:

		double** tmp_matrix;

		double x;
		double y;
		double z;


		bool lowGround = true;


		double rot_matrix_0_6[3][3] = {
			{0, 1, 0},
			{1, 0, 0},
			{0, 0, -1}
		};

		void anglesToSteps(double raw_angle, uint8_t x);

		//void findNewSpeed();
		//AccelStepper* findMaxSteps(AccelStepper* steppers);

		/*// for multiply two matrices, this function return pointer on matrix
		double** multiply_matrices(double matrix1[x][x], double matrix2[x][x]);

		// this function copy matrix1 to matrix2
		void copy_matrix(double** matrix1, double matrix2[x][x]);

		// for transposition of matrix, return changed matrix
		double** trans_matrix(double matrix[r][c]);

		// this function is only for 3x3 matrices,
		// function returns inverse_matrix
		double** inverse_matrix3(double matrix[3][3]);*/

};

#endif