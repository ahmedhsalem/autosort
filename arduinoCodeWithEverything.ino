int electromagnet = 2; //setup of electromagnet pin 
// Include the Stepper library:
#include <Stepper.h>

//setup of spectrometer Library 
#include "SparkFun_AS7265X.h" //Click here to get the library: http://librarymanager/All#SparkFun_AS7265X
AS7265X sensor;
#include <Wire.h>

//setup of lights 
#define whiteLED 7
#define uvLED 10

// Define number of steps per revolution:
const int stepsPerRevolution = 50;

// Give the motor control pins names:
#define pwmA 3
#define pwmB 11
#define brakeA 9
#define brakeB 8
#define dirA 12
#define dirB 13

// Initialize the stepper library on the motor shield:
Stepper myStepper = Stepper(stepsPerRevolution, dirA, dirB);

//pirSensorSetup
#define PIR_MOTION_SENSOR 4

//variables for keeping track of electromagnet turning on/off. 
bool isElectromagnetOn = false; 

void setup() {
  setupComponents();
}

char serialData;

void loop() {
  while(true){
    while(Serial.available() == false){} //do nothing while we wait for python input 
    
    serialData = Serial.read(); //reads input 

    if(sensor.begin() == false) {
      Serial.println("Sensor does not appear to be connected. Please check wiring. Freezing...");
      while(1);
    }

    if(serialData == '1'){
      while (isWasteDetected()){
       //send code 2 to pi 
        return;
      }
    }
      else {
      motor1Move();
    }
    

    if(serialData == '3'){
      motor2FromInitialToSensingStation();
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
      motor2FromSensingStationToInitial();
    }

    if(serialData == '8'){
      motor2FromSensingStationToBin2();
      electromagnetOff();
      electromagnetOn();
      motor2FromBin2ToInitial();
    }

    if(serialData == '9'){
      motor2FromSensingStationToBin3();
      electromagnetOff();
      electromagnetOn();
      motor2FromBin3ToInitial();
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

  // Set the motor speed (RPMs):
  myStepper.setSpeed(600);

  //setup of input window
  Serial.begin(9600);
   pinMode(whiteLED, OUTPUT);
  pinMode(uvLED, OUTPUT); 

  //setup of PIR sensor
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
  isElectromagnetOn = true; 
}

void electromagnetOff() {
  digitalWrite(electromagnet, LOW);
  isElectromagnetOn = false; 
}

void motor2FromInitialToSensingStation() {
  myStepper.step(5667); //221.4mm actual was 218mm so 3mm off which might be due to error of rod moving 
}

void motor2FromSensingStationToInitial(){
  myStepper.step(-5667);
}
void motor2FromSensingStationToBin2() {
  myStepper.step(8676); //distance was 339mm - actual distance ended up being 335mm 
}

void motor2FromBin2ToInitial(){
  myStepper.step(-14343); 
  
}void motor2FromSensingStationToBin3() {
  myStepper.step(17277); // distance measured was 666mm :) 
}

void motor2FromBin3ToInitial(){
  myStepper.step(-22944);
}

void motor1Move(){
  myStepper.step(100);
}

void spectrometerReadings(){
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
