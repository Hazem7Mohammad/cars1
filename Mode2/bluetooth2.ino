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

}

void loop() {


if (Serial.available()>0){
  remote = Serial.read();
  Serial.println(remote);
}

if(remote=='F'){
  forward();
}
else if(remote=='R'){
  right();
}
else if(remote=='L'){
  left();
}
else if(remote=='B'){
  backward();
}
else if(remote=='S'){
  off();
}
//delay (200);
}
//-------------------H-bridge-------------------------------
// car movement functions: enabling required motors with appropriate speeds
void backward(){
  analogWrite(enA, speed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enB, speed);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
}
void forward(){


  analogWrite(enB, speed);
  analogWrite(enA, speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW); 
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
