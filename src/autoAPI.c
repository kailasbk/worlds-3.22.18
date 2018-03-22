#include "main.h"

void driveCounts(int counts, int min, bool brake){
  encoderReset(left);
  encoderReset(right);

  // variables for storing encoder data
  int leftError = 0;
  int rightError = 0;
  int leftPower = 0;
  int rightPower = 0;

  if (counts > 0){
    while(encoderGet(left) < counts){ // while not at destination

      // calculate each sides error
      leftError = counts - encoderGet(left);
      rightError = counts - encoderGet(right);

      if(leftError < min/.2){
        leftPower = min; // minimum speed of 40
      }
      else{
        leftPower = .2 * leftError;
      }

      if(rightError < min/.2){
        rightPower = min; // minimum speed of 40
      }
      else{
        rightPower = .2 * rightError;
      }

      drive(leftPower, rightPower); // drive with speeds
      delay(20);
    }
  }
  else if (counts < 0){
    while(encoderGet(left) > counts){ // while not at destination

      // calculate each sides error
      leftError = counts - encoderGet(left);
      rightError = counts - encoderGet(right);

      if(leftError > -min/.2){
        leftPower = -min; // minimum speed of 40
      }
      else{
        leftPower = .2 * leftError;
      }

      if(rightError > -min/.2){
        rightPower = -min; // minimum speed of 40
      }
      else{
        rightPower = .2 * rightError;
      }

      drive(leftPower, rightPower); // drive with speeds
      delay(20);
    }
  }

  if(brake){
    driveBrake(min * 1.5); // brake to stop overshoot
  }
  else {
    drive(0, 0); // stop once done
  }
}

void driveBrake(int power){
  int last = encoderGet(left);
  delay(20);
  int current = encoderGet(left);
  int change = current - last;
  last = current;
  delay(20);

  if (change > 0){ // going forward
    while(change > 1){
      current = encoderGet(left);
      change = current - last;
      last = current;
      drive(-power, -power);
      delay(20);
    }
  }
  else if (change < 0){ // going backwards
    while(change < 1){
      current = encoderGet(left);
      change = current - last;
      last = current;
      drive(power, power);
      delay(20);
    }
  }
  drive(0, 0);

}

void turnDegrees(int degrees){
  int turnPower = 0;
  int turnError = 0;
  int errorSum = 0;
  int Kp = .7;
  int Ki = .04;
  int proportional, integral;

  if (degrees < gyroGet(gyro)){
    while(gyroGet(gyro) > degrees){

      turnError = abs(degrees - gyroGet(gyro)); // calculate turn error
      proportional = (.7) * turnError; // calulate proportional value
      if(proportional > 32){ // deactivate integral
        errorSum = integral = 0;
      }
      else{ // record and calculate integral
        errorSum = errorSum + turnError;
        integral = (.04) * (errorSum + 100);
        if(integral > 40){
          integral = 40;
        }
      }
      turnPower = proportional + integral;
      if(turnPower > 84){turnPower = 84;}

      drive(-turnPower, turnPower);

      delay(20);
    }
  }
  else if (degrees > gyroGet(gyro)){
    while(gyroGet(gyro) < degrees){

      turnError = abs(degrees - gyroGet(gyro)); // calculate turn error
      proportional = (.7) * turnError; // calulate proportional value
      if(proportional > 32){ // deactivate integral
        errorSum = integral = 0;
      }
      else{ // record and calculate integral
        errorSum = errorSum + turnError;
        integral = (.04) * (errorSum + 100);
        if(integral > 40){integral = 40;}
      }
      turnPower = proportional + integral;
      if(turnPower > 84){turnPower = 84;}

      drive(turnPower, -turnPower);

      delay(20);
    }
  }

  drive(0, 0);
}

void turnBrake(int power){
  int last = gyroGet(gyro);
  delay(20);
  int current = gyroGet(gyro);
  int change = current - last;
  last = current;
  delay(20);

  if (change > 0){ // going forward
    while(change > 1){
      current = gyroGet(gyro);
      change = current - last;
      last = current;
      drive(-power, power);
      delay(20);
    }
  }
  else if (change < 0){ // going backwards
    while(change < 1){
      current = gyroGet(gyro);
      change = current - last;
      last = current;
      drive(power, -power);
      delay(20);
    }
  }
  drive(0, 0);
}

void turnStabilize(int degrees){ // integral based stabilization turn
  int turnPower = 0;
  int turnError = 0;
  int errorSum = 0;
  int Ki = .08;
  int integral;

  if (degrees < gyroGet(gyro)){
    while(gyroGet(gyro) > degrees){

      turnError = abs(degrees - gyroGet(gyro)); // calculate turn error
      errorSum = errorSum + turnError;
      integral = (.08) * (errorSum);
      if(integral > 40){
          integral = 40;
      }
      turnPower = integral;

      drive(-turnPower, turnPower);

      delay(20);
    }
  }
  else if (degrees > gyroGet(gyro)){
    while(gyroGet(gyro) < degrees){

      turnError = abs(degrees - gyroGet(gyro)); // calculate turn error
      errorSum = errorSum + turnError;
      integral = (.08) * (errorSum);
      if(integral > 40){
          integral = 40;
      }
      turnPower = integral;

      drive(turnPower, -turnPower);

      delay(20);
    }
  }
  drive(0, 0);
}

void mogoPosition(int position){
  int liftError = 0;
  int liftPower = 0;

  if(analogRead(MOGO_POT) < position){
    while(analogRead(MOGO_POT) < position){

      liftError = position - analogRead(MOGO_POT);

      if(liftError < 300){
        liftPower = -45;
      }
      else{
        liftPower = -.15 * liftError;
      }

      mogo(-liftPower);
      delay(20);
    }
  }
  else if(analogRead(MOGO_POT) > position){
    while(analogRead(MOGO_POT) > position){

      liftError = analogRead(MOGO_POT) - position;

      if(liftError < 300){
        liftPower = 70;
      }
      else{
        liftPower = .15 * liftError;
      }

      mogo(-liftPower);
      delay(20);
    }
  }

  mogo(0);
}

void mogoSetup(){
  mogoPosition(2450);
}

void shifterMogo(){

  while(analogRead(BAR_POT) > 400){ // pot not past stack position
    shifter(127); // move chainbar towards stack
    delay(20);
  }
  shifter(0); // stop chainbar

}

void shifterIntake(){

  while(analogRead(BAR_POT) < 1800){ // pot not back in position
    shifter(-127); // move chainbar towards intake position
    delay(20);
  }
  shifter(0); // stop chainbar

}

void liftSustain(){
  if(analogRead(LIFT_POT) < 1750){
    lift(64);
    delay(200);
  }
  lift(0);
}
