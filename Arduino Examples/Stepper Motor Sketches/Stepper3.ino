/*
 Stepper: Third iteraton of the program: This programme will move a stepper motor
 with angular commands (ie, 45.0, 60.0,90.0, ...) 
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
     float ang = Serial.parseFloat();           //ang = angle written in the serial monitor
     float grstp = 2048.0;                     // grstp = (geared steps) number of stepps for one rotation after geared reduction
     int steps;
    
    steps = stepFunction(ang, grstp);           // calls the function
    motor.step(steps);  
    Serial.print(ang);                        //prints angle on the serial monitor
    Serial.print("  ");                      // This will ad a place between the two numbers "tab"
    Serial.print(steps);                     //prints on the serial monitor
  
  }
}
 float stepFunction(float ang, float grstp){      //The fuction 
    int result;
    result = (grstp/360.00)*ang 
    return result;                      //sent the output the calculated fuction 
    }
      

