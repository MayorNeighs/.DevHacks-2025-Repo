// C++ code4
#include <Servo.h>  // Include the Servo library
#include <avr/power.h> //Only necessary for 8Mhz arduino. Comment out for 16Mhz arduino.

Servo fan;

//Digital pin for the continous servo
const byte fanPin = 6;

//Variables for random choices
long randClean; //Randomize cleaning or not cleaning
long randTurn; //Randomize the turning of the DOOMBA

// Variables for millis timing
unsigned long previousCleanTime = 0;
unsigned long previousTurnTime = 0;

//Event times for everything
unsigned long eventClean = 1000;  //event happens every one second
unsigned long eventTurn = 2000; //event happens every 60 seconds

//Directions
/*
right = 1;
left = 2;
straight = 3;
*/

//Motor pins for bottom motor
const byte motorPin1 = 3; //Power pin for motor, connected to pin 3 on input 1
const byte motorPin2 = 5; //Ground pin for motor, connect to pin 5 on input 2

//Motor pins for top motor
const byte motorPin3 = 10; //Ground pin for motor, connected to pin 9 on input 3
const byte motorPin4 = 9; //Power pin for motor, connected to pin 10 on input4

//Digital pins for red LEDs
const byte red1 = 7; //Red LED on the right
const byte red2 = 8; //Red LED on the left

//Digital pins for ultrasonic sensor
const byte trigPin = 12;
const byte echoPin = 11;

//Variables for the ultrasonic sensor for distance calculations
int inches = 0;
int cm = 0;

// Sending a signal for the ultrasonic sensor
long readUltrasonicDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  digitalWrite(triggerPin, HIGH);
  digitalWrite(triggerPin, LOW);

  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);  // Return the sound wave travel time in microseconds
}

void setup()
{
  clock_prescale_set (clock_div_2); //Only necessary for 8Mhz arduino. Comment out for 16Mhz arduino.

  // Initialize serial communication
  Serial.begin(9600);
  
  //Setting pins as input or output
  
  //Motor pins
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
 
  //Ultrasonic sensor configuration
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  //Setting LEDs as output
  pinMode(red1, OUTPUT);
  pinMode(red2, OUTPUT);
  
  //Initialize servo
  fan.attach(fanPin, 500, 2500);
  
  //if analog input pin 0 is unconnected, random analog
  //noise will cause the call to randomSeed() to generate
  //different seed numbers each time the sketch runs.
  //randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
  
  //DOOMBA starts in cleaning mode and moves forward
  fan.write(180);
  //Moving straight
  
  //Top motor is going forward
  analogWrite(motorPin1, 255); 
  analogWrite(motorPin2, 0);
  
  //Bottom motor is going forward
  analogWrite(motorPin3, 255);
  analogWrite(motorPin4, 0);
  
}

void loop()
{
  unsigned long currentTime = millis(); //always keep currentTime = Millis at top
  
  //Measure the distance using the ultrasonic sensor
  cm = 0.01723 * readUltrasonicDistance(trigPin, echoPin);
  inches = cm / 2.54;  // Convert cm to inches
  
  //Event time for cleaning or not cleaning
  if (currentTime - previousCleanTime >= eventClean) {
    //Randomly deciding if it's cleaning time or not
    randClean = random(1, 3); //1 = cleaning, 2 = not cleaning
  }
  
  //Code for if DOOMBA is cleaning or not cleaning
  if (randClean == 1) {
    fan.write(180);
    digitalWrite(red1, LOW);
    digitalWrite(red2, LOW);
  } else if (randClean == 2) {
    fan.write(0);
    digitalWrite(red1, HIGH);
    digitalWrite(red2, HIGH);
    previousCleanTime = currentTime;
  }
  
  //Event time for turning of DOOMBA
  if (currentTime - previousTurnTime >= eventTurn) {
    //Randomly choosing turning for DOOMBA
    randTurn = random(1, 4); //1 = right, 2 = left, 3 = straight
    previousTurnTime = currentTime;
  }
  
  if (cm >= 20) { //If DOOMBA doesn't detect 20cm something in front of it
      
  //Movement code for DOOMBA
  if (randTurn == 1) {
    //moving right
  
  	//Top motor is going forward
    analogWrite(motorPin1, 255); 
    analogWrite(motorPin2, 0);
  
  	//Bottom motor is going in reverse
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 255);
  } else if (randTurn == 2) {
    //left
  
  	//Top motor is going in reverse
    analogWrite(motorPin1, 0); 
    analogWrite(motorPin2, 255);
  
  	//Bottom motor is going forward
    analogWrite(motorPin3, 255);
    analogWrite(motorPin4, 0);
    
  } else if (randTurn == 3) {
    //Moving straight
  
  	//Top motor is going forward
    analogWrite(motorPin1, 255); 
    analogWrite(motorPin2, 0);
  
  	//Bottom motor is going forward
    analogWrite(motorPin3, 255);
    analogWrite(motorPin4, 0);
  }
} else if (cm < 20) { //If DOOMBA detects something within 20 cm
    //moving right
  
  	//Top motor is going forward
    analogWrite(motorPin1, 255); 
    analogWrite(motorPin2, 0);
  
  	//Bottom motor is going in reverse
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 255);
  }
}