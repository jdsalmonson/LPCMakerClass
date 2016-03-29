/*This is the first iteration of Servo SG90 controlled by the Ultrasonic Ranging Module(HC-SR04).
  This Code is crude but works. The Wire Diagram for the HC-SR04 is found at the following site
  http://www.micropik.com/PDF/HCSR04.pdf
  The servo SG90 Data Sheet is found here: http://www.micropik.com/PDF/SG90Servo.pdf

  The Ultrasonic Sensor output is the servo's input control 
  
*/



#include <NewPing.h>

#include <Servo.h>

Servo myservo;  // create servo object to control a servo


int pos = 0;    // variable to store the servo position

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.



void setup() {
Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
myservo.attach(9);  // attaches the servo on pin 9 to the servo object

}

void loop() {
  delay(50);                           // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping();     // Send ping, get ping time in microseconds (uS).
   int uSS= (uS/US_ROUNDTRIP_CM)*10; //using differnt numbers to see what works for moving the servo
 
  Serial.print("Ping: ");          // print to serial to trouble shoot
  Serial.print(uSS); 
  Serial.println("cm");

  if (pos <= uSS) { 
    for(pos = 0; pos < uSS; pos+= 10){ //tells the degree to move
    myservo.write(pos);               // tell servo to go to position in variable 'pos'
    delay(1);                        // waits 15ms for the servo to reach the position
   }
  }
  
  else if (pos >= uSS)  {
   for(pos !=uSS; pos >= uSS; pos -= 10){
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(1);                       // waits 15ms for the servo to reach the position
    }
  }
  else (pos = uSS); {
    myservo.write(pos);           //Tells sever to stay-put of nothing changes
    delay(500);
  }

 Serial.println("ping");
 Serial.print(uS);
}


