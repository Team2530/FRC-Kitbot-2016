#include "WPILib.h"
#include "DriveTrain.h"
#include "Autonomous.h"
class Robot: public IterativeRobot{
private:
	LiveWindow *lw = LiveWindow::GetInstance();
	SendableChooser *chooser;

	Joystick *stick;
	Autonomous *autonomous;
	DriveTrain *Drive;



	Encoder *leftEncoder;
	Encoder *rightEncoder;

	double leftStart=0.0;
	double rightStart=0.0;
	int step=0;



	void RobotInit(){


		Drive= new DriveTrain();
		stick= new Joystick(0);


		leftEncoder = new Encoder (24,25, true, CounterBase:: k4X); //check ports
		rightEncoder = new Encoder (16,17, true, CounterBase:: k4X);
		leftEncoder->SetDistancePerPulse(6.0*3.14/128.0); //check circumference/(pulses per revolution)
		rightEncoder->SetDistancePerPulse(6.0*3.14/256.0);
		autonomous = new Autonomous(Drive);
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

		leftEncoder->Reset();
		rightEncoder->Reset();
		rightStart=0.0;
		leftStart=0.0;

		autonomous->startTimer();

	}

	void AutonomousPeriodic(){
			autonomous->driveOverDefense();

	}

	void TeleopInit(){
		rightEncoder->Reset();
		leftEncoder->Reset();
	}

	void TeleopPeriodic(){
		Drive->Drive();

	}

	void TestPeriodic(){
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
