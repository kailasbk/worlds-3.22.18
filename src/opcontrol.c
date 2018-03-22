/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

void driveTask(void * parameter){ // separate task for drivetrain control

    int drivePower, driveTurn; // variables for arcade drive
    int driveMode = 0; // mode that determined which side of robot is 'front'
    int goalPower; // variable for mogo lift power

    while (true){ // always loop

      if (joystick(MAIN_CONTROL, 7, JOY_UP)){ // mogo is front
        driveMode = 0;
      }
      if (joystick(MAIN_CONTROL, 7, JOY_DOWN)){ // cone intake is front
        driveMode = 1;
      }

      // mobile goal control
      goalPower = joystick(MAIN_CONTROL, 2, JOY_STICK);
      mogo(goalPower);

      if (driveMode == 0){ // drive control when mogo is front
    		drivePower = joystick(MAIN_CONTROL, 3, JOY_STICK);
    		driveTurn = joystick(MAIN_CONTROL, 4, JOY_STICK);
    		drive(drivePower + driveTurn, drivePower - driveTurn);
      }
      else if (driveMode == 1){ // drive control when cone intake is front
        drivePower = -joystick(MAIN_CONTROL, 3, JOY_STICK);
        driveTurn = -joystick(MAIN_CONTROL, 4, JOY_STICK);
        drive(drivePower - driveTurn, drivePower + driveTurn);
      }

    }

	delay(10); // prevent hogging from main/stacking task
}
/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControl() {
	taskCreate(driveTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  int liftPower, shifterPower;
  int stackLocation = 1;

	while (true) {

    if(joystick(AUX_CONTROL, 7, JOY_UP)){
      stackLocation = 2;
    }
    else if(joystick(AUX_CONTROL, 7, JOY_DOWN)){
      stackLocation = 1;
    }

    if(abs(joystick(AUX_CONTROL, 3, JOY_STICK)) > 24){
      liftPower = joystick(AUX_CONTROL, 3, JOY_STICK);
    }
    else{
      liftPower = 0;
    }
    lift(liftPower);

    if((joystick(AUX_CONTROL, 3, JOY_STICK) < -20) && (analogRead(BAR_POT) > 1500)){
      shifterPower = -12;
    }
    else{
      shifterPower = joystick(AUX_CONTROL, 2, JOY_STICK);
    }
    shifter(shifterPower);

    if(joystick(AUX_CONTROL, 6, JOY_UP)){
      intake(60);
    }
    else if(joystick(AUX_CONTROL, 6, JOY_DOWN)){
      intake(-60);
    }
    else if(stackLocation == 1){
      if(joystick(AUX_CONTROL, 2, JOY_STICK) > 10){
        intake(30);
      }
      else if((joystick(AUX_CONTROL, 3, JOY_STICK) < -20) && (analogRead(BAR_POT) > 1500)){
        intake(80);
      }
      else if((joystick(AUX_CONTROL, 3, JOY_STICK) > 20) && (analogRead(BAR_POT) > 1500)){
        intake(30);
      }
      else if((joystick(AUX_CONTROL, 3, JOY_STICK) < -10) && (analogRead(BAR_POT) < 700)){
        intake(30);
      }
      else if((joystick(AUX_CONTROL, 3, JOY_STICK) > 20) && (analogRead(BAR_POT) < 700)){
        intake(-120);
      }
      else{
        intake(0);
      }
    }
    else if(stackLocation == 2){
      if(joystick(AUX_CONTROL, 2, JOY_STICK) < -10){
        intake(30);
      }
      else if((joystick(AUX_CONTROL, 3, JOY_STICK) < -10) && (analogRead(BAR_POT) > 1500)){
        intake(30);
      }
      else if((joystick(AUX_CONTROL, 3, JOY_STICK) > 20) && (analogRead(BAR_POT) > 1500)){
        intake(-100);
      }
      else if((joystick(AUX_CONTROL, 3, JOY_STICK) < -10) && (analogRead(BAR_POT) < 700)){
        intake(80);
      }
      else if((joystick(AUX_CONTROL, 3, JOY_STICK) > 10) && (analogRead(BAR_POT) < 700)){
        intake(30);
      }
      else{
        intake(0);
      }
    }

    printf("%d\n", analogRead(LIFT_POT));

    delay(10);
  }
}
