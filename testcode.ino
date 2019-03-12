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
Adafruit_DCMotor *myMotorL = AFMS.getMotor(1);
Adafruit_DCMotor *myMotorR = AFMS.getMotor(2);
Servo highGround;
Servo younglings;


int servpos = 90;

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


highGround.attach(9);
younglings.attach(10);

highGround.write(servpos);

}

void loop() {

hgLeft();
delay(5000);
hgFront();
delay(5000);
hgRight();
delay(5000);
hgFront();
delay(5000);





}

//moving as in turning (15deg incriments as many times as we need to get the desired turn in)
//15

//sensing things with sensor A

//sensing things with sensor B



// Main Motor Controls
void leftForward() {
	myMotorL->run(FORWARD); //starts the motor at default speed set above
}

void rightForward() {
	myMotorR->run(BACKWARD); //starts the motor at default speed set above
}

void leftBackward() {
	myMotorL->run(BACKWARD); //starts the motor in reverse at default speed
}

void rightBackward() {
	myMotorR->run(FORWARD); //starts the motor in reverse at default speed
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

void hgLeft(){
  highGround.write(180);
  
  }

void hgRight(){

  highGround.write(0);
  
}

void hgFront(){
  highGround.write(90);
  
  }



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
