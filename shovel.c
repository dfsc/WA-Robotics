#pragma config(Sensor, in1,    ArmPot1,        sensorPotentiometer)
#pragma config(Sensor, in2,    ArmPot2,        sensorPotentiometer)
#pragma config(Sensor, in3,    WristPot1,      sensorPotentiometer)
#pragma config(Sensor, in4,    WristPot2,      sensorPotentiometer)
#pragma config(Sensor, in5,    Gyro,           sensorGyro)
#pragma config(Motor,  port1,           leftFrontMotor, tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port2,           leftBackMotor, tmotorVex393, openLoop)
#pragma config(Motor,  port3,           leftTopArm,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           leftBottomArm, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           rightWrist,    tmotorServoContinuousRotation, openLoop,)
#pragma config(Motor,  port6,           leftWrist,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port7,           rightTopArm,   tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port8,           rightBottomArm, tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port9,           rightFrontMotor, tmotorVex393, openLoop)
#pragma config(Motor,  port10,          rightBackMotor, tmotorVex393, openLoop)

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
/*==========================================
(c) 2013 Woodward Academy Robotics under GPLv3
==========================================*/
// ArmPot1 = 2833-2836, ArmPot2 = 4095, WristPot1 = 2270, WristPot2 = 2324 ArmPot2 = dud

// Autonomous codes
#define RAISE 1
#define LOWER 0

int power, time, timeMS;
char direction;
//  Time is to be put in seconds when referencing a function, it will be converted to seconds by the function
//  For example arm(127, 5); would use the arm at full power for 5 seconds
void timeConvert(int time){
	int timeMS = time * 1000;
}

void arm(int power, int time){
	timeConvert(time);
	motor[leftTopArm] = power;
	motor[leftBottomArm] = power;
	motor[rightTopArm] = power;
	motor[rightBottomArm] = power;
	wait1Msec(timeMS);
}

void wrist(int power, int time){
	timeConvert(time);
	motor[rightWrist]  = power;
	motor[leftWrist] = power;
	wait1Msec(timeMS);
}

void driveForward(int power, int time){
	timeConvert(time);
	motor[rightFrontMotor] = -power;
	motor[rightBackMotor] = -power;
	motor[leftFrontMotor] = power;
	motor[leftBackMotor] = power;
	wait1Msec(timeMS);
}

void driveBackward(int power, int time){
	timeConvert(time);
	motor[rightFrontMotor] = power;
	motor[rightBackMotor] = power;
	motor[leftFrontMotor] = -power;
	motor[leftBackMotor] = -power;
	wait1Msec(timeMS);
}

void turnLeft(int power, int time){
	timeConvert(time);
	motor[rightFrontMotor] = power;
	motor[rightBackMotor] = -power;
	motor[leftFrontMotor] = -power;
	motor[leftBackMotor] = power;
	wait1Msec(timeMS);
}

void turnRight(int power, int time){
	timeConvert(time);
	motor[rightFrontMotor] = -power;
	motor[rightBackMotor] = power;
	motor[leftFrontMotor] = power;
	motor[leftBackMotor] = -power;
	wait1Msec(timeMS);
}

void Aarm(int positionR, char direction, char power)
{
	//This function is for arm raising
	if(direction == RAISE)
	{
		//if direction is to raise the arm
		while (SensorValue[armPot2] > positionR)// arm up for high goal
		{
			// while both potentiometers are less than a set position power both arms
 			motor[leftTopArm] = power;
			motor[leftBottomArm] = power;
			motor[rightTopArm] = power;
			motor[rightBottomArm] = power;
		}
	}
	//End of RAISE

	else //LOWER
	{
		while(SensorValue[armPot2] < positionR)// arm down
		{   // while both potentiometers are more than a set position power both arms negatively.

	motor[leftTopArm] = power;
	motor[leftBottomArm] = power;
	motor[rightTopArm] = power;
	motor[rightBottomArm] = power;
		}
	}
	motor[port3]=0;   motor[port4]=0;
	motor[port7]=0;   motor[port8]=0;
	wait1Msec(20);
	//stop arm
}

void strafeLeft(int power, int time){
	timeConvert(time);
	motor[rightFrontMotor] = -power;
	motor[rightBackMotor] = -power;
	motor[leftFrontMotor] = -power;
	motor[leftBackMotor] = -power;
	wait1Msec(timeMS);
}

void strafeRight(int power, int time){
	timeConvert(time);
	motor[rightFrontMotor] = power;
	motor[rightBackMotor] = power;
	motor[leftFrontMotor] = power;
	motor[leftBackMotor]  = power;
	wait1Msec(timeMS);
}

// driver control code
void driverControl(){
	  int X2 = 0, Y1 = 0, X1 = 0, threshold = 15;
/*
  //Loop Forever
  while(1 == 1)
  {
    //Create "deadzone" for Y1/Ch3
    if(abs(vexRT[Ch3]) > threshold)
      Y1 = vexRT[Ch3];
    else
      Y1 = 0;
    //Create "deadzone" for X1/Ch4
    if(abs(vexRT[Ch4]) > threshold)
      X1 = vexRT[Ch4];
    else
      X1 = 0;
    //Create "deadzone" for X2/Ch1
    if(abs(vexRT[Ch1]) > threshold)
      X2 = vexRT[Ch1];
    else
      X2 = 0;

    //Remote Control Commands
    motor[rightFrontMotor] = Y1 - X2 - X1;
    motor[rightBackMotor] =  Y1 - X2 + X1;
    motor[leftFrontMotor] = Y1 + X2 + X1;
    motor[leftBackMotor] =  Y1 + X2 - X1;
  }
*/	  motor[RightFrontMotor] = vexRT[Ch4] - vexRT[Ch2] - vexRT[Ch1];
    motor[rightBackMotor] =  vexRT[Ch4] - vexRT[Ch2] + vexRT[Ch1];
    motor[LeftFrontMotor] = vexRT[Ch4] + vexRT[Ch2] + vexRT[Ch1];
    motor[leftBackMotor] =  vexRT[Ch4] + vexRT[Ch2] - vexRT[Ch1];
}





// Wrist and arm code
void armUserControl(){
  motor[rightTopArm] = 127 * vexRT[Btn6U] - 127 * vexRT[Btn6D];
	motor[rightBottomArm] = 127 * vexRT[Btn6U] - 127 * vexRT[Btn6D];
	motor[leftTopArm] = 127 * vexRT[Btn6U] - 127 * vexRT[Btn6D];
	motor[leftBottomArm] = 127 * vexRT[Btn6U] - 127 * vexRT[Btn6D];

  }
void wristUserControl(){
	motor[rightWrist] = 127 * vexRT[Btn5U] - 127 * vexRT[Btn5D];
	motor[leftWrist] = 127 * vexRT[Btn5U] - 127 * vexRT[Btn5D];
}

void position(){
if (vexRT[Btn6U] == 0 && vexRT[Btn6D] == 0 && SensorValue[ArmPot1] > 3000 && SensorValue[ArmPot1] < 3900){
	  motor[rightTopArm] = 25;
		motor[rightBottomArm] = 25;
		motor[leftTopArm] = 25;
		motor[leftBottomArm] = 25;
	}
}
//  && SensorValue[ArmPot1] > 3000
void wriststeady(){
    while(1){
    	if (abs(SensorValue[WristPot1]+SensorValue[ArmPot1] - (2408 + 2765)) < 50){
       motor[leftWrist] = 10;
	     motor[rightWrist]= 10;
      }
      else{

        if(SensorValue[WristPot1]+SensorValue[ArmPot1] < (2408 + 2765)){
       motor[leftWrist] = 50;
	     motor[rightWrist]= 50;
	   }
        else{
       motor[leftWrist] = -30;
	     motor[rightWrist]= -30;
	   }
	     }
    }

}

// autonomous plays are named as follows auton[Score-Result][starting tile]
task autonFiveLeft(){ //autonFiveLeft grabs the five stack, starts on left tile.
  strafeRight(127, 1);
  driveForward(127, 1);
  strafeLeft(127, 1.5);
  driveForward(127, .5);
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

task main(){
	// driver control
	while(1 == 1){
		startTask(one);
		startTask(two);
	}
}
