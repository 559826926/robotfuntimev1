/*
Description: (currently) mock code for our arduino movements/funtionality
Authors: Ethan, Lukas, Jacob, Gabby, Andrea, Henry.
Date(s): Feb - April 2019
*/
#include <Servo.h>
#include <Adafruit_MotorShield.h>
//#include <DistanceGP2Y0A21YK.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Creates IR sensor object
//DistanceGP2Y0A21YK IR_Dist;


// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotorL = AFMS.getMotor(1);
Adafruit_DCMotor *myMotorR = AFMS.getMotor(2);

Servo highGround;
Servo younglings;

int servpos = 90; // this is the setting of original position of the servo
float tolerance = 8;

//setup the ultrasonic sensor pins
const int trigPin = 7;
const int echoPin = 8;
long duration;
int distance;

void setup() {
//According to the example code for Arduino Motor shield v2, this starts the shield.
AFMS.begin();
//IR_Dist.begin(A0); // starts the IR sensor at port A0
myMotorL->setSpeed(100);
myMotorR->setSpeed(100);
myMotorL->run(FORWARD);
myMotorL->run(FORWARD);
// turn on motor
myMotorL->run(RELEASE);
myMotorR->run(RELEASE);

//servo setup
highGround.attach(9);
younglings.attach(10);

highGround.write(servpos);
younglings.write(servpos);

// setup for the ultrasonic sensor
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}

float UScontrol() {
  //Ultrasonic sensor looks forward for distance.
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
  
  }



void loop() {

    if (UScontrol() >tolerance){
      backward();
      }
    if ( UScontrol() <= tolerance){
      halt();
      hgLeft();
      delay(1000);
      if (UScontrol() > tolerance){
        leftTurn(); 
        delay(1000); 
        hgFront();      
        }
      else if (UScontrol() <= tolerance){
        hgFront();
        delay(50);
        hgRight();
        delay(1000);
        if (UScontrol() <= tolerance)

          
          rightTurn();
          delay(1000);
          hgFront();
          delay(50);
        }      
      }   
    







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
// here
void hgLeft(){
  highGround.write(180);
  
  }

void hgRight(){

  highGround.write(0);
  
}

void hgFront(){
  highGround.write(90);
  
  }

void yLeft(){
  younglings.write(180);
  
  }

void yRight(){

  younglings.write(0);
  
}

void yFront(){
  younglings.write(90);
  
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

 void halt(){
	 rightStop();
	 leftStop();
 }
// -----------------------

// Timing Controls



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

//    IR Sensor Control

//int getIRDistance(){
	//return IR_Dist.getDistanceCentimeter();
//}

// Ultrasonic Control

/*float UScontrol() {
  //Ultrasonic sensor looks forward for distance.
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
  
  }*/
  
