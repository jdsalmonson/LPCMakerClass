/*
 Stepper: #5b iteraton of the program: This program will move a stepper motor with commands for 
 Number of Rotation. In the serial monitor input number of rotations to the near second decimal. 
 Output on the serial monitor will be the fractional rotation in to the nearest 2nd decimal and the 
 Step number respectively.
 You MUST give a leading zero before decimals! otherwise the decimal point will be ignored.
 Give counterclockwise values a negative, as clockwise is positive.
*/

#include <Stepper.h>
  //pinout defined here
int in1Pin = 12;
int in2Pin = 11;
int in3Pin = 10;
int in4Pin = 9;
  //stepper module vars set-up here...
Stepper motor(48, in1Pin, in2Pin, in3Pin, in4Pin);  //actually 24stp/rev into gearing...
                                                   //steps/rev, pin # defines follow 
                                                  //here created new class "motor"???
  float tc = 1.0;                               //defines thread count (thread per mm) to feed to StepFuncMath
  int jump = 0;
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
     float lengths = Serial.parseFloat();   //mm input on serial -> var "lengths"
     
     if (lengths != 0.0)  {
       Serial.print(lengths);
       long steps;                           //creates var "steps" [remaining]
       long stepstaken = 0;                 //create/initialize step progress counter
       steps = stepFunction(lengths, tc);  //actually passes vars to StepFuncMath
       Serial.println(", OK go");        //to spit back input value first in CSV-line format
       while (steps != 0) {             //creates var "jump" for number of steps to take before printing position
          int jump = 1;                //and set sign to positive value given here
         
         if (steps >= 1) {                     //Clockwise Stepping
            motor.step(jump);                 //DoStep (#jumppositive);
           stepstaken = stepstaken + jump;   //accumulate step [progress] count
          steps = steps - jump;             //decrease [remaining] step count
          }
          
          if (steps <= -1) {                  //Counter-Clockwise Stepping
             motor.step(-jump);              //DoStep (#jumpnegative);
          stepstaken = stepstaken - jump;   //accumulate step [progress] count
          steps = steps + jump;            //decrease [remaining] step count
          }
          
          lengths = reverseMath(stepstaken);
          Serial.print(lengths);          //current position output
         Serial.print(" ");
         Serial.println(stepstaken);    //prints # after
       }
     }                                 //added extra test-for-non-zero 
                                      //before execute & return operations
     else {                          //for zero-value commands or no command given, result is...
      delay(2000);                  // a 2-sec delay-off for motor drive power.
        digitalWrite(in1Pin, LOW);
        digitalWrite(in2Pin, LOW);      // Why heat up the stationary motor?
        digitalWrite(in3Pin, LOW);
        digitalWrite(in4Pin, LOW);
     }                                 //no moves made? motor power stays off.
  }                                   //no serial input? nothing executes.
}                                    //break out of this, you're either in a function, 
                                    //or you branched to oblivion (you broke it).

float reverseMath(int stepstaken) {
  float result;
  result = (stepstaken)/(tc*48.0);
  return result;
}

 float stepFunction(float lengths, float r) {    //StepFuncMath
    long result;
    result = (lengths * 48.0)*(tc);              //product of 5760lengths, divided by Two_Pi_R
    return result;                                //^the steps-to-length coefficient
    }                                            //returns a int from 2 floats input 
                                                //(do float math, on result cast type to int, return it)      .

