#include "arm.h"

#include "math.h"



#define DEG_TO_RAD ( 3.1415 / 180 )
#define RAD_TO_DEG ( 180 / 3.1415 )

ARM::ARM()
{
}


template< int x >
double** multiplyMatrices(double matrix1[x][x], double matrix2[x][x]) {

    double** result = new double* [x] {};
    for (int i = 0; i < x; i++)
        result[i] = new double[x] {};

    double tmp = 0;
    double sum = 0;

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < x; j++) {
            for (int k = 0; k < x; k++) {
                tmp = matrix1[i][k] * matrix2[k][j];
                sum += tmp;
            }
            result[i][j] = sum;
            sum = 0;
        }
    }
    return result;
}

template< int x >
void copyMatrix(double** matrix1, double matrix2[x][x]) {
    for (uint8_t i = 0; i < x; i++) {
        for (uint8_t j = 0; j < x; j++)
            matrix2[i][j] = matrix1[i][j];
    }
}
template< int x >
void copyMatrix(double matrix1[x][x], double matrix2[x][x]) {
    for (uint8_t i = 0; i < x; i++) {
        for (uint8_t j = 0; j < x; j++)
            matrix2[i][j] = matrix1[i][j];
    }
}

template< int r, int c >
double** transMatrix(double matrix[r][c]) {

    double** result = new double* [c] {};
    for (int i = 0; i < c; i++)
        result[i] = new double[r] {};

    for (uint8_t i = 0; i < c; i++) {
        for (uint8_t j = 0; j < r; j++) {
            result[i][j] = matrix[j][i];
        }
    }
    return result;
}

double** inverseMatrix3(double matrix[3][3]) {

    double** result = new double* [3]{};
    for (int i = 0; i < 3; i++)
        result[i] = new double[3]{};

    for (uint8_t i = 0; i < 3; i++) {
        for (uint8_t j = 0; j < 3; j++)
            result[i][j] = matrix[i][j];
    }

    double det = (matrix[0][0] * matrix[1][1] * matrix[2][2]) +
        (matrix[0][1] * matrix[1][2] * matrix[2][0]) +
        (matrix[0][2] * matrix[1][0] * matrix[2][1]) -
        (matrix[0][2] * matrix[1][1] * matrix[2][0]) -
        (matrix[0][1] * matrix[1][0] * matrix[2][2]) -
        (matrix[0][0] * matrix[1][2] * matrix[2][1]);

    if (det == 0)
        return result;

    result[0][0] = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
    result[0][1] = -(matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]);
    result[0][2] = matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0];

    result[1][0] = -(matrix[0][1] * matrix[2][2] - matrix[0][2] * matrix[2][1]);
    result[1][1] = matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0];
    result[1][2] = -(matrix[0][0] * matrix[2][1] - matrix[0][1] * matrix[2][0]);

    result[2][0] = matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1];
    result[2][1] = -(matrix[0][0] * matrix[1][2] - matrix[0][2] * matrix[1][0]);
    result[2][2] = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

    double tmp[3][3]{ {}, {}, {} };

    for (uint8_t i = 0; i < 3; i++) {
        for (uint8_t j = 0; j < 3; j++)
            tmp[i][j] = result[i][j];
    }
    result = transMatrix< 3, 3 >(tmp);

    for (uint8_t i = 0; i < 3; i++) {
        for (uint8_t j = 0; j < 3; j++)
            result[i][j] /= det;
    }

    return result;
}

void ARM::anglesToSteps(double raw_angle, uint8_t x) {
    double max_steps = GEAR_RATIO * STEPS;

    int steps = round((max_steps * raw_angle) / 360);
    joints[x].angle.steps = steps;
}

// IK solve
bool ARM::solve() {

    z -= a1;

    double theta1 = atan2(y, x) * RAD_TO_DEG;                                       // 1. first three joints angles
    double c = sqrt(x * x + y * y);


    double l = sqrt(z * z + c * c);
    double alpha = acos((a3 * a3 + l * l - a5 * a5) / (2 * a3 * l)) * RAD_TO_DEG;
    double gamma = atan2(z, c) * RAD_TO_DEG;

    double phi3 = acos((a3 * a3 + a5 * a5 - l * l) / (2 * a3 * a5)) * RAD_TO_DEG;   // took from imagin place

    double theta2 = alpha + gamma;
    double theta3 = -1 * (180 - phi3);


    theta1 *= DEG_TO_RAD;
    theta2 *= DEG_TO_RAD;
    theta3 *= DEG_TO_RAD;

	

    ////////////////////////////////////////////////////////////////                 // 2. set effector orientation
    
    ////////////////////////////////////////////////////////////////



    double rot_matrix_0_1[3][3] = {                                                  // 3. 0 - 3 rot_matrixes
        { cos(theta1), 0, sin(theta1)  },
        { sin(theta1), 0, -cos(theta1) },
        { 0,             1,          0 }
    };

    double rot_matrix_1_2[3][3] = {
        { cos(theta2), -sin(theta2), 0 },
        { sin(theta2), cos(theta2),  0 },
        { 0,             0,          1 }
    };

    double rot_matrix_2_3[3][3] = {
        { cos(theta3), -sin(theta3), 0 },
        { sin(theta3), cos(theta3),  0 },
        { 0,             0,          1 }
    };

    double rot_matrix_0_3[3][3] = { {}, {}, {} };

    tmp_matrix = multiplyMatrices< 3 >(rot_matrix_0_1, rot_matrix_1_2);            
    copyMatrix< 3 >(tmp_matrix, rot_matrix_0_3);
    tmp_matrix = multiplyMatrices< 3 >(rot_matrix_0_3, rot_matrix_2_3);
    copyMatrix< 3 >(tmp_matrix, rot_matrix_0_3);



    double inv_rot_matrix_0_3[3][3] = { {}, {}, {} };                                   // 4. inverse rot_matrix_0_3
    
    tmp_matrix = inverseMatrix3(rot_matrix_0_3);
    copyMatrix< 3 >(tmp_matrix, rot_matrix_0_3);



double rot_matrix_3_6[3][3] = { {}, {}, {} };                                       // 5. count rot_mat_3_6 from inv_rot_mat_0_3 * orient_effector_0_6

tmp_matrix = multiplyMatrices< 3 >(rot_matrix_0_3, rot_matrix_0_6);
copyMatrix< 3 >(tmp_matrix, rot_matrix_3_6);



double theta5 = -(acos(rot_matrix_3_6[2][2]));                                      // find last three angles
double theta6 = acos(rot_matrix_3_6[2][0] / sin(theta5));
double theta4 = asin(rot_matrix_3_6[1][2] / sin(theta5));

theta1 *= RAD_TO_DEG;
theta2 *= RAD_TO_DEG;
theta3 *= RAD_TO_DEG;
theta4 *= RAD_TO_DEG;
theta5 *= RAD_TO_DEG;
theta6 *= RAD_TO_DEG;

if (this->lowGround)
    theta4 = 180 - theta4;

theta5 = -180 - theta5;



double tmp[] = { theta1, theta2, theta3, theta4, theta5, theta6 };

uint8_t i;
for (i = 0; i < sizeof(tmp) / sizeof(double); i++) {
    if (tmp[i] != tmp[i])
        return false;
}

for (i = 0; i < 6; i++) {
    joints[i].angle.raw_angle = tmp[i];
    joints[i].angle.angle = round(tmp[i]);
}

for (i = 0; i < 6; i++)
    anglesToSteps(joints[i].angle.raw_angle, i);

return true;
}






void ARM::setPoint(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}
void ARM::setEffectorOrientation(double rot_matrix[3][3]) {
    copyMatrix< 3 >(rot_matrix, rot_matrix_0_6);
}
void ARM::setEffectorIntoLowGround(const bool isLowGround) {
    switch (isLowGround) {
    case 0:
        this->lowGround = 0;
        break;
    case 1:
        this->lowGround = 1;
        break;
    default:
        break;
    }
}
void ARM::getPos(double& x, double& y, double& z) {
    x = this->x;
    y = this->y;
    z = this->z;
}






void ARM::move(MultiStepper& steppers) {
    long gotopos[JOINTS_NUM];

    for (uint8_t i = 0; i < (uint8_t)JOINTS_NUM; i++)
        gotopos[i] = this->joints[i].angle.steps;

    steppers.moveTo(gotopos);
    steppers.runSpeedToPosition();
}


void ARM::moveWTHAccel(AccelStepper* steppers) {
    for (uint8_t i = 0; i < (uint8_t)JOINTS_NUM; i++)
        steppers[i].moveTo(this->joints[i].angle.steps);

#if JOINTS_NUM == 6

    while (steppers[0].currentPosition() != this->joints[0].angle.steps ||
        steppers[1].currentPosition() != this->joints[1].angle.steps ||
        steppers[2].currentPosition() != this->joints[2].angle.steps ||
        steppers[3].currentPosition() != this->joints[3].angle.steps ||
        steppers[4].currentPosition() != this->joints[4].angle.steps ||
        steppers[5].currentPosition() != this->joints[5].angle.steps) {

        for (uint8_t i = 0; i < (uint8_t)JOINTS_NUM; i++)
            steppers[i].run();
    }

#endif
}




/*AccelStepper* ARM::findMaxSteps(AccelStepper* steppers) {
    if (JOINTS_NUM > 1) {
        int tab[JOINTS_NUM];
        for (uint8_t i = 0; i < (uint8_t)JOINTS_NUM; i++)
            tab[i] = this->joints[i].angle.steps;


        AccelStepper* result;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4 - 1; j++)
                if (tab[j] < tab[j + 1]) {
                    std::swap(tab[j], tab[j + 1]);


        for (uint8_t i = 0; i < (uint8_t)JOINTS_NUM; i++) {
            if (this->joints[i].angle.steps == tab[0])
                result = this->joints[i];
        }


        return result;
    }
    else {
        return steppers;
    }

}*/

/*void ARM::findNewSpeed() {

}*/