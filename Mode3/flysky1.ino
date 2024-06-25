/*
  Arduino FS-I6X Demo
  fsi6x-arduino-uno.ino
  Read output ports from FS-IA6B receiver module
  Display values on Serial Monitor
  
  Channel functions by Ricardo Paiva - https://gist.github.com/werneckpaiva/
  
  DroneBot Workshop 2021
  https://dronebotworkshop.com
*/

// Define Input Connections
#define CH1 13
#define CH2 12
#define CH3 11
#define CH4 10
//#define CH5 9
//#define CH6 8

// Integers to represent values from sticks and pots
int ch1Value;
int ch2Value;
int ch3Value;
int ch4Value; 
//int ch5Value;
//
//// Boolean to represent switch value
//bool ch6Value;

// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

//// Read the switch channel and return a boolean value
//bool readSwitch(byte channelInput, bool defaultValue){
//  int intDefaultValue = (defaultValue)? 100: 0;
//  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
//  return (ch > 50);
//}

//void setup(){
//  // Set up serial monitor
//  Serial.begin(115200);
//  
//  // Set all pins as inputs
//  pinMode(CH1, INPUT);
//  pinMode(CH2, INPUT);
//  pinMode(CH3, INPUT);
//  pinMode(CH4, INPUT);
//  pinMode(CH5, INPUT);
//  pinMode(CH6, INPUT);
//}
//
//
//void loop() {
  
//  // Get values for each channel
//  ch1Value = readChannel(CH1, -100, 100, 0);
//  ch2Value = readChannel(CH2, -100, 100, 0);
//  ch3Value = readChannel(CH3, -100, 100, -100);
//  ch4Value = readChannel(CH4, -100, 100, 0);
//  ch5Value = readChannel(CH5, -100, 100, 0);
//  ch6Value = readSwitch(CH6, false);
//  
//  // Print to Serial Monitor
//  Serial.print("Ch1: ");
//  Serial.print(ch1Value);
//  Serial.print(" | Ch2: ");
//  Serial.print(ch2Value);
//  Serial.print(" | Ch3: ");
//  Serial.print(ch3Value);
//  Serial.print(" | Ch4: ");
//  Serial.print(ch4Value);
//  Serial.print(" | Ch5: ");
//  Serial.print(ch5Value);
//  Serial.print(" | Ch6: ");
//  Serial.println(ch6Value);
//  
//  delay(500);
//}
//small car 
//******** Important Note **********
// must disconnect Tx & Rx before uploading any code
// Tx & Rx are pins o and 1 in arduino


// -------------- H-bridge connection pins -------- 

int speed = 170;// PWM from 0 to 255 which represent the speed
int turnSpeed = 200;
// Motor A
 
int enA = 9;//pwm pin
int in1 = 8;
int in2 = 7;
 
// Motor B
 
int enB = 3;//pwm pin
int in3 = 5;
int in4 = 4;

// Remote data
char remote = 0; // variable for remote button



void setup() {

  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

    // Set up serial monitor
  Serial.begin(115200);
  
  // Set all pins as inputs
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
//  pinMode(CH5, INPUT);
//  pinMode(CH6, INPUT);

}

void loop() {


if (Serial.available()>0){
  remote = Serial.read();
  Serial.println(remote);
}

//if(remote=='F'){
//  forward();
//}
//else if(remote=='R'){
//  right();
//}
//else if(remote=='L'){
//  left();
//}
//else if(remote=='B'){
//  backward();
//}
//else if(remote=='S'){
//  off();
//}

  // Get values for each channel
  ch1Value = readChannel(CH1, -100, 100, 0);
  ch2Value = readChannel(CH2, -100, 100, 0);
  ch3Value = readChannel(CH3, -100, 100, -100);
  ch4Value = readChannel(CH4, -100, 100, 0);
//  ch5Value = readChannel(CH5, -100, 100, 0);
//  ch6Value = readSwitch(CH6, false);
  
  // Print to Serial Monitor
  Serial.print("Ch1: ");
  Serial.print(ch1Value);
  Serial.print(" | Ch2: ");
  Serial.print(ch2Value);
  Serial.print(" | Ch3: ");
  Serial.print(ch3Value);
  Serial.print(" | Ch4: ");
  Serial.println(ch4Value);
//  Serial.print(" | Ch5: ");
//  Serial.print(ch5Value);
//  Serial.print(" | Ch6: ");
//  Serial.println(ch6Value);
  
  delay(500);

if(ch3Value>50){
  forward();
}


else if(ch3Value<-50){
  backward();
}
//else if(remote=='L'){
//  left();
//}
//else if(remote=='B'){
//  backward();
//}
else {
  off();
}
//delay (200);
}
//-------------------H-bridge-------------------------------
// car movement functions: enabling required motors with appropriate speeds
void backward(){
  analogWrite(enB, speed);
  analogWrite(enA, speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW); 
  
}
void forward(){

  analogWrite(enA, speed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enB, speed);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void left(){
  
  analogWrite(enA, turnSpeed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW); 
  analogWrite(enB, turnSpeed); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void right(){
  
  analogWrite(enA, turnSpeed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enB, turnSpeed);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void off(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
