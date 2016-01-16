#include "WPILib.h"

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw = LiveWindow::GetInstance();
	//SendableChooser *chooser;
	Victor *victor1;
	Victor *victor2;
	Victor *victor3;
	Victor *victor4;
	Joystick *arcadeStick;
	RobotDrive *myRobot;



	/*const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;*/

	void RobotInit()
	{
		victor1= new Victor(0);
		victor2= new Victor(1);
		victor3= new Victor(2);
		victor4= new Victor(3);
		myRobot= new RobotDrive(victor1, victor2, victor3, victor4);
		arcadeStick= new Joystick(0);
		/*chooser = new SendableChooser();
		chooser->AddDefault(autoNameDefault, (void*)&autoNameDefault);
		chooser->AddObject(autoNameCustom, (void*)&autoNameCustom);
		SmartDashboard::PutData("Auto Modes", chooser);*/
	}


	/**
	 * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
	 * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
	 * Dashboard, remove all of the chooser code and uncomment the GetString line to get the auto name from the text box
	 * below the Gyro
	 *
	 * You can add additional auto modes by adding additional comparisons to the if-else structure below with additional strings.
	 * If using the SendableChooser make sure to add them to the chooser code above as well.
	 */
	void AutonomousInit()
	{
		/*autoSelected = *((std::string*)chooser->GetSelected());
		//std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if(autoSelected == autoNameCustom){
			//Custom Auto goes here
		} else {
			//Default Auto goes here
		}*/
	}

	void AutonomousPeriodic()
	{
		/*if(autoSelected == autoNameCustom){
			//Custom Auto goes here
		} else {
			//Default Auto goes here
		}*/
	}

	void TeleopInit()
	{

	}
	double getThrottle(double val)
	{
		 float throttle = arcadeStick->GetThrottle();
		 throttle++;
		 throttle = throttle *((1-val)/2);
		 throttle+= val;
		 return throttle;
	}

	void TeleopPeriodic()
	{
		float x= arcadeStick->GetY();
		float y= arcadeStick->GetTwist();
		double sensitivity= getThrottle(.5);
		myRobot->ArcadeDrive(x*sensitivity,y*sensitivity,true);
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
