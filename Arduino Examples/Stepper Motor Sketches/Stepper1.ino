/*
Adafruit Arduino - Lesson 16. Stepper
This is the origial programme for of the Arduino Stepper motor 
write the number of steps you want the motor to take in the serial moniter
as an integer (ie, 1, 2, 3, ...)
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
  
  Serial.begin(9600);         //baud rate is the rate at which information 
                             //is transferred in a communication channel. 
                            //In the serial port context, "9600 baud" means 
                           //that the serial port is capable of transferring a 
                          //maximum of 9600 bits per second.
 
  motor.setSpeed(10);   //Speed of the motor 
}

void loop()
{
  if (Serial.available())
  {
    int steps = Serial.parseInt();
    motor.step(steps);
  }
}
