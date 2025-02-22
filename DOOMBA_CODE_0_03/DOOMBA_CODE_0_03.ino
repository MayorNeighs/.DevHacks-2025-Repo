// C++ code4
#include <Servo.h>  // Include the Servo library
#include <avr/power.h> //Only necessary for 8Mhz arduino. Comment out for 16Mhz arduino.

Servo lift;
Servo poop;

// Digital pin for the continuous servo
const byte liftPin = 6;
const byte poopPin = 11;

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


void setup() {
  clock_prescale_set (clock_div_2); //Only necessary for 8Mhz arduino. Comment out for 16Mhz arduino.
  
  // Initialize serial communication
  Serial.begin(9600);

  // Setting pins as input or output
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  pinMode(red1, OUTPUT);
  pinMode(red2, OUTPUT);

  // Initialize servo
  lift.attach(liftPin, 500, 2500);
  poop.attach(poopPin, 500, 2500);

  // Seed random function
  randomSeed(analogRead(0));

  // DOOMBA starts in cleaning mode and moves forward
  lift.write(90);
  poop.write(90);

  // Moving straight
  analogWrite(motorPin1, 255); 
  analogWrite(motorPin2, 0);
  analogWrite(motorPin3, 255);
  analogWrite(motorPin4, 0);
}

void loop() {
  unsigned long currentTime = millis(); // Always keep currentTime = millis at top

  // Event time for cleaning or not cleaning
  if (currentTime - previousCleanTime >= eventClean) {
    randClean = random(1, 3); // 1 = cleaning, 2 = not cleaning
    previousCleanTime = currentTime;
  }

  // Cleaning mode logic
  if (randClean == 1) { //Cleaning
    lift.write(90);
    poop.write(180);
    digitalWrite(red1, LOW);
    digitalWrite(red2, LOW);
  } else if (randClean == 2) { //Not cleaning
    lift.write(180);
    poop.write(180);
    digitalWrite(red1, HIGH);
    digitalWrite(red2, HIGH);
  }


  // Event time for turning of DOOMBA
  if (currentTime - previousTurnTime >= eventTurn) {
    randTurn = random(1, 4); // 1 = right, 2 = left, 3 = straight
    previousTurnTime = currentTime;
  }

  // Movement logic
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
}

