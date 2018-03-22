#ifndef _AUTOAPI_H_
#define _AUTOAPI_H_

void driveCounts(int counts, int min, bool brake);
void driveBrake(int power);

#define COAST 0
#define BRAKE 1

void turnDegrees(int degrees);
void turnBrake(int power);
void turnStabilize(int degrees);

void mogoPosition(int position);
void mogoSetup();

void shifterMogo();
void shifterIntake();

void liftSustain();

#endif // _AUTOAPI_H_
