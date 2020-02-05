#include "SparkFun_AS7265X.h" //Click here to get the library: http://librarymanager/All#SparkFun_AS7265X
AS7265X sensor;
#include <Wire.h>
#define whiteLED 7
#define uvLED 10

void setup() {
  Serial.begin(9600);
  senseMaterial();
  whiteLightOn();
  delay(1000);
  whiteLightOff(); 
}

void whiteLightOn() {
  digitalWrite(whiteLED, HIGH); 
}

void whiteLightOff(){
  digitalWrite(whiteLED, LOW);
}

void senseMaterial(){
      if(sensor.begin() == false)
    {
      Serial.println("Sensor does not appear to be connected. Please check wiring. Freezing...");
      while(1);
    }
  
    sensor.disableIndicator(); //Turn off the blue status LED
    
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
void loop(){
  
}
