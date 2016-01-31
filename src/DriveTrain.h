/*
 * DriveTrain.h 
 *
 *  Created on: Jan 31, 2016
 *      Authors: Eric and Jack
 */
#include "WPILib.h"
#ifndef SRC_DRIVETRAIN_H_
#define SRC_DRIVETRAIN_H_

class DriveTrain {

	Victor *vic1;
	Victor *vic2;
	Victor *vic3;
	Victor *vic4;

	Joystick *stick;

	RobotDrive *myRobot;

	Encoder *leftEncoder;
	Encoder *rightEncoder;

public:
	DriveTrain();

	double getThrottle(double);
	void DriveSet(float, float);

	void AutonomousInit();
	void TeleopInit();
	void Drive();
	bool driveDistance(int,double);

};

#endif /* SRC_DRIVETRAIN_H_ */

