#ifndef _BASICS_H_
#define _BASICS_H_

Gyro gyro; // gyro object
#define GYRO_PORT 1 // macro for gyro port
Encoder left;
#define LEFT_PORT 1
Encoder right;
#define RIGHT_PORT 3

void drive(int left, int right);

void intake(int power);

void mogo(int power); // mogo lift function

#define LIFT_POT 2 // dr4b pot
#define BAR_POT 3 // 4-bar/shifter pot
#define MOGO_POT 4 // mogo lift pot
#define SIDE_POT 5 // auton selection side pot
#define MODE_POT 6 // auton selection type pot

void lift(int power); // elevator function

void shifter(int power); // chainbar function

#define JOY_STICK 0 // macro for accessing values from sticks in joystick() function
#define MAIN_CONTROL 1 // address of main controller (controls drive and mogo)
#define AUX_CONTROL 2 // address of aux controller (controls stacking)

int joystick(int controller, int channel, int button); // joystick value combo function

#endif // _BASICS_H_
