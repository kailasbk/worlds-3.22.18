#include "main.h"

class robotStatus{
  public:
    int statusCode = 0;
    bool voltageCheck_Main, voltageCheck_Expander, voltageCheck_Backup; // battery charged y/n
    // status of each mechanism: 0 is working, 1 is encoder issue, 2 is motor issue.
    int liftCheck, driveCheck, mogoCheck, shifterCheck;
    char problems[];

    void systemCheck(){

      // check the voltages of each battery to assure they are charged
      if(powerLevelBackup() < 8200){
        voltageCheck_Backup = false;
      }
      if(powerLevelMain() < 7900){
        voltageCheck_Main = false;
      }
      if(analogRead(0000) < 7900){
        voltageCheck_Expander = false;
      }

      // test that the drive is functioning properly
      encoderReset(left);
      encoderReset(right);
      drive(40, 40);
      delay(500);
      drive(0, 0);
      if ((encoderGet(left) <= 0) || (encoderGet(right) <= 0)){
        driveCheck = 1;
      }
      if (abs(encoderGet(left) - encoderGet(right)) > 30){
        driveCheck = 2;
      }

      // test that the lift is functioning properly
      int liftStart = analogRead(LIFT_POT);
      lift(40);
      delay(300);
      lift(0);
      int liftEnd = analogRead(LIFT_POT);
      if((liftStart < 300) || (liftEnd < 300)){
        liftCheck = 1;
      }
      if((liftEnd - liftStart) < 600){
        liftCheck = 2;
      }

      // test that the mogo intake is working
      int mogoStart = analogRead(MOGO_POT);
      mogo(40);
      delay(300);
      mogo(0);
      int mogoEnd = analogRead(MOGO_POT);
      if((mogoStart < 300) || (mogoEnd < 300)){
        mogoCheck = 1;
      }
      if((mogoEnd - mogoStart) < 400){
        mogoCheck = 2;
      }

      // test that the shifter is working
      int shifterStart = analogRead(BAR_POT);
      shifter(-40);
      delay(300);
      shifter(0);
      int shifterEnd = analogRead(BAR_POT);
      if((shifterStart < 300) || (shifterEnd < 300)){
        mogoCheck = 1;
      }
      if((shifterEnd - shifterStart) < 300){
        mogoCheck = 2;
      }

      // pack up robot
      mogoPosition(350);
      intake(60); // visually check to make sure intake moving
      shifter(60);
      delay(300);
      shifter(0);
      lift(-40);
      delay(400);
      lift(0);
    }

};

robotStatus status;
