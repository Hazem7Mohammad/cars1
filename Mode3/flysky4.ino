#define CH1 13
#define CH2 12
#define CH3 11
#define CH4 10

int ch1Value;
int ch2Value;
int ch3Value;
int ch4Value;

int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

int speed = 170;
int turnSpeed = 200;

int enA = 9;
int in1 = 8;
int in2 = 7;

int enB = 3;
int in3 = 5;
int in4 = 4;

void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Serial.begin(115200);
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
}

void loop() {
  ch1Value = readChannel(CH1, -100, 100, 0);
  if ch1Value > 0 {
    map(speed, 0, 100, 0, 255)
  } 
  else if ch1Value < 0 {
    map(speed, 0, -100, 0, 255)
  }
  ch2Value = readChannel(CH2, -100, 100, 0);
  ch3Value = readChannel(CH3, -100, 100, -100);
  ch4Value = readChannel(CH4, -100, 100, 0);

  Serial.print("Ch1: ");
  Serial.print(ch1Value);
  Serial.print(" | Ch2: ");
  Serial.print(ch2Value);
  Serial.print(" | Ch3: ");
  Serial.print(ch3Value);
  Serial.print(" | Ch4: ");
  Serial.println(ch4Value);

  forward();
  
  // if(ch1Value > 50){
  //   forward();
  // }
  // else if(ch1Value < -50){
  //   backward();
  // }
  // else if(ch2Value > 50){
  //   right();
  // }
  // else if(ch2Value < -50){
  //   left();
  // }
  // else {
  //   off();
  // }
}

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
