/*
Description: code for our arduino movements/funtionality
Authors: Ethan, Lukas, Jacob, Gabby, Andrea 
Special thanks to: Mr. David Weber (our sponsor) and Henry (our assistant)  
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
//Servo younglings;

int servpos = 90; // this is the setting of original position of the servo
float tolerance = 20.0;

//setup the ultrasonic sensor pins
const int trigPin = 7;
const int echoPin = 8;

const int TURNTIME = 750; // needs to be set up after some calculations 
long duration;
float distance;

int Lspeed = 75;
int Rspeed = 65;

void setup() {
//According to the example code for Arduino Motor shield v2, this starts the shield.
AFMS.begin();

//IR_Dist.begin(A0); // starts the IR sensor at port A0
// Killed off because of lack of time, lesser reliability, and inability to find assisting programs for sensor that worked properly

myMotorL->setSpeed(Lspeed);
myMotorR->setSpeed(Rspeed);
myMotorL->run(FORWARD);
myMotorR->run(FORWARD);
// turn on motor
myMotorL->run(RELEASE);
myMotorR->run(RELEASE);

//servo setup
highGround.attach(9);
//younglings.attach(10);

highGround.write(servpos);
//younglings.write(servpos);

// setup for the ultrasonic sensor
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input

forward();
hgFront();
}

float UScontrol() {  //Ultrasonic sensor looks forward for distance.
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
    
  return distance;
}

// this is the main loop that actual will decide how the vehicle will travel
void loop() { // it should typical be going forward or turning and rarely going backwards

  if(UScontrol() <= tolerance){ // Constant check in front
     halt();
     hgLeft();
     delay(1000);
                                   // if blocked in front
     if(UScontrol() > tolerance){ // but open in left then turn left 
       hgFront();
       leftTurn();
               
     }
                // if blocked in left and front
     else{      // then look to the right
       hgFront();
       delay(150);
       hgRight();
       delay(1000);
                                      // if it is open to the right 
       if (UScontrol() > tolerance){  // then turn right
         hgFront();
         delay(50);
         rightTurn();
       }
        
       else{            // if every way is blocked 
         while(true){   // loop to continue
          
          hgFront();
          backward(); // vehicle goes backwards
          delay(1000); // for half a second
          halt();
          hgLeft();
          delay(1000);
          
          if(UScontrol() > tolerance){ // checks left if open then turns left
            leftTurn();
            hgFront();
            delay(150);
            break; // break is to exit the while loop not void loop
          }
          
          hgRight();
          delay(1000);
          
          if(UScontrol() > tolerance){ // checks right if open then turns right
            rightTurn();
            hgFront();
            delay(50);
            break; 
          }
          
        }  // end of while loop  
      }    // end of else (each way is blocked)
    }      // end of else then look to the right     
  }        // end of initial check in front of vehicle
}          // end of arduino void loop


//
//
//
// Main Motor Controls
void leftForward() {
	myMotorL->run(BACKWARD); //starts the motor at default speed set above
}

void rightForward() {
	myMotorR->run(FORWARD); //starts the motor at default speed set above
}

void leftBackward() {
	myMotorL->run(FORWARD); //starts the motor in reverse at default speed
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
//
// Servo Controls
// 
void hgLeft(){
  highGround.write(180); // turns the servo with US sensor to left 
  }

void hgRight(){
  highGround.write(0); // to the right
}

void hgFront(){
  highGround.write(90); // to the front of vehicle
  }
  
/* this was servo for IR sensor which was canceled do to time and being less reliable
void yLeft(){
  younglings.write(180);
}

void yRight(){
  younglings.write(0);
}

void yFront(){
  younglings.write(90);
}

*/
// ------------------------------------------
//								You are a Bold One.
// General Kenobi Controls    	(0_0)/			\\(0_0)//
//
// An attempt was made 
//
void forward(){ // forward both motors
	leftForward();
	rightForward();
}

void backward(){ // reverse both motors
  rightBackward();
  leftBackward();
}

void halt(){ // stops both motors
	backward();
  delay(150);
	rightStop();
	leftStop();
} 
// -----------------------
//
// 		Turns
void rightTurn(){ // left on right off to turn right
	myMotorL->setSpeed(160);
  myMotorR->setSpeed(80);
	leftForward();
  rightBackward();
  delay(TURNTIME);
  myMotorL->setSpeed(Lspeed);
  myMotorR->setSpeed(Rspeed);
  halt();
  delay(1000);
  forward();
  hgFront();
}

void leftTurn(){ // right on left off to turn left
	myMotorR->setSpeed(155);
  myMotorL->setSpeed(85);
  rightForward();
  leftBackward();
  delay(TURNTIME);
  myMotorL->setSpeed(Lspeed);
  myMotorR->setSpeed(Rspeed);
  halt();
  delay(1000);
  forward();
  hgFront();
}
//-----------------------
//
/* 	   Sharp Turns
void sharpRightTurn(){ // left forward right back to turn right quickly
	leftForward();
	rightBackward();
}

void sharpLeftTurn(){ // right forward left back to turn left quickly
	leftBackward();
	rightForward();
}
------------------------

//
//    IR Sensor Control

int getIRDistance(){
	return IR_Dist.getDistanceCentimeter();
}

// Ultrasonic Control

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
*/
  
