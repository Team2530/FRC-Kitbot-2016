#include "WPILib.h"

class Robot: public IterativeRobot{
private:
	LiveWindow *lw = LiveWindow::GetInstance();
	SendableChooser *chooser;
	
	Victor *victor1;
	Victor *victor2;
	Victor *victor3;
	Victor *victor4;
	
	Joystick *arcadeStick;
	
	RobotDrive *myRobot;
	
	Timer *timer;
	
	Encoder *leftEncoder; 
	Encoder *rightEncoder;
	
	double leftStart=0.0; 
	double rightStart=0.0;
	int step=0;

	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;

	void RobotInit(){
		
		victor1= new Victor(0);
		victor2= new Victor(1);
		victor3= new Victor(2);
		victor4= new Victor(3);
		myRobot= new RobotDrive(victor1, victor2, victor3, victor4);
		arcadeStick= new Joystick(0);
		chooser = new SendableChooser();
		chooser->AddDefault(autoNameDefault, (void*)&autoNameDefault);
		chooser->AddObject(autoNameCustom, (void*)&autoNameCustom);
		SmartDashboard::PutData("Auto Modes", chooser);
		
		
		timer= new Timer();
		leftEncoder = new Encoder (24,25, true, CounterBase:: k4X); //check ports
		rightEncoder = new Encoder (16,17, true, CounterBase:: k4X);
		leftEncoder->SetDistancePerPulse(6.0*3.14/128.0); //check circumference/(pulses per revolution)
		rightEncoder->SetDistancePerPulse(6.0*3.14/256.0);
	}
	void DriveSet(float speed, float angle){
		myRobot->ArcadeDrive(speed, angle, true);
	}
	
	bool driveDistance(int inches, double speed){
		bool done = false;
		double leftDis= leftEncoder->GetDistance()-leftStart;
		double rightDis= rightEncoder->GetDistance()-rightStart;
		if (leftDis<inches && leftDis>-inches && rightDis<inches && rightDis>-inches){
			Drive->DriveSet(speed,0.0);
		}
		else{
			Drive->DriveSet(0.0,0.0);
			done=true;
		}
		return done;
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
	void AutonomousInit(){
		autoSelected = *((std::string*)chooser->GetSelected());
		std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;
		
		leftEncoder->Reset();
		rightEncoder->Reset();
		rightStart=0.0;
		leftStart=0.0;
		
		
		timer->Start();
		if(autoSelected == autoNameCustom){
			//Custom Auto goes here
		} else {
			//Default Auto goes here
		}
	}
	
	void nextStep(bool done){
		if (done){
		  	step++;
			time->Reset();
			leftStart=leftEncoder->GetDistance();
			rightStart= rightEncoder->GetDistance();
		}
	}
	
	void doNothing()
	{
		Drive->DriveSet(0.0,0.0);
	}

	void AutonomousPeriodic(){
		if(autoSelected == autoNameCustom){
			//Custom Auto goes here
			if (timer->Get()<5)
			{
				myRobot->Drive(1.0,0.0);
			}
			else
			{
				myRobot->Drive(0.0,0.0);
			}
		} else {
			//Default Auto goes here
		}
	}

	void TeleopInit(){
		rightEncoder->Reset();
		leftEncoder->Reset();
	}
	double getThrottle(double val){
		 float throttle = arcadeStick->GetThrottle();
		 throttle++;
		 throttle = throttle *((1-val)/2);
		 throttle+= val;
		 return throttle;
	}

	void TeleopPeriodic(){
		float x= arcadeStick->GetY();
		float y= arcadeStick->GetTwist();
		double sensitivity= getThrottle(.5);
		myRobot->ArcadeDrive(x*sensitivity,y*sensitivity,true);
	}

	void TestPeriodic(){
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
