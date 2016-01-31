/*
 * DriveTrain.cpp
 *
 *  Created on: Jan 31, 2016
 *      Authors: Eric and Jack
 */

#include <DriveTrain.h>



DriveTrain::DriveTrain() {
		vic1 = new Victor(3);
		vic2= new Victor(2);


		vic3= new Victor(1);
		vic4= new Victor(0);
		myRobot= new RobotDrive(vic1,vic2,vic3,vic4);

		stick = new Joystick(0);
}
	void DriveTrain::AutonomousInit(){
		leftEncoder->Reset();
		rightEncoder->Reset();}


	void DriveTrain::TeleopInit(){}
	double DriveTrain::getThrottle(double val){
		 float throttle = stick->GetThrottle();
		 throttle++;
		 throttle = throttle *((1-val)/2);


		 throttle+= val;
		 return throttle;}

	void DriveTrain::Drive(){


		float throttle = getThrottle(.4);


		myRobot->ArcadeDrive(stick->GetY()*throttle, stick->GetTwist(),true);
	}


	void DriveTrain::DriveSet(float speed, float angle){
		myRobot->ArcadeDrive(speed,angle,true);
	}
