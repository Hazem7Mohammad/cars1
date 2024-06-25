


int i=0;
// -------------- H-bridge connection pins -------- 
// Motor A
 
int enA = 9;//pwm pin
int in1 = 8;
int in2 = 7;
 
// Motor B
 
int enB = 3;//pwm pin
int in3 = 5;
int in4 = 4;

int speed = 120;// PWM from 0 to 255 

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


delay(10000);//count 10sec before starting


forward();
delay(1000);
off();
right();
delay(1000);
off();
delay(1000);
left();
delay(1000);
off();
delay(1000);
backward();
delay(1000);
off();
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
void right(){
  analogWrite(enA, speed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enB, speed);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void left(){
  

  analogWrite(enA, speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW); 
  analogWrite(enB, speed); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void off(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
