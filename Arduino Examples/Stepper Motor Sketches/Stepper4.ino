/*
 Stepper: #4 iteraton of the program: This program will move a stepper motor 
 with input of number of rotation in the serial monitor. The serial monitor 
 will then print the number of rotaions and the number of steps required to trun the motor 
 This program also gets rid of that DAMN ZERO that kept popping up at the end!  
*/

#include <Stepper.h>
  //pinout defined here
int in1Pin = 12;
int in2Pin = 11;
int in3Pin = 10;
int in4Pin = 9;
  //stepper module vars set-up here...
Stepper motor(48, in1Pin, in2Pin, in3Pin, in4Pin);  //actually 48stp/rev into gearing...
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
  motor.setSpeed(200);  //# given = RPM
}

void loop() {
  if (Serial.available())  {                 //wait for input, until given
     float rts = Serial.parseFloat();       //mm input on serial -> var "Rotations"
     if (rts != 0.0)  {
       Serial.print(rts);
     Serial.print(" ");             // to spit back input value first in CSV-line format
       float grst = 2048.0;        //geared steps
       int steps;                 //creates var "steps"
    
       steps = stepFunction(rts, grst);    //actually passes vars to StepFuncMath
       motor.step(steps);                  //DoStep (#);
       Serial.println(steps);       //prints # after, for some reason end-of-command spits out addt'l "0"
     }                             //added extra test-for-non-zero before execute & return operations
     else {
      delay(2000);
        digitalWrite(in1Pin, LOW);
        digitalWrite(in2Pin, LOW);
        digitalWrite(in3Pin, LOW);
        digitalWrite(in4Pin, LOW);
     }
  }
}

 float stepFunction(float rts, float grst) {    //StepFuncMath
    int result;
    result = (rts * grst);  //the number of turns
    return result;      //^the steps-to-length coefficient
    } //returns a int from 2 floats input (do float math, on result cast type to int, return it)      .

