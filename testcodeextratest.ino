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

const int TURNTIME = 0;// needs to be set up after some calculations 
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
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  
  return distance;
}


// this is the main loop that actual will decide how the vehicle will travel
void loop() { // it should typical be going forward or turning and rarely going backwards
  
  forward(); // initiates movement to be forward
  hgFront(); // initiates 
  
  if ( UScontrol() <= tolerance){ // Constant check in front
      halt();
      hgLeft();
      delay(200);
                                    // if blocked in front
      if (UScontrol() > tolerance){ // but open in left then turn left 
        hgFront();
        leftTurn(); 
        delay(1000);
        halt();       
        }
             // if blocked in left and front
      else { // then look to the right
        hgFront();
        delay(50);
        hgRight();
        delay(200);
                                      // if it is open to the right 
        if (UScontrol() > tolerance){ // then turn right
          hgFront();
          delay(50);
          rightTurn();
          delay(1000);
          halt();
        }
        
        else{ // if every way is blocked 
          while(true){ // loop to continue
          
          hgFront();
          backward(); // vehicle goes backwards
          delay(500); // for half a second
          hgLeft();
          delay(200);
          
          if(UScontrol() > tolerance){ // checks left if open then turns left
            leftTurn();
            delay(1000);
            halt();
            hgFront();
            delay(50);
            break; // break is to exit the while loop not void loop
          }
          
          hgRight();
          delay(200);
          
          if(UScontrol() > tolerance){ // checks right if open then turns right
            rightTurn();
            delay(1000);
            halt();
            hgFront();
            delay(50);
            break; 
          }
          
          }// end of while loop  
        }// end of else (each way is blocked)
      }// end of else if then look right   
    }// end of initial check in front of vehicle

}// end of arduino void loop
//
//
//
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
//  
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
void forward(){ // forward both motors
	leftForward();
	rightForward();
}

void backward(){ // reverse both motors
  rightBackward();
  leftBackward();
 }

void halt(){ // stops both motors
	rightStop();
	leftStop();
 }
// -----------------------
//
// Timing Controls



// -----------------------
//
// 		Turns
void rightTurn(){ // left on right off to turn right
	leftForward();
	rightStop();
}

void leftTurn(){ // right on left off to turn left
	leftStop();
	rightForward();
}
//-----------------------
//
// 	   Sharp Turns
void sharpRightTurn(){ // left forward right back to turn right quickly
	leftForward();
	rightBackward();
}

void sharpLeftTurn(){ // right forward left back to turn left quickly
	leftBackward();
	rightForward();
}

//------------------------
//
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
  
