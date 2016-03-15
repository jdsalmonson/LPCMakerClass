
// Photoresistor2_to_HbridgeL293D
// H-bridge wiring based on a sketch example at:
// http://garagelab.com/profiles/blogs/tutorial-l293d-h-bridge-dc-motor-controller-with-arduino
// Jay Salmonson
// 2/29/2016
// 3/14/2016

// pin assignments
int LDR[2] = {A1, A0};
int motorPin1[2] = {5, 3};
int motorPin2[2] = {6, 4};

// allocate variables:
int v[2];
int base[2];
int thresh[2] = {0, 0};
int drv[2];
int min[2]    = { 1000,  1000};
int max[2]    = {-1000, -1000};

int switchPin = 2; // switch input

int enablePin = 9; // pin 1 on L293D

int ledPin    = 13; // UNO LED

void setup() {    
  // set the switch as an input:
  pinMode(switchPin, INPUT);

  // set up the pins:
  for (int i = 0; i <= 1; i++) 
    { 
     pinMode(LDR[i], INPUT);
     int base = analogRead(LDR[i]);
     min[i] = base;
     max[i] = base+100;   
     pinMode(motorPin1[i], OUTPUT);
     pinMode(motorPin2[i], OUTPUT);
     analogWrite(motorPin1[i],0);
     analogWrite(motorPin2[i],0);
    }
    
    pinMode(enablePin, OUTPUT);
    // set enablePin high so that motor can turn on:
    digitalWrite(enablePin, HIGH);
    
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
}

void loop() {
  
     // for each photoresistor 'i':
     for (int i = 0; i <= 1; i++) {
       // read the voltage of the photoresistor:
       v[i] = analogRead(LDR[i]);
     
       // find min and max value of the photoresistor:
       if (v[i] > max[i]) max[i] = v[i];
       if (v[i] < min[i]) min[i] = v[i];
     
       // Set the threshold to activate the motor at 35% between min and max
       int mx_mn35 = int(0.35*(max[i] - min[i]));
       thresh[i] = mx_mn35 + min[i]; 
     
       // If we're above threshold, then scale the motor voltage according to how far above threshold we are.
       if (v[i] > thresh[i]) {  
         // minimum speed is 175.
         // maximum speed is 175 + 80 = 255.
         drv[i] = 175 + int( 80.0*( float(v[i] - thresh[i]) / (max[i] - thresh[i]) ));
       } else {
         drv[i] = 0; // remember to turn the motor off if below threshold
       }
     
       // send the voltage to the motor pins on the H-bridge:
       analogWrite(motorPin1[i], drv[i] );
       analogWrite(motorPin2[i], 0 );  
     }

    // If either motor is driving, light the LED:
    if (drv[0] > 0 || drv[1] > 0) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
    
}
