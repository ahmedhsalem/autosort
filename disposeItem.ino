int electromagnet = 2; //setup of electromagnet pin 
// Include the Stepper library:
#include <Stepper.h>

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
  if(Serial.available())
  {
    serialData = Serial.read();

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
  myStepper.setSpeed(100);

  //setup of input window
  Serial.begin(9600);
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
  myStepper.step(200);
}

void motor2PlasticBackwards(){
  myStepper.step(-200);
}
void motor2MetalsForwards() {
  myStepper.step(400);
}

void motor2MetalsBackwards(){
  myStepper.step(-400);
  
}void motor2WasteForwards() {
  myStepper.step(100);
}

void motor2WasteBackwards(){
  myStepper.step(-100);
}
