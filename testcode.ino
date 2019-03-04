/*
Description: (currently) mock code for our arduino movements/funtionality
Authors: Ethan, Lukas, Jacob, Gabby, Andrea, Henry.
Date(s): Feb - April 2019
*/
#include <Servo.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();


// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotoL = AFMS.getMotor(1);
Adafruit_DCMotor *myMotorR = AFMS.getMotor(2);


void setup() {
//According to the example code for Arduino Motor shield v2, this starts the shield.
AFMS.begin();
myMotorL->setSpeed(150);
myMotorR->setSpeed(150);
myMotorL->run(FORWARD);
myMotorL->run(FORWARD);
// turn on motor
myMotorL->run(RELEASE);
myMotorR->run(RELEASE);
}

void loop() {

}
// It appears that to control something over pwm on the arduino we simply have to use the analogWrite(); function. It doesn't look to require any extra libraries.

//moving
//forwards
//backwards (moving+turning+speed)

//moving as in turning (15deg incriments as many times as we need to get the desired turn in)
//15

//sensing things with sensor A

//sensing things with sensor B



// Main Motor Controls
void leftForward() {
	myMotorL->run(FORWARD); //starts the motor at default speed set above
}

void rightForward() {
	myMotorR->run(FORWARD); //starts the motor at default speed set above
}

void leftBackward() {
	myMotorL->run(BACKWARD); //starts the motor in reverse at default speed
}

void rightBackward() {
	myMotorR->run(BACKWARD); //starts the motor in reverse at default speed
}

void leftStop() {
	myMotorL->run(RELEASE); //stops the motor
}

void rightStop() {
	myMotorR->run(RELEASE); //stops the motor
}
//--------------------------------------------

// Servo Controls
//here

// ------------------------------------------
//											You are a Bold One.
// General Kenobi Controls    	(0_0)/			\\(0_0)//
void forward(){
	leftForward();
	rightForward();
}

 void backward(){
	 rightBackward();
	 leftBackward();
 }

 void stop(){
	 rightStop();
	 leftStop();
 }
// -----------------------

// 		Turns
void rightTurn(){
	leftForward();
	rightStop();
	delay(1000);
	leftStop();
}

void leftTurn(){
	leftStop();
	rightForward();
	delay(1000);
	rightStop();
}
//-----------------------

// 	   Sharp Turns
void sharpRightTurn(){
	rightBackward();
	leftForward();
	delay(1000);
	rightStop();
	leftStop();
}

void sharpLeftTurn(){
	leftBackward();
	rightForward();
	delay(1000);
	leftStop();
	rightStop();
}
//------------------------
