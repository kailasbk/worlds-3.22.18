#include "main.h"

void nothing(){}

void left_20(){
  gyroReset(gyro); // reset gyro

  intake(30); // unfold robot
  while(analogRead(LIFT_POT) < 1750){
    lift(128);
    delay(20);
  }
  lift(12);

  TaskHandle shifterStart = taskRunLoop(shifterIntake, 10000); // position mogo intake
  TaskHandle mogoStart = taskRunLoop(mogoSetup, 10000); // position mogo intake
  delay(800);

  driveCounts(2500, 70, COAST); // drive towards goal
  taskDelete(mogoStart);
  taskDelete(shifterStart);

  delay(100); // stack first cone
  shifter(12);
  delay(100);
  lift(-48);
  delay(400);
  intake(-80);
  lift(64);
  delay(500);
  lift(0);

  mogoPosition(350); // intake mogo

  driveCounts(250, 50, COAST);

  intake(50); // intake 2nd cone
  shifter(-12);
  lift(-128);
  delay(400);
  lift(0);
  shifter(0);
  delay(200);

  intake(30); // stack 2nd cone
  lift(128);
  delay(400);
  lift(0);

  TaskHandle shifterBack = taskRunLoop(shifterMogo, 10000); // position mogo intake
  driveCounts(-800, 128, COAST);
  taskDelete(shifterBack);

  lift(-128);
  driveCounts(-250, 128, COAST);
  lift(0);

  driveCounts(-1450, 120, BRAKE); // drive back to zones
  intake(0); // shut off intake

  turnDegrees(-45); // turn parallel to starting bar

  driveCounts(-1200, 60, BRAKE); // drive to center
  lift(0);

  turnDegrees(-135); // turn to face zones

  intake(-80); // release stack
  lift(60);
  driveCounts(500, 128, COAST); // drive into zones
  lift(0);
  mogo(60);
  driveCounts(550, 128, COAST); // drive into zones

  drive(128, 128);
  delay(400);
  mogo(0);
  drive(-128, -128);
  delay(500);
  drive(0, 0);
}

void right_20(){
  gyroReset(gyro); // reset gyro

  intake(30); // unfold robot
  while(analogRead(LIFT_POT) < 1750){
    lift(128);
    delay(20);
  }
  lift(12);

  TaskHandle shifterStart = taskRunLoop(shifterIntake, 10000); // position mogo intake
  TaskHandle mogoStart = taskRunLoop(mogoSetup, 10000); // position mogo intake
  delay(800);

  driveCounts(2500, 70, COAST); // drive towards goal
  taskDelete(mogoStart);
  taskDelete(shifterStart);

  delay(100); // stack first cone
  shifter(12);
  delay(100);
  lift(-48);
  delay(400);
  intake(-80);
  lift(64);
  delay(500);
  lift(0);

  mogoPosition(350); // intake mogo

  driveCounts(250, 50, COAST);

  intake(50); // intake 2nd cone
  shifter(-12);
  lift(-128);
  delay(400);
  lift(0);
  shifter(0);
  delay(200);

  intake(30); // stack 2nd cone
  lift(128);
  delay(400);
  lift(0);

  TaskHandle shifterBack = taskRunLoop(shifterMogo, 10000); // position mogo intake
  driveCounts(-800, 128, COAST);
  taskDelete(shifterBack);

  lift(-128);
  driveCounts(-250, 128, COAST);
  lift(0);

  driveCounts(-1450, 120, BRAKE); // drive back to zones
  intake(0); // shut off intake

  turnDegrees(45); // turn parallel to starting bar

  driveCounts(-1200, 60, BRAKE); // drive to center
  lift(0);

  turnDegrees(135); // turn to face zones

  intake(-80); // release stack
  lift(60);
  driveCounts(500, 128, COAST); // drive into zones
  lift(0);
  mogo(60);
  driveCounts(550, 128, COAST); // drive into zones

  drive(128, 128);
  delay(400);
  mogo(0);
  drive(-128, -128);
  delay(500);
  drive(0, 0);
}

void left_stationary(){

  intake(30); // unfold robot
  while(analogRead(LIFT_POT) < 2400){
    lift(128);
    delay(20);
  }
  lift(12);

  shifterIntake();

  driveCounts(800, 30, BRAKE);

  shifter(-12);
  lift(-48);
  delay(400);
  intake(-80);
  lift(64);
  delay(300);

  driveCounts(-450, 30, COAST);

  lift(-64);
  delay(500);
  lift(0);

  TaskHandle shifterTuck = taskRunLoop(shifterMogo, 10000);

  turnDegrees(45);
  turnBrake(30);

  driveCounts(2600, 128, COAST);
  drive(100, 100);
  delay(300);
  drive(0, 0);

  taskDelete(shifterTuck);

}

void right_stationary(){

  intake(30); // unfold robot
  while(analogRead(LIFT_POT) < 2400){
    lift(128);
    delay(20);
  }
  lift(12);

  shifterIntake();

  driveCounts(800, 30, BRAKE);

  shifter(-12);
  lift(-48);
  delay(400);
  intake(-80);
  lift(64);
  delay(300);

  driveCounts(-450, 30, COAST);

  lift(-64);
  delay(500);
  lift(0);

  TaskHandle shifterTuck = taskRunLoop(shifterMogo, 10000);

  turnDegrees(45);
  turnBrake(30);

  driveCounts(2600, 128, COAST);
  drive(100, 100);
  delay(300);
  drive(0, 0);

  taskDelete(shifterTuck);

}
