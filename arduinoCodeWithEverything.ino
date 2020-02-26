// Stepper libraries
#include <Stepper.h>

// Spectrometer Library
#include "SparkFun_AS7265X.h" //Click here to get the library: http://librarymanager/All#SparkFun_AS7265X
AS7265X sensor;
#include <Wire.h>

// Large motor 
#define motorInterfaceType 1
#define dirPin 2  
#define stepPin 5
const int LargeMotorStepsPerRev = 200;
Stepper stepper2 = Stepper(LargeMotorStepsPerRev, stepPin, dirPin);

// Small motor 
#define pwmA 3
#define pwmB 11
#define brakeA 9
#define brakeB 8
#define dirA 12
#define dirB 13
const int SmallMotorStepsPerRev = 200;
Stepper stepper1 = Stepper(SmallMotorStepsPerRev, dirA, dirB);

// Electromagnet pin
#define electromagnet 10

//LED pins
#define whiteLED 7

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

    if(serialData == '1'){   // activate sorting program, will be activated by PIR sensor 1 in the future 

     while (isWasteDetected()== false){
       SmallMotorFullForward();
       if(isWasteDetected()== true){     //from PIR sensor 2 in the sensing box
      // Serial.println("2");  //send code 2 to pi, pi then sends instruction number back to the serial port
       break;
      }
    
    }
    }
    
    if(serialData == '3'){
      LargeMotorInitialToBin1SenseBox();
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
      openDoor();
      closeDoor();
      LargeMotorBin1SenseBoxToInitial();    
    }

    if(serialData == '8'){
      LargeMotorBin1SenseBoxToBin2();
      openDoor();
      closeDoor();
      LargeMotorBin2ToInitial();
    }

    if(serialData == '9'){
      LargeMotorBin1SenseBoxToBin3();
      openDoor();
      closeDoor();
      LargeMotorBin3ToInitial();
    }
    
  }
  }


void setupComponents() {
  pinMode(electromagnet,OUTPUT); //setup of electromagnet
 // SMALL MOTOR
 // Drection and step pins
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  digitalWrite(pwmA, HIGH);
  digitalWrite(pwmB, HIGH);
  // Motor speed, maximum 90 RPM
  stepper1.setSpeed(60);

  // LARGE MOTOR
  // Set the maximum speed 
  stepper2.setSpeed(700);

  // Setup of input window
  Serial.begin(9600);
   pinMode(whiteLED, OUTPUT);

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

void SmallMotorFullForward(){
  stepper1.step(200);    

}

void SmallMotorFullReverse(){
  stepper1.step(-1000);    // needs calibrating
}

void LargeMotorInitialToBin1SenseBox() {
  stepper2.step(16000);     // needs calibrating
}

void LargeMotorBin1SenseBoxToInitial(){
  stepper2.step(16000);     // needs calibrating
}

void LargeMotorBin1SenseBoxToBin2() {
  stepper2.step(-16000);     // needs calibrating 
}

void LargeMotorBin2ToInitial(){
  stepper2.step(-16000);     // needs calibrating
}

void LargeMotorBin1SenseBoxToBin3() {
  stepper2.step(-16000);     // needs calibrating
}

void LargeMotorBin3ToInitial(){
  stepper2.step(-16000);     // needs calibrating
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


boolean isWasteDetected(){
  int sensorValue = digitalRead(PIR_MOTION_SENSOR);
  if(sensorValue == HIGH)//if the sensor value is HIGH?
  {
    return true;   // yes,return ture
  }
  else
  {
    return false;   // no,return false
  }
}
