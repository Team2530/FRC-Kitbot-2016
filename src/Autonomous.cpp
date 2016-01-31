/*
 * Autonomous.cpp
 *
 *  Created on: Jan 31, 2016
 *      Authors: Eric and Jack
 */

#include <Autonomous.h>



Autonomous::Autonomous(DriveTrain *dt) {
	chooser = new SendableChooser();
	chooser->AddDefault(dN, (void*)&dN);
	chooser->AddObject(position1, (void*)&position1);
	chooser->AddObject(position4, (void*)&position4);
	chooser->AddObject(position2, (void*)&position2);
	chooser->AddObject(position3, (void*)&position3);
	chooser->AddObject(position5, (void*)&position5);
	SmartDashboard::PutData("Auto Modes", chooser);
	autoSelected = *((std::string*)chooser->GetSelected());
	std::string autoSelected = SmartDashboard::GetString("Auto Selector", dN);
	std::cout << "Auto selected: " << autoSelected << std::endl;
	robotd=dt;
	timer= new Timer();

}
	void Autonomous::doNothing(){
		robotd->DriveSet(0.0,0.0);
	}
	void Autonomous::driveOverDefense(){

		if (timer->Get()<5.0){
			robotd->DriveSet(1.0,0.0);
		}
		else{
			Autonomous::doNothing();
		}

	}
	bool Autonomous::attackTower(std::string position){
		//Angle/drive based on position
		return false;
	}
	void Autonomous::startTimer(){
		timer->Start();
	}
