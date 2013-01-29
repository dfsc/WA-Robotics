#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    leftPot,        sensorPotentiometer)
#pragma config(Sensor, in2,    rightPot,       sensorPotentiometer)
#pragma config(Sensor, I2C_1,  rightIEM,       sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  leftIEM,        sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           frontLeftMotor, tmotorVex393, openLoop)
#pragma config(Motor,  port2,           backLeftMotor, tmotorVex393, openLoop, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port3,           topLeftLift,   tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port4,           bottomLeftLift, tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port5,           rightIntake,   tmotorVex269, openLoop)
#pragma config(Motor,  port7,           bottomRightLift, tmotorVex269, openLoop)
#pragma config(Motor,  port6,           leftIntake,    tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port8,           topRightLift,  tmotorVex269, openLoop)
#pragma config(Motor,  port9,           backRightMotor, tmotorVex393, openLoop, reversed, encoder, encoderPort, I2C_2, 1000)
#pragma config(Motor,  port10,          frontRightMotor, tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*==========================================
(c) 2013 Woodward Academy Robotics under GPLv3
==========================================*

#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)


#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

#define FORWARD 1
#define BACKWARD 0
#define RAISE 1
#define LOWER 0
#define RIGHT 1
#define LEFT 0
//define characters

float metersperclick = .000516;
//clicks in a meter
float clickspermeters = 1936.93;
//encoder clicks per 1 meter

void userArm(int positionR,int positionL ,char direction, char power);
void swivel(int distance, char direction, int power);
void drive(int distance, char direction, int power);
void arm(int positionR,int positionL ,char direction, char power);
void turn(int position, char direction, int power);
void autoIntake(int time, int power);
void driveTime(int time, char direction, int power);
void armTime(int time, char direction, int power);
//functions for drive, arm, and intake during autonomous

string either = "either R/L";
string center = "press center";
string sure = "Are you sure?";
string one = "Auto or Skills?";
string two = "left // right";
string hard = "Basic or Hard?";
//strings for LCD

bool auton = false;
bool auton1 = false;
int rightLeft = 0;
int firstchoice = 0;
int LCDselect = 0;
bool autonL = false;
bool autonR = false;
int easyHard = 0;
// LCD variables and booleans

const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;
// constants for buttons

int rightMaxPot = 2150;
int leftMaxPot = 2150;
int rightMinPot = 4080;
int leftMinPot = 4080;
// max and min for Potentionmeters



task leftLeftOne(){
	clearLCDLine(0);
	clearLCDLine(1);
	//clear LCD
	SensorValue[leftIEM] = 0;
	SensorValue[rightIEM] = 0;
	driveTime(350, FORWARD, 127);
	driveTime(200, BACKWARD, 127); //200 to 250 to 200
	//quick jerk to bring down intake
	swivel(880,LEFT,65); //630 to 600 to 610 to 600 to 630 to 650 to 670 to 690 to 750 to 770 to 800 to 780 to 750
	//swivel left to wall
	drive( .35 * clickspermeters, FORWARD, 70); //60 70 to .36
	wait1Msec(800);
	//drive to wall and pick up green sack
	driveTime(450, BACKWARD, 127);
	//drive backward
	turn(800, RIGHT, 55);//600 to 400 to 350 to 370 to 350 to 600 to 670 to 690 to 680 to 690 to 700 to 720 to 650 to 750 to 740
	armTime(200,RAISE,127); //raise arm to avoid tape //50 to 125 to 325 to 125 to 200
	//wait1Msec(50); replace waits with armTime
	// turn to trough
	drive(.65 * clickspermeters, FORWARD, 110);
	wait1Msec(50);
	armTime(300,LOWER,127);//lower the arm to contact ground // 125 5o 345 to 125 to 250 to 200 to 250
	//forward to yellow sack
	drive(.32 * clickspermeters, FORWARD, 70); // .33 to .31
	wait1Msec(1000);
	//drive forward to yellow sack and wait for 1 second
	driveTime(700, BACKWARD, 100);
	wait1Msec(50);
	//go backward
	armTime(1500, RAISE, 127);//950 to 1100 to 1300
	wait1Msec(10);
	//raise arm
	drive(.10 * clickspermeters, FORWARD, 40);
	drive(.46 * clickspermeters, FORWARD, 60); //.49 to .40 to .43
	//Forward to goal
	autoIntake(2000, -127); //why did this reverse? negative to positive to negative
	//Let sacks out
	driveTime(400, BACKWARD, 100);
	//back off
	//auton=false;
	if (auton == false){
		turn(1800,LEFT,60);
		driveTime(2000, BACKWARD, 100);
	}
}

task leftLeftTwo(){
	autoIntake(5000, 127); //6000 to to 5000 to 4500 to 4500
	// Use intake to pick up green
	autoIntake(3100, 0); //3300 to 3000 to 3300 to 3000 to 3600 to 2700 to 2400 to 2200 to 2000 to 2700 to 3000 to 3500
	// Do nothing with ifntake
	autoIntake(2200, 127); //2500 to 1000 to 2000 to 2200 to 2500 to 1750 from 2k
	//Use intake to pick up yellow
}

task leftRushOne(){
	clearLCDLine(0);
	clearLCDLine(1);
	//clear LCD
	//SensorValue[leftIEM] = 0;
	//SensorValue[rightIEM] = 0;
	driveTime(350, FORWARD, 127);
	driveTime(200, BACKWARD, 127);
	armTime(100,RAISE,127);
	swivel(330,LEFT,60);
	SensorValue[leftIEM] = 0;
	SensorValue[rightIEM] = 0;
	drive(.10 * clickspermeters,FORWARD,110); //10 to .15
	swivel(350,RIGHT,60); //360 to 340
	drive(.35 * clickspermeters,FORWARD,110); //.35 to .33
	armTime(100,LOWER,127);
	drive(.35 * clickspermeters,FORWARD,110);
	drive(.14 * clickspermeters, FORWARD,40);
	wait1Msec(275);
	driveTime(700, BACKWARD,100);
	armTime(1500, RAISE, 127);
	wait1Msec(10);
	drive(.10 * clickspermeters, FORWARD, 40);
	drive(.46 * clickspermeters, FORWARD, 60);
	autoIntake(2000, -127);
	driveTime(400, BACKWARD, 100);
	armTime(1100, RAISE, 120);
	driveTime(400, BACKWARD, 100);
	//auton = false;
	if (auton == false){
				armTime(1000,LOWER,100);
				driveTime(1000,BACKWARD,100);
	} //autoIntake(2000, 127);
}

task leftRushTwo(){
wait1Msec(3500); //possibly delete?
autoIntake(2000,127);
}

task leftRightOne(){
	clearLCDLine(0);
	clearLCDLine(1);
	//SensorValue[leftIEM] = 0;
	//SensorValue[rightIEM] = 0;
	//Clear LCD
	//jerk to get intake down
	//turn(830,RIGHT,40);
	// turn right 90 degrees
	//drive(.43* clickspermeters, FORWARD, 127);
	//forward to the line that the bonus sack is on999/8
	//turn(550,LEFT,40);
	//swivel turn to pick up yellow sack
	drive(.5 * clickspermeters, FORWARD, 100);
	wait1Msec(600);
	drive(.5 * clickspermeters, FORWARD, 100);
	//forward to yellow sack
	//turn to trough
	wait1Msec(300);
	//armTime(1150,RAISE,127);
	//raise arm
	swivel(310, RIGHT, 80);
	drive(.2 * clickspermeters, FORWARD, 127);
	//drive forward to goal
	drive(.2 * clickspermeters, FORWARD, 127);
	wait1Msec(900);
	driveTime(700, BACKWARD, 67);
	//Let sacks out5
  turn(550, LEFT, 80);
  armTime(1800,RAISE,127);
  drive(.58 * clickspermeters, FORWARD, 60); //127 to 80 //.53 to .58
  autoIntake(2050, -127);
  wait1Msec(200);
  driveTime(700, BACKWARD, 95);
  //auton=false;
	if (auton == false){
		turn(200,LEFT,60);
		driveTime(2000, BACKWARD, 100);
	}
  }

task leftRightTwo(){
	wait1Msec(1000); //1200
	autoIntake(2100, 127); //3400 to 3000 to 2300 to 2100
	wait1Msec(900);	 //1000 to 700 to 500
	autoIntake(2200, 127); //2200
	//continuous intake till sacks are picked up
}


task rightLeftOne(){
	clearLCDLine(0);
	clearLCDLine(1);
	//SensorValue[leftIEM] = 0;
	//SensorValue[rightIEM] = 0;
	//Clear LCD
	driveTime(400, FORWARD, 100);
	driveTime(200, BACKWARD, 100);
	// quick jerk to pull down intake
	swivel(850,LEFT,80);
	// turn left 90 degrees
	drive(.38* clickspermeters, FORWARD, 127);
	//forward to the line that the bonus sack is on
	armTime(250,RAISE,65);
	swivel(885 , RIGHT,70);
	//swivel turn to bonus sack
	armTime(250,LOWER,70);
	drive(.35 * clickspermeters, FORWARD, 100);
	//pick up bonus sack
	wait1Msec(300);
	turn(260,RIGHT,60);
	//turn to our closest trough
	armTime(1100,RAISE,127);
	//raise arm
	drive(.7 * clickspermeters, FORWARD, 60);
	//drive to goal
	swivel(260,LEFT,60);
	autoIntake(2000, -127);
	//let sacks out
	driveTime(300, BACKWARD, 100);
	//auton = false //remove this statement when not testing skills
	if(auton == false){
		driveTime(300,BACKWARD,100);
		armTime(1100,LOWER, 127);
		swivel(260,RIGHT, 60);
		driveTime(1000, BACKWARD,100);
		turn(400,LEFT,60);
		drive(2000, BACKWARD,100);
	}
}


task rightLeftTwo(){
	wait1Msec(2000);
	autoIntake(5000, 127);
	//continuous intake till yellow sack is picked up
}

//Wait for LCD Press--------------------------------------------------
void waitForPress(){
	while(nLCDButtons == 0){}
	wait1Msec(5);
}
//Wait for LCD Release------------------------------------------------
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

void pre_autonomous(){
	SensorType(in8) = sensorNone;
	//Clearing this should eliminate any drift the gyro builds over time
	wait1Msec(1000);
	SensorType(in8) = sensorGyro;
	wait1Msec(2000);
	//Needed for stabalization
	SensorFullCount[in8] = 3600;
	//sets the gyro to go back to 0 after it hits 3600(a full rotation)
	bLCDBacklight = true;
	//Set the LCD light to on
	SensorValue[in1] = 0;
	SensorValue[in2] = 0;
	SensorValue[rightIEM] = 0;
	SensorValue[leftIEM] = 0;
	//Clear ALL Sensors
}

void autonomousLeft(){
	StartTask(leftRightOne);
	StartTask(leftRightTwo); //multitask the leftHard
}

void autonomousLeft2(){
	StartTask(leftLeftOne);
	StartTask(leftLeftTwo); //multitask the leftEasy WORKING
}

void autonomousLeft3(){
	StartTask(leftRushOne);
	StartTask(leftRushTwo); //multitask the left one WO
}

void autonomousRight(){
	StartTask(rightLeftOne);
	StartTask(rightLeftTwo); //multitask the rightHard
}

void autonomousSelection(){
	//LCD selection in the form of asking questions
	while(LCDselect == 0  && nSysTime < 15000){
		//set the while loop for the choices
		while(firstchoice == 0  && nSysTime < 15000){
			displayLCDCenteredString(0, one);
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
			displayLCDCenteredString(0, two);
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

		while (autonL == true  && nSysTime < 15000) {
			//if left autonomous is selected
			displayLCDCenteredString(0, hard);
			// Easy, Rush, or Hard autonomous?
			if(nLCDButtons == leftButton){
				waitForRelease();
				easyHard = 1;
				autonL = false;
				//set variables for autonomous Left Easy
			}

			if(nLCDButtons == centerButton){
				waitForRelease();
				easyHard = 3; //this selects the rush mode
				autonL = false;
		}

			if(nLCDButtons == rightButton){
				waitForRelease();
				easyHard = 2;
				autonL = false;
				//set variables for autonomous Left Hard
			}
		}

		while (autonR == true) {
			//if right autonomous is selected
			displayLCDCenteredString(0, either);
			// Press Either L/R
			//Code for leftEasy can't be mirrored due to field positioning
			if(nLCDButtons == leftButton){
				waitForRelease();
				easyHard = 1;
				autonR = false;
				//set variables for autonomous right Hard
			}

			if(nLCDButtons == rightButton){
				waitForRelease();
				easyHard = 2;
				autonR = false;
				//set variables for autonomous right Hard
			}

		}

		displayLCDCenteredString(0, sure);
		//Are you sure with the Code selected?
		displayLCDCenteredString(1, center);
		//If sure, press center

		if(nLCDButtons == centerButton){
			//End LCD selections
			waitForRelease();
			LCDselect = 1;
		}

		if(nLCDButtons == leftButton){
			// User is unsure, clear ALL variables to restart selection
			resetLCD();
		}

		if(nLCDButtons == rightButton){
			// User is unsure, Clear ALL variables to restart Selection
			resetLCD();
		}
	}
}

void nothing(){
	//Do nothing code for when no autonomous is selected
	wait1Msec(100);
	clearLCDLine(0);
	clearLCDLine(1);
}

void armMotor(){
	if(vexRT[Btn6U] == 1){
		// If 6U is pressed, arm goes up
		motor[topRightLift] = 127;
		motor[topLeftLift] = 127;
		motor[bottomLeftLift] = 127;
		motor[bottomRightLift] = 127;
	}
	else if(vexRT[Btn6D] == 1){
		// If 6D is pressed, arm goes down
		motor[topRightLift] = -127;
		motor[topLeftLift] = -127;
		motor[bottomLeftLift] = -127;
		motor[bottomRightLift] = -127;
	}
	else{
		// otherwise, do nothing
		motor[topRightLift] = 0;
		motor[topLeftLift] = 0;
		motor[bottomLeftLift] = 0;
		motor[bottomRightLift] = 0;
	}

	if(vexRT(Btn8U) == 1){
		//If 8U is pressed, bring arm to maximum height
		userArm(rightMaxPot,leftMaxPot,RAISE ,127);
	}
	else if(vexRT(Btn8D) == 1){
		//If 8D is pressed, bring arm to minimum height
		userArm(rightMinPot,leftMinPot,LOWER ,127);
	}
}
void highGoal(){
	//highGoal macro
	if(vexRT[Btn7U]==1){
		driveTime(450,BACKWARD, 127);
		driveTime(450,FORWARD, 127);
	}
}

void driveControl(){
	//4 motor drive control
	motor[frontLeftMotor] = vexRT[Ch3];
	motor[backLeftMotor]  = vexRT[Ch3];
	motor[frontRightMotor] = vexRT[Ch2];
	motor[backRightMotor]  = vexRT[Ch2];
}

void intake(){
	if(vexRT[Btn5U] == 1){
		//If button 5U is pressed, intake is grabbing sacks inward
		motor[leftIntake] = 127;
		motor[rightIntake] = 127;
	}
	else if(vexRT[Btn5D] == 1){
		//If button 5D is pressed, intake is pushing sacks outwards
		motor[leftIntake] = -127;
		motor[rightIntake] = -127;
	}
	else{
		//otherwise, do nothing
		motor[leftIntake] = 0;
		motor[rightIntake] = 0;
	}
}



void autonomousDecisions(){
	//Robot decides what autonomous to do after the LCD selection has been made
	if (auton == false){
		//No autonomous? Do nothing //SkillsPlaylist
		autonomousLeft2();
	}

	if (rightLeft == 1 && easyHard == 1){
		//This sets the Left Easy Code to run
		autonomousLeft2();
	}
	else if (rightLeft == 1 && easyHard == 3){
		autonomousLeft3();
	}

	else if(rightLeft == 1 && easyHard == 2){
		//This sets the Left Hard Code to run
		autonomousLeft();
	}

	if (rightLeft == 2 && easyHard == 1){
		//This sets the Right Easy code to run
		autonomousRight();
	}

	if (rightLeft == 2 && easyHard == 2){
		//This sets the Right Hard code to run
		autonomousRight();
	}
}

void pre_auton(){
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;
	pre_autonomous();
	//autonomousSelection();
	//autonomous selection
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

task autonomous(){ //autonomous selection AUTOSELECT
//switchup
 	autonomousRight();
 	if (auton = false){
 		autonomousRight()		//put first play here
 		while(nLCDButtons == 0){}
		waitForRelease();
 		autonomousLeft();//second play
 		while(nLCDButtons == 0){}
		waitForRelease();
 		autonomousLeft2();//third play here
 		while(nLCDButtons == 0){}
		waitForRelease();
 		autonomousLeft3();// fourth play here
 	//autonomousLeft();
	//autonomousLeft2();
	//autonomousLeft3();

 		//autonomousDecisions();
 	}
}

//////////////////////////////autonomousLeft//////////////////////////////////////////////////////
//4
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol(){
	// User control code here, inside the loop

	while (true){
		driveControl();//joystick controls
		intake(); //intake control
		armMotor(); // arm control
		highGoal(); // macro control for highGoal
	}
}

void turn(int position, char direction, int power){
	//This function is for turning
	SensorValue[in8]=0;
	//Clear gyro
	if(direction == LEFT){
		//If direction == Left
		while(abs(SensorValue[in8]) < position){
			//While the gyro is less than a set degrees, turn Left
			motor[port1]= -power;
			motor[port9]= power;
			motor[port2]= -power;
			motor[port10]=power;
		}
	}
	//end of LEFT turn
	else{
		//if direction == right
		while(abs(SensorValue[in8]) < position){
			//While the gyro is less than a set degrees, turn right
			motor[port1]=power;
			motor[port9]=-power;
			motor[port2]=power;
			motor[port10]=-power;
		}
	} //end of RIGHT turn
	motor[port1]= 0;
	motor[port9]=0;
	motor[port2]= 0;
	motor[port10]=0;
	wait1Msec(20); //stop turning
}

void arm(int positionR,int positionL ,char direction, char power){
	//This function is for arm raising
	if(direction == RAISE){
		//if direction is to raise the arm
		while (SensorValue[rightPot] > positionR && SensorValue[leftPot] > positionL){// arm up for high goal
			// while both potentiometers are less than a set position power both arms
			motor[topRightLift]=power;    motor[bottomLeftLift]=power;
			motor[topLeftLift]=power;    motor[bottomRightLift]=power;
		}
	}
	//End of RAISE

	else //LOWER
	{
		while(SensorValue[rightPot] < positionR && SensorValue[leftPot] < positionL){// arm down. while both potentiometers are more than a set position power both arms negatively.
			motor[topRightLift]=-power;   motor[bottomLeftLift]=-power;
			motor[topLeftLift]=-power;   motor[bottomRightLift]=-power;
		}
	}
	motor[port3]=0;   motor[port4]=0;
	motor[port7]=0;   motor[port8]=0;
	wait1Msec(20);
	//stop arm
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
				motor[port9]=power;
				motor[port2]=power;
				motor[port10]=power;
			}
			else if (abs(turnPower) > 30 && abs(SensorValue[leftIEM]) > abs(SensorValue[rightIEM])){	// If rightEncoder has counted more encoder counts
				// Turn slightly right
				motor[port1]=power;
				motor[port9]=power-10;
				motor[port2]=power;
				motor[port10]=power-10;
				}else{	// Only runs if leftEncoder has counted more encoder counts
				motor[port1]=power-10;
				motor[port9]=power;
				motor[port2]=power-10;
				motor[port10]=power;
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

void autoIntake(int time,int power){
	//Autonomous Intake Collection
	motor[port5]=power;
	motor[port6]=power;
	wait1Msec(time);
	//Use intake at power, relying on time
	motor[port5]=0;
	motor[port6]=0;
	wait1Msec(20);
	//turn motors off
}

void swivel(int distance, char direction, int power){
	//Swivel here is defined as making a turn using only one motor
	SensorValue[rightIEM]=0;  SensorValue[leftIEM]=0;
	SensorValue[in8] = 0;
	// clear encoders
	if(direction == LEFT){
		//if direction = LEFT
		while(abs(SensorValue[in8]) < distance){
			//turn left until gyro is at a certain degrees
			motor[port1]=0;
			motor[port2]=0;
			motor[port9]=power;
			motor[port10]=power;
			//move right motors at power, while left motors = 0
		}
	}
	//end of Left
	else{ //right
		while(abs(SensorValue[in8]) < distance){
			//turn right until gyro is at a certain degrees
			motor[port1]=power;
			motor[port2]=power;
			motor[port9]=0;
			motor[port10]=0;
			//move right motors at power, while left motors = 0
		}
	}
	motor[port1]=0;
	motor[port9]=0;
	motor[port2]=0;
	motor[port10]=0;
	wait1Msec(20);
	//turn motors off
}

void driveTime(int time, char direction, int power){
	//This function is for driving forward using time. Only used for VERY SHORT distances
	if(direction == FORWARD){ // forward move
		// Move Forward until time has passed
		motor[port1]=power;
		motor[port9]=power;
		motor[port2]=power;
		motor[port10]=power;
		wait1Msec(time);
	}
	//end of forward move
	if(direction == BACKWARD){ //backward move
		// move backward until time has passed
		motor[port1]= -power;
		motor[port2]= -power;
		motor[port9]= -power;
		motor[port10]= -power;
		wait1Msec(time);
	}//end of backwards move
	motor[port1]=0;
	motor[port9]=0;
	motor[port2]=0;
	motor[port10]=0;
	wait1Msec(20);
	//turn motors off
}


void userArm(int positionR,int positionL ,char direction, char power){
	//This function is for arm raising + user control
	int correction = abs(SensorValue[rightPot]) - abs(SensorValue[leftPot]);
	if(direction == RAISE){
		//if direction is to raise the arm
		while (SensorValue[rightPot] > positionR && SensorValue[leftPot] > positionL){ // arm up for high goal
			// while both potentiometers are less than a set position power both arms
			motor[frontLeftMotor] = vexRT[Ch3];
			motor[backLeftMotor]  = vexRT[Ch3];
			motor[frontRightMotor] = vexRT[Ch2];
			motor[backRightMotor]  = vexRT[Ch2];

			if(vexRT[Btn8R] == 1)
				break;


			if (abs(correction) < 50){ // arm straightening code
				motor[topRightLift] = power;
				motor[topLeftLift] = power;
				motor[bottomLeftLift] = power;
				motor[bottomRightLift] = power;
			}
			else if (abs(correction) > 50 && abs(SensorValue[leftPot]) > abs(SensorValue[rightPot])){	// arm straightening code
				motor[topRightLift] = power;
				motor[topLeftLift] = power-20;
				motor[bottomLeftLift] = power-20;
				motor[bottomRightLift] = power;
			}
			else{	// arm straightening code
				motor[topRightLift] = power-20;
				motor[topLeftLift] = power;
				motor[bottomLeftLift] = power;
				motor[bottomRightLift] = power-20;
			}
		}
	}
	//End of RAISE
	else{ //LOWER
		while(SensorValue[rightPot] < positionR && SensorValue[leftPot] < positionL){ // arm down
			// while both potentiometers are more than a set position power both arms negatively.
			motor[frontLeftMotor] = vexRT[Ch3];
			motor[backLeftMotor]  = vexRT[Ch3];
			motor[frontRightMotor] = vexRT[Ch2];
			motor[backRightMotor]  = vexRT[Ch2];

			if(vexRT[Btn8R] == 1)
				break;


			if (abs(correction) < 50){ // arm straightening code
				// Move Forward
				motor[topRightLift] = -power;
				motor[topLeftLift] = -power;
				motor[bottomLeftLift] = -power;
				motor[bottomRightLift] = -power;
			}
			else if (abs(correction) > 50 && abs(SensorValue[leftPot]) > abs(SensorValue[rightPot])){	// arm straightening code
				// Turn slightly right
				motor[topRightLift] = -power;
				motor[topLeftLift] = -power+20;
				motor[bottomLeftLift] = -power+20;
				motor[bottomRightLift] = -power;
			}
			else{	// arm straightening code
				motor[topRightLift] = -power+20;
				motor[topLeftLift] = -power;
				motor[bottomLeftLift] = -power;
				motor[bottomRightLift] = -power+20;
			}
		}
	}
	motor[port3]=0;
	motor[port4]=0;
	motor[port7]=0;
	motor[port8]=0;
	wait1Msec(20);
	//stop arm
}
void armTime(int time, char direction, int power){
	//This function is for moving the arm up for time
	if(direction == RAISE){ // arm up
		// raise arm until X amount of time has passed
		motor[port3]=power;
		motor[port4]=power;
		motor[port7]=power;
		motor[port8]=power;
		wait1Msec(time);
	}

	if (direction == LOWER){ //arm down
		// move arm down until X amount of time has passed
		motor[port3]= -power;
		motor[port4]= -power;
		motor[port7]= -power;
		motor[port8]= -power;
		wait1Msec(time);
	}
	motor[port3]=0;
	motor[port4]=0;
	motor[port7]=0;
	motor[port8]=0;
	wait1Msec(20);
	//turn motors off
}
