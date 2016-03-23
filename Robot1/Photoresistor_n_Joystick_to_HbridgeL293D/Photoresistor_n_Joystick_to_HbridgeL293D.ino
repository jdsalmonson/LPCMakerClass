
// Photoresistor_n_Joystick_to_HbridgeL293D
//
// Clicking the joystick button switches between light-chasing (photoresistor) and joystick mode.
//
// H-bridge wiring based on a sketch example at:
// http://garagelab.com/profiles/blogs/tutorial-l293d-h-bridge-dc-motor-controller-with-arduino
// Jay Salmonson
// 2/29/2016
// 3/14/2016
// 3/22/2016 - Added joystick functionality

// bit to tell whether we're in joystick or photoresistor (light-seeking) mode:
int joy_or_photo;
boolean iserial = false; // run serial terminal for debugging

// pin assignments
int LDR[2] = {A1, A0};
int motorPin1[2] = {5, 3};
int motorPin2[2] = {6, 4};

// joystick pins:
int xPin = A4;
int yPin = A5;
int buttonPin = 2;

// allocate variables:
int v[2];
int base[2];
int thresh[2] = {0, 0};
int drv[2];
int min[2]    = { 1000,  1000};
int max[2]    = {-1000, -1000};

// joystick variables:
int xPos0, xPosition;
int yPos0, yPosition;
int buttonState, prevButtonState;

int enablePin = 9; // pin 1 on L293D (to enable or disable H-bridge)

int ledPin    = 13; // UNO LED

void setup() {  
  if (iserial) {
    Serial.begin(9600);
  }
  
  joy_or_photo = 1; // initial state: 1 = joystick, 0 = photoresistor
  
  // joystick:
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  //activate pull-up resistor on the push-button pin
  pinMode(buttonPin, INPUT_PULLUP); 
  xPos0 = analogRead(xPin);
  yPos0 = analogRead(yPin);
  buttonState     = 1;
  prevButtonState = 1;

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
  // read the joystick
  xPosition   = analogRead(xPin);
  yPosition   = analogRead(yPin);
  buttonState = digitalRead(buttonPin);

  if (joy_or_photo) { // if joy_or_photo = 1, then do joystick:
    float dx, dy;
    if (xPosition > xPos0) {
      dx = float(xPosition - xPos0) / (1023.0 - xPos0);
    } else {
      dx = float(xPosition - xPos0) / xPos0;
    }
    if (yPosition > yPos0) {
      dy = float(yPosition - yPos0) / (1023.0 - yPos0);
    } else {
      dy = float(yPosition - yPos0) / yPos0;
    }
    
    // dx is the forward/backward vector spanning [-1.0:1.0]
    // dy is the twist left/right vector spanning [-1.0:1.0]
    float drvThresh = 0.05;
    float drvRight = 0.5*(dx + dy);
    float drvLeft  = 0.5*(dx - dy);
    
    // if +/- drvRight is smaller than a threshold, don't power motors.
    if (abs(drvRight) <= drvThresh) {
      analogWrite(motorPin1[0], 0 );
      analogWrite(motorPin2[0], 0 );
    } else if (drvRight > drvThresh) { // if the motor is directed to move forward...
      // ... then write the forward motor voltage in a range between 175 and 255:
      analogWrite(motorPin1[0], 175 + int( 80.*drvRight ));
      analogWrite(motorPin2[0], 0 );
    } else {
      // otherwise write the reverse voltage in a range between 175 and 255:
      analogWrite(motorPin1[0],  0 );
      analogWrite(motorPin2[0], (175 - int( 80.*drvRight )) );
    }

    // do same for left:
    if (abs(drvLeft) <= drvThresh) {
      analogWrite(motorPin1[1], 0 );
      analogWrite(motorPin2[1], 0 );
    } else if (drvLeft > drvThresh) {
      analogWrite(motorPin1[1], 175 + int( 80.*drvLeft ));
      analogWrite(motorPin2[1], 0 );
    } else {
      analogWrite(motorPin1[1],  0 );
      analogWrite(motorPin2[1], (175 - int( 80.*drvLeft )) );
    }
      
    if (iserial) {
      Serial.print("drvRight = ");
      Serial.print(drvRight);
      Serial.print(" drvLeft = ");
      Serial.print(drvLeft);
      Serial.print(" xpos0 = ");
      Serial.print(xPos0);
      Serial.print(" yPos0 = ");
      Serial.print(yPos0);
      Serial.print(" xPosition = ");
      Serial.print(xPosition);
      Serial.print(" yPosition = ");
      Serial.print(yPosition);
      Serial.print(" buttonState = ");
      Serial.println(buttonState);
    }
    
  } else { // if joy_or_photo = 0, then do photoresistor
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
  }
  
  // if the joystick button is pushed, toggle joy_or_photo
  // The button is "pressed" when the buttonState = 0, but the previous button state = 1
  if (buttonState == 0 && prevButtonState == 1) {
    joy_or_photo = !joy_or_photo; // reverse: 0 -> 1 or 1 -> 0
    digitalWrite(ledPin,joy_or_photo);
    
    // reset base for photoresistors:
    for (int i = 0; i <= 1; i++) 
    { 
     pinMode(LDR[i], INPUT);
     int base = analogRead(LDR[i]);
     min[i] = base;
     max[i] = base+100;   
    }    
  }
  prevButtonState = buttonState;
}
