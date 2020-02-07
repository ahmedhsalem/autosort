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

    if(serialData == 'S'){
      spectrometerReadings();
    }
     if(serialData == 'P')
        {
          Serial.println("Plastic");
          motor2PlasticForwards();
          openDoor();
          delay(1000);
          closeDoor();
          motor2PlasticBackwards();
        }
        if(serialData == 'M')
                {
                  Serial.println("Metals");
                  motor2MetalsForwards();
                  openDoor();
                  delay(1000);
                  closeDoor();
                  motor2MetalsBackwards();
                }
                if(serialData == 'W'){
                   motor2WasteForwards();
                   openDoor();
                  delay(1000);
                  closeDoor();
                  motor2WasteBackwards();
                }
                if(serialData == '1'){
                  whiteLightOn();
                }
                if(serialData == '0'){
                  whiteLightOff();
                }
                if(serialData == '2'){
                  uvLightOn();
                }
                if(serialData == '3'){
                  uvLightOff();
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
  myStepper.setSpeed(300);

  //setup of input window
  Serial.begin(9600);
   pinMode(whiteLED, OUTPUT);
  pinMode(uvLED, OUTPUT); 
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

void motor2PlasticForwards() {
  myStepper.step(2000);
}

void motor2PlasticBackwards(){
  myStepper.step(-2000);
}
void motor2MetalsForwards() {
  myStepper.step(3000);
}

void motor2MetalsBackwards(){
  myStepper.step(-3000);
  
}void motor2WasteForwards() {
  myStepper.step(1000);
}

void motor2WasteBackwards(){
  myStepper.step(-1000);
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
