#include "main.h"

void drive(int left, int right){
  motorSet(8, left); // drive left port 8
  motorSet(9, -right); // drive right port 9 (reversed)
}

void intake(int power){
  motorSet(2, power);
}

void mogo(int power){ // function for moving mogo lift
  motorSet(3, power); // right side port 3
}

void lift(int power){ // function for moving dr4b
  motorSet(6, power); // left side port 6
  motorSet(7, -power); // right side port 7
}

void shifter(int power){ // function for moving fourbar
  motorSet(4, power); // port 4
}

int joystick(int controller, int channel, int button){
  //combo joystick function for simplification
  if (channel <= 4){ // if analog channel
    return joystickGetAnalog(controller, channel);
  }
  else if (channel >= 5){ // if digital channel
    return joystickGetDigital(controller, channel, button);
  }
  return 0; // something goes wrong return 0;
}
