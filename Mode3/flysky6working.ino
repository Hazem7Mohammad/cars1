#define CH1 13
#define CH2 12
#define CH3 11
#define CH4 10

int ch1Value;
int ch2Value;
int ch3Value;
int ch4Value;

int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue) {
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

int mapspeed;
int mapspeed2;

int enA = 9;
int in1 = 8;
int in2 = 7;

int enB = 3;
int in3 = 5;
int in4 = 4;

void setup() {
  Serial.begin(115200);  // Initialize serial communication at 115200 baud
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
}

void loop() {
  // Read channel values
  ch1Value = readChannel(CH1, -100, 100, 0);
  ch2Value = readChannel(CH2, -100, 100, 0);
  ch3Value = readChannel(CH3, -100, 100, -100);
  ch4Value = readChannel(CH4, -100, 100, 0);

  bool moving = false;  // Flag to track if any movement command is active

  // Control forward and backward movement
  if (ch2Value > 5) {
    mapspeed = map(ch2Value, 0, 100, 0, 255);
    forward(mapspeed);
    Serial.println(mapspeed);
    moving = true;
  } else if (ch2Value < -5) {
    mapspeed = map(ch2Value, 0, -100, 0, 255);
    backward(mapspeed);
    Serial.println(mapspeed);
    moving = true;
  }

  // Control left and right movement
  if (ch4Value > 5) {
    mapspeed2 = map(ch4Value, 0, 100, 0, 255);
    right(mapspeed2);
    Serial.println(mapspeed2);
    moving = true;
  } else if (ch4Value < -5) {
    mapspeed2 = map(ch4Value, 0, -100, 0, 255);
    left(mapspeed2);
    Serial.println(mapspeed2);
    moving = true;
  }

  // If no movement commands are active, turn off the motors
  if (!moving) {
    off();
  }

  // Print channel values to the serial monitor
  Serial.print("Ch1: ");
  Serial.print(ch1Value);
  Serial.print(" | Ch2: ");
  Serial.print(ch2Value);
  Serial.print(" | Ch3: ");
  Serial.print(ch3Value);
  Serial.print(" | Ch4: ");
  Serial.println(ch4Value);
}

void backward(int speed) {
  analogWrite(enA, speed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enB, speed);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void forward(int speed) {
  analogWrite(enA, speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enB, speed);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void left(int speed) {
  analogWrite(enA, speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enB, speed);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void right(int speed) {
  analogWrite(enA, speed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enB, speed);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void off() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
