// C++ code4
#include <Servo.h>  // Include the Servo library

Servo fan;

//Digital pin for the continous servo
const byte fanPin = 6;

//Variable for random direction decider
long randMotion;
long randTurn;

// Variables for millis timing
unsigned long previousTime = 0;

//Event times for everything
unsigned long eventTime = 1000;  //event happens every one second
unsigned long eventDirection = 60000; //event happens every minute

//Directions
const byte forward = 1;
const byte reverse = 2;
const byte right = 1;
const byte left = 2;
const byte straight = 3;

//Motor pins for bottom motor
const byte motorPin1 = 3; //Power pin for motor, connected to pin 3 on input 1
const byte motorPin2 = 0; //Ground pin for motor, connect to pin 5 on input 2

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
}

void loop()
{
  unsigned long currentTime = millis(); //always keep currentTime = Millis at top
  
  //Measure the distance using the ultrasonic sensor
  cm = 0.01723 * readUltrasonicDistance(trigPin, echoPin);
  inches = cm / 2.54;  // Convert cm to inches
 
  
  //Event time for the direction of the robot
  if (currentTime - previousTime >= eventDirection) {
    //Randomly choosing motion for DOOMBA
    randMotion = random(1, 2); //1 = forward, 2 = reverse
    
    //Randomly choosing turning for DOOMBA
    randTurn = random(1, 3); //1 = right, 2 = left, 3 = straight
    
    previousTime = currentTime;
      }
      
  //Movement code for DOOMBA
  if (randMotion == 1 && randTurn == 3) {
    //moving forward AND straight
  
  	//Top motor
    analogWrite(motorPin1, 255);
    analogWrite(motorPin2, 0);
  
  	//Bottom motor
    analogWrite(motorPin3, 255);
    analogWrite(motorPin4, 0);
    
  } else if 
  
  delay(10); // Delay a little bit to improve simulation performance
}