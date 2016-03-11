/*
 Stepper: #4c iteraton of the program: This program will move a stepper motor with linear displacement
 that is difined by the Linear Actuator on an optical bench. The Linear Actuator has 16 threads per 10mm
 That converts to: 16 turns to travel 10mm. The maximum travel distance of the actuator is 27.50mm  
 Write in milimeters in the serial monitor (e.g. type from in the quotes "3.0" or "27.5" or "0.15")
*/

#include <Stepper.h>
  //pinout defined here
int in1Pin = 12;
int in2Pin = 11;
int in3Pin = 10;
int in4Pin = 9;

  //stepper module vars set-up here...
Stepper motor(48, in1Pin, in2Pin, in3Pin, in4Pin);  //actually 24stp/rev into gearing...
          // steps/rev, pin # defines follow // here created new class "motor"???
//END OF VARS

void setup()  {
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  // this line is for Leonardo's, it delays the serial interface
  // until the terminal window is opened
  while (!Serial);
  
  Serial.begin(9600);
  motor.setSpeed(350);  //# given = RPM
}

void loop() {
  if (Serial.available())  {                 //wait for input, until given
     float lengths = Serial.parseFloat();   //mm input on serial -> var "lengths"
     if (lengths != 0.0)  {
       Serial.print(lengths);
       Serial.print(", ");                  // to spit back input value first in CSV-line format
       float tc = 1.0;                     //defines Thread Count(thead per 10.0 mm) to feed to StepFuncMath
       int steps;                         //creates var "steps"
    
       steps = stepFunction(lengths, tc);   //actually passes vars to StepFuncMath
       motor.step(steps);                 //DoStep (#);
       Serial.println(steps);            //prints # after, for some reason end-of-command spits out addt'l "0"
     }                                  //added extra test-for-non-zero before execute & return operations
     else {
      delay(2000);
        digitalWrite(in1Pin, LOW);
        digitalWrite(in2Pin, LOW);
        digitalWrite(in3Pin, LOW);
        digitalWrite(in4Pin, LOW);
     }
  }
}

 float stepFunction(float lengths, float tc) {     //StepFuncMath
    int result;
    result = lengths * 5760.0 * tc;  //product of lengths
    return result;                               //^the steps-to-length coefficient
    }                                           //returns a int from 2 floats input 
                                               //(do float math, on result cast type to int, return it)      .

