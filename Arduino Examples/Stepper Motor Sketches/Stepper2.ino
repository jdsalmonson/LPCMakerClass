/*
 Stepper: This programme will move a stepper motor in incraments of turns
This is a modification of the original code. 
A math fuction to convert steps in to number of turns
Write the number of turn in the Serial Monitor 
as a Real number with a decimal (ie, 1. , 1.0, 1.00, 1.000, ...)
negative number will make the motor sping the other direction 
*/

#include <Stepper.h>

int in1Pin = 12;
int in2Pin = 11;
int in3Pin = 10;
int in4Pin = 9;

Stepper motor(48, in1Pin, in2Pin, in3Pin, in4Pin);  

void setup()
{
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  // this line is for Leonardo's, it delays the serial interface
  // until the terminal window is opened
  while (!Serial);
  
  Serial.begin(9600);
  motor.setSpeed(200);
}

void loop()   
{
  if (Serial.available())
  {
     float rts = Serial.parseFloat();    // rts = rations you desire to have the motor to turn
     float grstp = 2048.0;              //grstp = (geared steps) number of stepps for one rotation after geared reduction
     int steps;
    
    steps = stepFunction(rts, grstp); 
    motor.step(steps);
  Serial.print(steps);
  }
}
 
 float stepFunction(float rts, float grstp){    // This is the beginning of the function
    int result;
    result = rts * grstp;                     //the actual math
    return result;                           // sends out calculation
 }
      
  


