#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    ArmPot1,        sensorPotentiometer)
#pragma config(Sensor, in3,    WristPot1,      sensorPotentiometer)
#pragma config(Sensor, in4,    WristPot2,      sensorPotentiometer)
#pragma config(Sensor, I2C_3,  rightIEM,       sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  leftIEM,        sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           leftFrontMotor, tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port2,           leftBackMotor, tmotorVex393, openLoop)
#pragma config(Motor,  port3,           leftTopArm,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port4,           leftBottomArm, tmotorVex393, openLoop)
#pragma config(Motor,  port5,           leftWrist,     tmotorVex393, openLoop)
#pragma config(Motor,  port6,           rightWrist,    tmotorVex393, openLoop)
#pragma config(Motor,  port7,           rightBottomArm, tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port8,           rightTopArm,   tmotorVex393, openLoop)
#pragma config(Motor,  port9,           rightBackMotor, tmotorVex393, openLoop)
#pragma config(Motor,  port10,          rightFrontMotor, tmotorVex393, openLoop)

#pragma platform(VEX)
#include "Vex_Competition_Includes.c"
//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// ArmPot1 = 2833-2836, ArmPot2 = 4095, WristPot1 = 2270, WristPot2 = 2324 ArmPot2 = dud
//DYLAN DONT DELETE ANYTHING, DRIVING IS EASY WITH THIS. IF YOU WANT TO CONDENSE THOUGH, THAT IS FINE.
bool auton = false;
bool auton1 = false;
int rightLeft = 0;
int firstchoice = 0;
int LCDselect = 0;
bool autonL = false;
bool autonR = false;
int easyHard = 0;
// Autonomous codes
#define FORWARD 1
#define BACKWARD 0
#define RIGHT 1
#define LEFT 0
float clickspermeters = 1936.93;
bool isrunning;
int power, time, timeMS;
char direction;
int MaxPot = 1400;
int MinPot = 340;
const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;
//  Time is to be put in seconds when referencing a function, it will be converted to seconds by the function
//  For example arm(127, 5); would use the arm at full power for 5 seconds
void timeConvert(int time){
	int timeMS = time * 1000;
}
#define RAISE 1
#define LOWER 0
void arm(int power, int time){
	timeConvert(time);
	motor[leftTopArm] = power;
	motor[leftBottomArm] = power;
	motor[rightTopArm] = power;
	motor[rightBottomArm] = power;
	wait1Msec(timeMS);
}
void waitForRelease(){
	while(nLCDButtons != 0){}
	wait1Msec(5);
}
void resetLCD(){
	//reset all LCD variables to reset selection
	waitForRelease();
	rightLeft = 0;
	easyHard = 0;
	autonL = false;
	autonR = false;
	auton1 = false;
	auton = false;
	firstchoice = 0;
}
void autonomousSelection(){

	while(LCDselect == 0  && nSysTime < 15000){
		//set the while loop for the choices
		while(firstchoice == 0  && nSysTime < 15000){
			displayLCDCenteredString(0, "Left or Right?");
			//Autonomous or Not?
			if(nLCDButtons == leftButton){
				waitForRelease();
				auton = true;
				auton1 = true;
				firstchoice = 1;
				//set up the variables and booleans for autonomous = true
			}

			if(nLCDButtons == rightButton){
				waitForRelease();
				auton = false;
				firstchoice = 1;
				//Do nothing, prepare for User Control
			}

		} //End the Autonomous yes or no loop

		while(auton1 == true  && nSysTime < 15000){
			//when autonomous is selected
			displayLCDCenteredString(0, "Five sack or Y?");
			//Left or right Autonomous?
			if(nLCDButtons == leftButton){
				waitForRelease();
				rightLeft = 1;
				auton1 = false;
				autonL = true;
				//Set the variables for autonomous left
			}

			if(nLCDButtons == rightButton){
				waitForRelease();
				rightLeft = 2;
				auton1 = false;
				autonR = true;
				//set the variables for autonomous Right
			}
    }
	  displayLCDCenteredString(0, "Are you sure?");
		//Are you sure with the Code selected?
		displayLCDCenteredString(1, "Press center");
		//If sure, press center

		if(nLCDButtons == centerButton){
			//End LCD selections
			waitForRelease();
			LCDselect = 1;
		}

		if(nLCDButtons == leftButton)
		{
			// User is unsure, clear ALL variables to restart selection
			resetLCD();
		}

		if(nLCDButtons == rightButton)
		{
			// User is unsure, Clear ALL variables to restart Selection
			resetLCD();
		}

		}
}



void wrist(int power, int time){
	motor[rightWrist]  = power;
	motor[leftWrist] = power;
	wait1Msec(time);

	motor[rightWrist]  = 0;
	motor[leftWrist] = 0;
	wait1Msec(20);

}



void drive(int distance, char direction, int power){
	//This function is for driving autonomously with encoders
	int slave = power - 20;
	//To keep both motors and encoders fairly even
	SensorValue[rightIEM]=0;
	SensorValue[leftIEM]=0;
	// clear encoders
	if(direction == FORWARD){
		//if direction is = to forward
		while(abs(SensorValue[rightIEM]) < distance && abs(SensorValue[leftIEM]) < distance){
			//while encoders have less clicks than distance
			int turnPower = abs(SensorValue[rightIEM]) - abs(SensorValue[leftIEM]);

			if (abs(turnPower) < 30){ // If rightEncoder has counted the same amount as leftEncoder:
				// Move Forward
				motor[port1]=power;
				motor[port9]=-power;
				motor[port2]=power;
				motor[port10]=-power;
			}
			else if (abs(turnPower) > 30 && abs(SensorValue[leftIEM]) > abs(SensorValue[rightIEM])){	// If rightEncoder has counted more encoder counts
				// Turn slightly right
				motor[port1]=power;
				motor[port9]=-power+10;
				motor[port2]=power;
				motor[port10]=-power+10;
				}else{	// Only runs if leftEncoder has counted more encoder counts
				motor[port1]=power-10;
				motor[port9]=-power;
				motor[port2]=power-10;
				motor[port10]=-power;
			}
		}
	}//end of forward move

	if(direction == BACKWARD){
		//if direction = backward
		if(abs(SensorValue[rightIEM]) < distance && abs(SensorValue[leftIEM]) < distance){
			//Go backwards until the encoders are more than distance.(Did not use more accurate code because backwards is rarely used for than .5 seconds)
			motor[port1]=-power;
			motor[port2]=-power;
			motor[port9]=-power;
			motor[port10]=-power;
		}
	} //end of backtimemove
	motor[port1]=0;
	motor[port9]=0;
	motor[port2]=0;
	motor[port10]=0;
	wait1Msec(20);
	//turn motors off
}

void driveBackward(int power, int time){

	motor[rightFrontMotor] = power;
	motor[rightBackMotor] = power;
	motor[leftFrontMotor] = -power;
	motor[leftBackMotor] = -power;
	wait1Msec(time);
	motor[rightFrontMotor] = 0;
	motor[rightBackMotor] = 0;
	motor[leftFrontMotor] = 0;
	motor[leftBackMotor] = 0;
}

void turnLeft(int power, int time){

	motor[rightFrontMotor] = -power;
	motor[rightBackMotor] = -power;
	motor[leftFrontMotor] =-power;
	motor[leftBackMotor] = -power;
	wait1Msec(time);
}

void turnRight(int power, int time){
	timeConvert(time);
	motor[rightFrontMotor] = -power;
	motor[rightBackMotor] = power;
	motor[leftFrontMotor] = power;
	motor[leftBackMotor] = -power;
	wait1Msec(timeMS);
}
void aArm(int positionR, char direction, char power)
{

	//This function is for arm raising
	if(direction == RAISE)
	{
		//if direction is to raise the arm
		while (SensorValue[ArmPot1] > positionR)// arm up for high goal
		{
			// while both potentiometers are less than a set position power both arms

  motor[rightFrontMotor] = vexRT[Ch3] - vexRT[Ch2] + vexRT[Ch1];
    motor[rightBackMotor] =  vexRT[Ch3] - vexRT[Ch2] - vexRT[Ch1];
    motor[leftFrontMotor] = vexRT[Ch3] + vexRT[Ch2] + vexRT[Ch1];
    motor[leftBackMotor] =  vexRT[Ch3] + vexRT[Ch2] - vexRT[Ch1];
			motor[leftWrist] = -30;
		motor[rightWrist] = -30;

  motor[leftTopArm] = power;
	motor[leftBottomArm] = power;
	motor[rightTopArm] = power;
	motor[rightBottomArm] = power;
		}
		isrunning = false;
	}
	//End of RAISE

	else if(direction == LOWER) //LOWER
	{
 while (SensorValue[ArmPot1] < positionR) {// arm down
	// while both potentiometers are more than a set position power both arms negatively.

	motor[leftTopArm] = -power;
	motor[leftBottomArm] = -power;
	motor[rightTopArm] = -power;
	motor[rightBottomArm] = -power;
	  motor[leftWrist] = -30;
		motor[rightWrist] = -30;
     motor[rightFrontMotor] = vexRT[Ch3] - vexRT[Ch2] + vexRT[Ch1];
    motor[rightBackMotor] =  vexRT[Ch3] - vexRT[Ch2] - vexRT[Ch1];
    motor[leftFrontMotor] = vexRT[Ch3] + vexRT[Ch2] + vexRT[Ch1];
    motor[leftBackMotor] =  vexRT[Ch3] + vexRT[Ch2] - vexRT[Ch1];
 	}
 		isrunning = false;
		}
   motor[leftWrist] = 0;
		motor[rightWrist] = 0;
		wait1Msec(20);
	//stop arm
}
void AutoArm(int positionR, char direction, char power)
{

	//This function is for arm raising
	if(direction == RAISE)
	{
		//if direction is to raise the arm
		while (SensorValue[ArmPot1] < positionR)// arm up for high goal
		{
			// while both potentiometers are less than a set position power both arms
	motor[leftTopArm] = power;
	motor[leftBottomArm] = power;
	motor[rightTopArm] = power;
	motor[rightBottomArm] = power;
			motor[leftWrist] = -40;
		motor[rightWrist] = -40;

		}
		isrunning = false;
	}
	//End of RAISE

	else if(direction == LOWER) //LOWER
	{
 while (SensorValue[ArmPot1] > positionR) {// arm down
	// while both potentiometers are more than a set position power both arms negatively.

	motor[leftTopArm] = -power;
	motor[leftBottomArm] = -power;
	motor[rightTopArm] = -power;
	motor[rightBottomArm] = -power;
	  motor[leftWrist] = -30;
		motor[rightWrist] = -30;

 	}
 		isrunning = false;
		}

	//stop arm
}
void strafeLeft(int power, int distance){
 while(abs(SensorValue[leftIEM]) < distance){
	motor[rightFrontMotor] = -power;
	motor[rightBackMotor] = power;
	motor[leftFrontMotor] = -power;
	motor[leftBackMotor]  = power;
}
}

void strafeRight(int power, int distance){
  SensorValue[rightIEM]=0;
	SensorValue[leftIEM]=0;
 while(abs(SensorValue[rightIEM]) < distance){
	motor[rightFrontMotor] = power;
	motor[rightBackMotor] = -power;
	motor[leftFrontMotor] = power;
	motor[leftBackMotor]  = -power;
}
}

// driver control code
void driverControl(){

    motor[rightFrontMotor] = vexRT[Ch3] - vexRT[Ch2] + vexRT[Ch4];
    motor[rightBackMotor] =  vexRT[Ch3] - vexRT[Ch2] - vexRT[Ch4];
    motor[leftFrontMotor] = vexRT[Ch3] + vexRT[Ch2] + vexRT[Ch4];
    motor[leftBackMotor] =  vexRT[Ch3] + vexRT[Ch2] - vexRT[Ch4];

}

// Wrist and arm code
void armUserControl(){
		if(vexRT[Btn6U] == 1 && SensorValue[ArmPot1] > 1850)
		// If 6U is pressed, arm goes up
	{
		motor[leftBottomArm] = 127;
		motor[leftTopArm] = 127;
		motor[rightBottomArm] = 127;
		motor[rightTopArm] = 127;
	}

	else if(vexRT[Btn6D] == 1)
		// If 6D is pressed, arm goes down
	{
  	motor[leftBottomArm] = -127;
		motor[leftTopArm] = -127;
		motor[rightBottomArm] = -127;
		motor[rightTopArm] = -127;
	}
	else
		// otherwise, do nothing
	{
		motor[leftBottomArm] = 0;
		motor[leftTopArm] = 0;
		motor[rightBottomArm] = 0;
		motor[rightTopArm] = 0;
	}


if(vexRT[Btn8D] == 1)
		// If 6U is pressed, arm goes up
	{
    isrunning = true;
		aArm(MinPot, LOWER, 120);
	}
	else if(vexRT[Btn8U] == 1){
		isrunning = true;
		aArm(MaxPot, RAISE, 120);
}
}
void wristUserControl(){
	if(vexRT[Btn5U] == 1 && SensorValue[ArmPot1] > 3400 && SensorValue[WristPot1] < 3450)//wrist stop
		// If 6U is pressed, arm goes up
  {
  	motor[leftWrist] = 127;
		motor[rightWrist] = 127;
	}
	else if(vexRT[Btn5U] == 1 && SensorValue[ArmPot1] < 3400){

		motor[leftWrist] = 127;
		motor[rightWrist] = 127;

	}
	else if(vexRT[Btn5D] == 1)
		// If 6D is pressed, arm goes down
	{
			motor[leftWrist] = -127;
		motor[rightWrist] = -127;
	}
	else
		// otherwise, do nothing
	{
	  motor[leftWrist] = 0;
		motor[rightWrist] = 0;
	}
}

void position(){
if (vexRT[Btn6U] == 0 && vexRT[Btn6D] == 0 && SensorValue[ArmPot1] < 3400&& SensorValue[ArmPot1] > 1850 && vexRT[Btn8U] == 0 && vexRT[Btn8D] == 0){
	  motor[rightTopArm] = 15;
		motor[rightBottomArm] = 15;
		motor[leftTopArm] = 15;
		motor[leftBottomArm] = 15;
	}
}

void easy(){
	while (vexRT[Btn6U] == 1 && motor[rightTopArm] == 127){
		motor[leftWrist] = -25;
		motor[rightWrist] = -25;
	}
	while (vexRT[Btn6D] == 1 && motor[rightTopArm] == 127){
		motor[leftWrist] = 60;
		motor[rightWrist] = 60;
	}

}
//  && SensorValue[ArmPot1] > 3000
void wriststeady(){
	while(vexRT[Btn5U] == 0 && vexRT[Btn5D] == 0 && vexRT[Btn6D] == 0 && vexRT[Btn6U] == 0 && vexRT[Btn8U] == 0 && vexRT[Btn8D] == 0 && motor[rightTopArm] < 30	&&	motor[rightWrist] < 30 &&
		motor[rightWrist] > -30){
		motor[leftWrist] = 10;
		motor[rightWrist] = 10;
	}
}

task one(){
	driverControl();
	armUserControl();
	wristUserControl();
	position();

}
task two(){
	wriststeady();
}
task three(){
easy();

}
task four(){
position();
}
task five(){
		while(1){
		StartTask(two);
		StartTask(four);
    }
}
// autonomous plays are named as follows auton[Score-Result][starting tile]
void autonFiveLeft(){ //autonFiveLEft grabs the five stack, starts on left tile.
	SensorValue[rightIEM]=0;
	SensorValue[leftIEM]=0;
	strafeRight(127, .3 * clickspermeters);
  drive( .1 * clickspermeters, FORWARD, 70);
  wait1Msec(20);
  wrist(-127, 1100);
  //AArm(300 , LOWER, 60);
	wait1Msec(400);
  drive( .69 * clickspermeters, FORWARD, 80);
  StartTask(five);
  wrist(127, 750);
  wait1Msec(950);
  driveBackward(100, 300);
  wrist(10, 20);
  driveBackward(100, 300);
  aArm(2100, RAISE, 120);
  wrist(127, 300);
  SensorValue[rightIEM]=0;
	SensorValue[leftIEM]=0;
  strafeLeft(100, clickspermeters);
  turnLeft(60, 600);
  drive( .35 * clickspermeters, FORWARD, 70);
  wait1Msec(20);
  while(SensorValue[WristPot1] > 200){
  motor[leftWrist] = -127;
  motor[rightWrist] = -127;
  }
  motor[leftWrist] = 0;
  motor[rightWrist] = 0;
 driveBackward(100, 100);
  wait1Msec(500);
 driveBackward(0, 1000);
  }
void autonYellow(){ //autonFiveLEft grabs the five stack, starts on left tile.
	SensorValue[rightIEM]=0;
	SensorValue[leftIEM]=0;
	strafeLeft(127, .34 * clickspermeters);
  drive( .7 * clickspermeters, FORWARD, 70);
  wrist(-127, 1100);
  wait1Msec(400);
  drive( .28 * clickspermeters, FORWARD, 80);
  StartTask(five);
  wrist(127, 600);
  wait1Msec(900);
  wrist(10, 20);
  driveBackward(70, 900);
  aArm(1500, RAISE, 120);
  wrist(127, 200);
  drive(.27 * clickspermeters, FORWARD, 70);
 while(SensorValue[WristPot2] > 1900){
  motor[leftWrist] = -127;
  motor[rightWrist] = -127;
  }
  motor[leftWrist] = 0;
  motor[rightWrist] = 0;
  wait1Msec(800);
  driveBackward(90, 500);
  }
  void autonFiveRight(){ //autonFiveLEft grabs the five stack, starts on left tile.
	SensorValue[rightIEM]=0;
	SensorValue[leftIEM]=0;
	strafeLeft(127, .3 * clickspermeters);
  drive( .1 * clickspermeters, FORWARD, 70);
  wrist(-127, 1100);
  //AArm(300 , LOWER, 60);
	wait1Msec(400);
  drive( .6 * clickspermeters, FORWARD, 80);
  wait1Msec(20);
  StartTask(five);
  wrist(127, 850);
  wait1Msec(1050);
  driveBackward(100, 100);
  aArm(2100, RAISE, 120);
  wrist(127, 200);
  drive( .4 * clickspermeters, FORWARD, 70);
  wait1Msec(20);
   while(SensorValue[WristPot1] > 200){
  motor[leftWrist] = -127;
  motor[rightWrist] = -127;
  }
  motor[leftWrist] = 0;
  motor[rightWrist] = 0;
 driveBackward(100, 1000);
  wait1Msec(500);
 driveBackward(0, 1000);
  }



  void autonomousDecisions(){
	//Robot decides what autonomous to do after the LCD selection has been made
	if (auton == false)
		//No autonomous? Do nothing //SkillsPlaylist
	{
		autonFiveRight();
	}

	if (autonL == true)
		//This sets the Left Easy Code to run
	{
		autonFiveLeft();
	}
	else if (autonR== true)
	{
		autonYellow();
	}

}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////


void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

 //Clearing this should eliminate any drift the gyro builds over time
	wait1Msec(1000);
	SensorType(in8) = sensorGyro;
	wait1Msec(2000);
	//Needed for stabalization
	SensorFullCount[in8] = 3600;

  bLCDBacklight = true;
	//Set the LCD light to on
	SensorValue[in1] = 0;
	SensorValue[in2] = 0;
	SensorValue[rightIEM] = 0;
	SensorValue[leftIEM] = 0;
//	autonomousSelection();
	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
autonFiveLeft();
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{
		while(1 == 1){
		if (isrunning == false){

		StartTask(one);
		StartTask(two);
	  StartTask(three);
}
	  }
	}
}
