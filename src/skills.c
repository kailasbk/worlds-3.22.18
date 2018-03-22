#include "main.h"

void skills(){ // skills run which scores 42 points
  gyroReset(gyro); // reset gyro

  intake(30); // unfold robot
  lift(128);
  delay(400);
  lift(12);

  TaskHandle mogoStart = taskRunLoop(mogoSetup, 10000); // position mogo intake
  delay(800);

  driveCounts(2500, 40, COAST); // drive towards goal
  taskDelete(mogoStart);

  mogoPosition(350); // intake mogo

  driveCounts(-550, 128, COAST);

  lift(-128);
  driveCounts(-250, 128, COAST);
  lift(0);

  driveCounts(-1450, 40, BRAKE); // drive back to zones
  intake(0); // shut off intake

  turnDegrees(-45); // turn parallel to starting bar
  turnBrake(40);

  driveCounts(-1200, 60, BRAKE); // drive to center
  lift(0);

  turnDegrees(-135); // turn to face zones

  intake(-80); // release stack
  lift(60);
  driveCounts(500, 128, COAST); // drive into zones
  lift(0);
  mogo(60);
  driveCounts(550, 128, COAST); // drive into zones

  drive(128, 128); // drive in and out of zones
  delay(400);
  mogo(0);
  drive(-128, -128);
  delay(500);
  drive(0, 0);
  intake(0);
  delay(1000);
//---------------------------------------------------------------------//
  turnDegrees(-225); // turn parrallel to zone
  turnBrake(30);
  driveCounts(-1500, 40, COAST); // drive into zones
  turnStabilize(-270);
  drive(-40, -40);
  delay(1000);
  drive(0, 0);

  gyroReset(gyro);
  TaskHandle liftHold = taskRunLoop(liftSustain, 2000);

  driveCounts(400, 40, COAST); // drive off of wall
  turnDegrees(-15); // turn to mobile goal
  turnBrake(25);
  mogoPosition(2450);
  driveCounts(700, 40, COAST); // drive into mogo
  mogoPosition(350);

  turnDegrees(-225); // turn to face zones

  driveCounts(1050, 40, COAST); // drive into zones

  mogoPosition(2000);

  mogo(-60);
  driveCounts(-400, 40, BRAKE);
//---------------------------------------------------------------------//
  turnDegrees(-45); // turn to face next goal
  turnBrake(45);

  mogoPosition(2450);
  driveCounts(3300, 40, COAST);
  mogoPosition(350);
  mogo(-12);
  driveCounts(1800, 40, BRAKE);
  turnDegrees(-135); // turn parallel to zones

  driveCounts(-800, 40, BRAKE); //  to drive into center center

  turnDegrees(-45); // turn to face to zones

  driveCounts(500, 128, COAST); // drive into zones
  mogo(60);
  driveCounts(550, 128, COAST); // drive into zones

  drive(128, 128); // drive in and out of zones
  delay(400);
  mogo(0);
  drive(-128, -128);
  delay(600);
  drive(0, 0);

  //---------------------------------------------------------------------//

  turnDegrees(-135); // turn parrallel to zone
  driveCounts(-1500, 40, COAST); // drive into zones
  turnStabilize(-180);
  drive(-40, -40);
  delay(1000);
  drive(0, 0);

  gyroReset(gyro);

  driveCounts(400, 40, COAST); // drive off of wall
  turnDegrees(-15); // turn to mobile goal
  turnBrake(25);
  mogoPosition(2450);
  driveCounts(700, 40, COAST); // drive into mogo
  mogoPosition(350);

  turnDegrees(-225); // turn to face zones

  driveCounts(1050, 40, COAST); // drive into zones

  mogoPosition(2000);

  mogo(-60);
  driveCounts(-400, 40, BRAKE);
}
