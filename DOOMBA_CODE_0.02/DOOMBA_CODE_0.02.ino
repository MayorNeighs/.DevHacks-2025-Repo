// C++ code4
#include <Servo.h>  // Include the Servo library

Servo fan;

// Digital pin for the continuous servo
const byte fanPin = 6;

// Variables for random choices
long randClean; // Randomize cleaning or not cleaning
long randTurn; // Randomize the turning of the DOOMBA

// Variables for millis timing
unsigned long previousCleanTime = 0;
unsigned long previousTurnTime = 0;

// Event times for everything
unsigned long eventClean = 1000;  // Event happens every one second
unsigned long eventTurn = 2000; // Event happens every two seconds

// Directions
/*
right = 1;
left = 2;
straight = 3;
*/

// Motor pins for bottom motor
const byte motorPin1 = 3; // Power pin for motor, connected to pin 3 on input 1
const byte motorPin2 = 5; // Ground pin for motor, connect to pin 5 on input 2

// Motor pins for top motor
const byte motorPin3 = 10; // Ground pin for motor, connected to pin 9 on input 3
const byte motorPin4 = 9; // Power pin for motor, connected to pin 10 on input 4

// Digital pins for red LEDs
const byte red1 = 7; // Red LED on the right
const byte red2 = 8; // Red LED on the left

// Digital pins for ultrasonic sensor
const byte trigPin = 12;
const byte echoPin = 11;

// Variables for the ultrasonic sensor for distance calculations
int cm = 0;

// Sending a signal for the ultrasonic sensor
long readUltrasonicDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);  // Return the sound wave travel time in microseconds
}

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Setting pins as input or output
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(red1, OUTPUT);
  pinMode(red2, OUTPUT);

  // Initialize servo
  fan.attach(fanPin, 500, 2500);

  // Seed random function
  randomSeed(analogRead(0));

  // DOOMBA starts in cleaning mode and moves forward
  fan.write(180);

  // Moving straight
  analogWrite(motorPin1, 255); 
  analogWrite(motorPin2, 0);
  analogWrite(motorPin3, 255);
  analogWrite(motorPin4, 0);
}

void loop() {
  clock_prescale_set (clock_div_2); //Only necessary for 8Mhz arduino. Comment out for 16Mhz arduino.

  unsigned long currentTime = millis(); // Always keep currentTime = millis at top

  // Measure the distance using the ultrasonic sensor
  cm = 0.01723 * readUltrasonicDistance(trigPin, echoPin);

  // Event time for cleaning or not cleaning
  if (currentTime - previousCleanTime >= eventClean) {
    randClean = random(1, 3); // 1 = cleaning, 2 = not cleaning
    previousCleanTime = currentTime;
  }

  // Cleaning mode logic
  if (randClean == 1) { //Cleaning
    fan.write(180);
    digitalWrite(red1, LOW);
    digitalWrite(red2, LOW);
  } else if (randClean == 2) { //Not cleaning
    fan.write(0);
    digitalWrite(red1, HIGH);
    digitalWrite(red2, HIGH);
  }


  // Event time for turning of DOOMBA
  if (currentTime - previousTurnTime >= eventTurn) {
    randTurn = random(1, 4); // 1 = right, 2 = left, 3 = straight
    previousTurnTime = currentTime;
  }

  // Movement logic
  if (cm >= 20) { // If DOOMBA doesn't detect something within 20 cm
    if (randTurn == 1) {
      // Moving right
      analogWrite(motorPin1, 255);
      analogWrite(motorPin2, 0);
      analogWrite(motorPin3, 0);
      analogWrite(motorPin4, 255);
    } else if (randTurn == 2) {
      // Moving left
      analogWrite(motorPin1, 0);
      analogWrite(motorPin2, 255);
      analogWrite(motorPin3, 255);
      analogWrite(motorPin4, 0);
    } else {
      // Moving straight
      analogWrite(motorPin1, 255);
      analogWrite(motorPin2, 0);
      analogWrite(motorPin3, 255);
      analogWrite(motorPin4, 0);
    }
  } else if (cm < 20) { // If DOOMBA detects something within 20 cm
    // Move right to avoid obstacle
    analogWrite(motorPin1, 255);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 255);
  }
}
