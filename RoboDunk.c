#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1, lSensor, sensorLineFollower)
#pragma config(Sensor, in2, mSensor, sensorLineFollower)
#pragma config(Sensor, in3, rSensor, sensorLineFollower)
#pragma config(Sensor, in4, gyro, sensorGyro)
#pragma config(Sensor, in6, arm, sensorPotentiometer)
#pragma config(Sensor, dgtl1, rEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl3, lEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl6, touch, sensorTouch)
#pragma config(Sensor, dgtl8, sonar, sensorSONAR_cm)
#pragma config(Sensor, I2C_1, rightIME, sensorQuadEncoderOnI2CPort, , AutoAssign )
#pragma config(Sensor, I2C_2, leftIME, sensorQuadEncoderOnI2CPort, , AutoAssign )
#pragma config(Sensor, I2C_3, armIME, sensorQuadEncoderOnI2CPort, , AutoAssign )
#pragma config(Motor, port2, rMotor, tmotorVex393_MC29, openLoop, reversed, driveRight, encoderPort, I2C_1)
#pragma config(Motor, port3, lMotor, tmotorVex393_MC29, openLoop, driveLeft, encoderPort, I2C_2)
#pragma config(Motor, port6, armMotor, tmotorVex393_MC29, openLoop, encoderPort, I2C_3)
#pragma config(DatalogSeries, 0, "LeftFollow", Sensors, Sensor, in1, 50)
#pragma config(DatalogSeries, 1, "MidFollow", Sensors, Sensor, in2, 50)
#pragma config(DatalogSeries, 2, "RightFollow", Sensors, Sensor, in3, 50)
//*!!Code automatically generated by 'ROBOTC' configuration wizard !!*//

//Global variables for line following, distance recording, and status of progress
int sonarVal = 100;

//This function will make the robot move straight forwards "int blocks" number of blocks on the grid of a table
void forwards(int blocks){
	motor[lMotor]= 127;
	motor[rMotor]= 127;
	wait1Msec(blocks*200/5.3*10);
}

//This function will make the robot turn 90 degrees to the left
void left(){
	motor[lMotor]= -127;
	motor[rMotor]= 127;
	wait1Msec(630);
}
//This function will make the robot turn 90 degrees to the right
void right(){
	motor[lMotor]= 127;
	motor[rMotor]= -127;
	wait1Msec(630);
}

//This function will make the robot travel backwards for a set amount of time by the parameter
void backwards(int time){
	motor[lMotor]= -100;
	motor[rMotor]= -100;
	wait1Msec(time);
}

//This function will make the robot "scoot" forwards a little bit because the forwards function is not flexible enough
void scoot(){
	motor[lMotor]= 60;
	motor[rMotor]= 60;
	wait1Msec(500);
}

//This function will move the arm upwards and the stop the arm movement after some time to pick up an object
void pickUpBall(){
	//Slightly move forwards
	motor[lMotor]= 40;
	motor[rMotor]= 40;

	//Move arm up, and stop arm
	motor[armMotor] = -80;
	wait1Msec(500);
	motor[armMotor] = 0;
}

//This function is the opposite of the "pickUpBall" function, and will revert the arm back to its normal position downwards
void armDown(){
	//Slightly move forwards
	motor[lMotor]= 40;
	motor[rMotor]= 40;

	//Move arm down, and stop arm
	motor[armMotor] = 80;
	wait1Msec(650);
	motor[armMotor] = 0;
}

task main()
{
	//Get the ball from the pole

	//While the robot is not the right distance away from the ball, scoot forwards
	while(sonarVal>13){
		scoot();											//Scoot forwards
		sonarVal=SensorValue[sonar]; 	//Check the distance from the ball
	}

	//Pick up the ball
	pickUpBall();



	//Go around the pole holding the ball

	backwards(500); //Go backwards
	right();				//Turn right
	forwards(2);		//Go forwards to evade the pole
	left();					//Turn left to face the end of the court
	forwards(5);		//Advance down the court, passing the pole
	left();					//Turn left, towards the middle
	forwards(2);		//Advance back to the centre of the court
	right();				//Turn right, to face the hoop



	//Travel towards the hoop

	//Reset sonar sensing variable
	sonarVal=100;

	//While the robot is the not the right distance away from the hoop, move towards it
	while(sonarVal>37){
		scoot();											//Scoot forwards
		sonarVal=SensorValue[sonar]; 	//Check the distance from the hoop
	}

	//Move arm down to dunk
	armDown();

}
