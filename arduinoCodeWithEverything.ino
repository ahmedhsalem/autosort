// Stepper libraries
#include <Stepper.h>
#include <AccelStepper.h>

// Spectrometer Library
#include "SparkFun_AS7265X.h" //Click here to get the library: http://librarymanager/All#SparkFun_AS7265X
AS7265X sensor;
#include <Wire.h>

// Large motor pins
#define dirPin 2   //same pin as electromagnet
#define stepPin 3
#define motorInterfaceType 1

// Small motor pins
#define pwmA 3
#define pwmB 11
#define brakeA 9
#define brakeB 8
#define dirA 12
#define dirB 13

// Electromagnet pin
#define electromagnet 2

//LED pins
#define whiteLED 7
#define uvLED 10

// Small motor steps per revolution
const int stepsPerRevolution = 50;

// Initialise the AccelStepper.h library:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

// Initialise the stepper.h library:
Stepper myStepper = Stepper(stepsPerRevolution, dirA, dirB);

// PIR sensor pin
#define PIR_MOTION_SENSOR 4


void setup() {
  setupComponents();
}

char serialData;

void loop() {
  while(true){
    while(Serial.available() == false){} //do nothing while we wait for python input

    serialData = Serial.read(); //reads input

    /*if(sensor.begin() == false) {
      Serial.println("Sensor does not appear to be connected. Please check wiring. Freezing...");
      while(1);
    }*/

    if(serialData == '1'){

      while (isWasteDetected()== false){
        if(isWasteDetected()== true){
       Serial.println("2");
       break;
      }
       //send code 2 to pi
    }
    }

    if(serialData == '3'){
      motor1FromInitialToSensingStation();
    }

    if(serialData == '4'){
      whiteLightOn();
    }

    if(serialData == '5'){
      whiteLightOff();
    }

    if(serialData == '6'){
      spectrometerReadings();
    }

    if(serialData == '7'){
      electromagnetOff();
      electromagnetOn();
      motor1FromSensingStationToInitial();
    }

    if(serialData == '8'){
      motor1FromSensingStationToBin2();
      electromagnetOff();
      electromagnetOn();
      motor1FromBin2ToInitial();
    }

    if(serialData == '9'){
      motor1FromSensingStationToBin3();
      electromagnetOff();
      electromagnetOn();
      motor1FromBin3ToInitial();
    }
    
  }
}

void setupComponents() {
  pinMode(electromagnet,OUTPUT); //setup of electromagnet

 // Set the PWM and brake pins so that the direction pins can be used to control the motor:
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(brakeA, OUTPUT);
  pinMode(brakeB, OUTPUT);

  digitalWrite(pwmA, HIGH);
  digitalWrite(pwmB, HIGH);
  digitalWrite(brakeA, LOW);
  digitalWrite(brakeB, LOW);

  // Set the motor speed (RPMs) for stepper.h
  myStepper.setSpeed(85);

  // Set the maximum speed and acceleration for accelstepper.h
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(500);

  // Setup of input window
  Serial.begin(9600);
   pinMode(whiteLED, OUTPUT);
  pinMode(uvLED, OUTPUT);

  // Setup of PIR sensor
  pinMode(PIR_MOTION_SENSOR, INPUT);
}


void openDoor(){
  electromagnetOff();
}

void closeDoor(){
  electromagnetOn();
}

void electromagnetOn() {
  digitalWrite(electromagnet, HIGH);

}

void electromagnetOff() {
  digitalWrite(electromagnet, LOW);
}

void motor1FromInitialToSensingStation() {
  stepper.moveTo(4000);     // Set the target position
  stepper.runToPosition();  // Run to target position with set speed and acceleration/deceleration
 }

void motor1FromSensingStationToInitial(){
  stepper.moveTo(-4000);    
  stepper.runToPosition();  
}

void motor1FromSensingStationToBin2() {
  stepper.moveTo(8000);    
  stepper.runToPosition();  
}

void motor1FromBin2ToInitial(){
  stepper.moveTo(-12000);    
  stepper.runToPosition();
}

void motor1FromSensingStationToBin3() {
  stepper.moveTo(16000);    
  stepper.runToPosition();
}

void motor1FromBin3ToInitial(){
  stepper.moveTo(-20000);    
  stepper.runToPosition();
}

void spectrometerReadings(){

      if(sensor.begin() == false)
    {
      Serial.println("Sensor does not appear to be connected. Please check wiring. Freezing...");
      while(1);
    }

    sensor.disableIndicator(); //Turn off the blue status LED

    Serial.println("A,B,C,D,E,F,G,H,R,I,S,J,T,U,V,W K,L");

   for (int i=0; i < 10; i++){
    sensor.takeMeasurementsWithBulb(); //This is a hard wait while all 18 channels are measured

      Serial.print(sensor.getCalibratedA());
      Serial.print(",");
      Serial.print(sensor.getCalibratedB());
      Serial.print(",");
      Serial.print(sensor.getCalibratedC());
      Serial.print(",");
      Serial.print(sensor.getCalibratedD());
      Serial.print(",");
      Serial.print(sensor.getCalibratedE());
      Serial.print(",");
      Serial.print(sensor.getCalibratedF());
      Serial.print(",");
      Serial.print(sensor.getCalibratedG());
      Serial.print(",");
      Serial.print(sensor.getCalibratedH());
      Serial.print(",");
      Serial.print(sensor.getCalibratedR());
      Serial.print(",");
      Serial.print(sensor.getCalibratedI());
      Serial.print(",");
      Serial.print(sensor.getCalibratedS());
      Serial.print(",");
      Serial.print(sensor.getCalibratedJ());
      Serial.print(",");
      Serial.print(sensor.getCalibratedT());
      Serial.print(",");
      Serial.print(sensor.getCalibratedU());
      Serial.print(",");
      Serial.print(sensor.getCalibratedV());
      Serial.print(",");
      Serial.print(sensor.getCalibratedW());
      Serial.print(",");
      Serial.print(sensor.getCalibratedK());
      Serial.print(",");
      Serial.print(sensor.getCalibratedL());
      Serial.print(",");

      Serial.println();
    }
}
void whiteLightOn() {
  digitalWrite(whiteLED, HIGH);
}

void whiteLightOff(){
  digitalWrite(whiteLED, LOW);
}

void uvLightOn() {
  digitalWrite(uvLED, HIGH);
}

void uvLightOff(){
  digitalWrite(uvLED, LOW);
}

boolean isWasteDetected(){
  int sensorValue = digitalRead(PIR_MOTION_SENSOR);
  if(sensorValue == HIGH)//if the sensor value is HIGH?
  {
    return true;//yes,return ture
  }
  else
  {
    return false;//no,return false
  }
}
