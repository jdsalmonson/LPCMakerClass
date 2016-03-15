// SimplePhotoresistorTest 
// Jay Salmonson
// 3/15/2016

// pin assignment
int LDR = A0;

void setup() {
  pinMode(LDR, INPUT);
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(LDR);
  
  Serial.print("A0: ");
  Serial.println(val);
  
  delay(1000);
}
