#ifndef rotations_h
#define rotations_h

// low -> false
double down_rotation[3][3] = {
	{0, 1, 0},
	{1, 0, 0},
	{0, 0, -1}
};

// low -> false
double default_rotation[3][3] = {
	{1, 0, 0},
	{0, 0, 1},
	{0, -1, 0}
};


/*double up_rotation[3][3] = {
	{0, 1, 0},
	{-1, 0, 0},
	{0, 0, 1}
};*/

// low -> true
double straight_rotation[3][3] = {
	{0, 0, 1},
	{1, 0, 0},
	{0, 1, 0}
};

// low -> false
double back_rotation[3][3] = {
	{0, 0, -1},
	{1, 0, 0},
	{0, -1, 0}
};

#endif