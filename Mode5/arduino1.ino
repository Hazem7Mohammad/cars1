//original code
#include <ros.h>
#include <std_msgs/Int16.h>
#include <Servo.h>
#include <geometry_msgs/Pose2D.h>

ros::NodeHandle
nh;
Servo x_servo; // create servo object to control a yaw servo
float x = 0.0; // variable to store the servo position
Servo y_servo; // create servo object to control a pitch servo
float y = 0.0; // variable to store the servo position
bool flag = 1;
float area =0.0 ;


int speed = 255;// PWM from 0 to 255 which represent the speed
//int turnSpeed = 255;
// Motor A
 
int enA = 9;//pwm pin
int in1 = 8;
int in2 = 7;
 
// Motor B
 
int enB = 3;//pwm pin
int in3 = 5;
int in4 = 4;

//------------------Call Backs-----------------------------
void callback( const geometry_msgs::Pose2D& pose_message){
/* the callback function named callback carry the
msg pose_message and deal with it
*/
// saving the messages in x & y variables
x = pose_message.x;
y = pose_message.y;
area = pose_message.theta;
// when there is no target the message is zeros
// so it changed to keep the camera in the middle
if((y==0)&&(x==0)){
x= 320;
y= 230;

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
// if the target in the middle turn LED On
if ((220<x && x<420)&&(130<y && y<330)&&(area > 40000)){
digitalWrite(13,HIGH);
delay (30);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}else if ((220<x && x<420)&&(130<y && y<330)&&(area <= 40000 && area > 3500)){
digitalWrite(13,HIGH);
delay (30);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
else {
//------Region 1(left upper quarter)-------
while (x<320 && y<230){
go_right();
go_up();
goto label;
}
//------Region 2(right upper quarter)-------
while (x>320 && y<230){
go_left();
go_up();
goto label;
}
//------Region 3(left lower quarter)-------
while (x<320 && y>230){
go_right();
go_down();goto label;
}
//------Region 2(right lower quarter)-------
while (x>320 && y>230){
go_left();
go_down();
goto label;
}
label: ;
}
}
//---------------------------------------------------------
ros::Subscriber<geometry_msgs::Pose2D> servo_n("pose", &callback );
/* create a subscriber node named servo_n that
* receive the msg (type Pose2D) from the topic
x_pose then invoke the callback
*/
//----------------------------------------------------
void setup()
{
nh.initNode(); //initiate the node
nh.subscribe(servo_n);
//set the subscriber named servo_n to subscribe
pinMode(13,OUTPUT);
// LED light on when target in the middle
x_servo.attach(10);//9
// attaches the servo on pin 9 (PWM) to the servo object
y_servo.attach(6);//6
// attaches the servo on pin 6 (PWM) to the servo object
x_servo.write(90); // Set the servo in the middle
y_servo.write(90); // Set the servo in the middle
delay (30);

  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}
void loop()
{
digitalWrite(13,LOW);//LED off
nh.spinOnce();
delay(300);
}
void go_left (){
int x; // define local variable
x = x_servo.read();// read servo position
if (x<135){
//cap the extreme left to 135 deg
x_servo.write(x+2);// rotate with step of 2 deg
delay(10);
  analogWrite(enA, speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW); 
  analogWrite(enB, speed); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
return ;
}void go_right (){
int x;
x = x_servo.read();
if (x>45){
//cap the extreme right to 45 deg
x_servo.write(x-2);
delay(10);
  analogWrite(enA, speed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enB, speed);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
return ;
}
void go_up (){
int y;
y = y_servo.read();
if (y>45){
//cap the extreme up to 45 deg
y_servo.write(y-2);
delay(10);
}
return ;
}
void go_down (){
int y;
y = y_servo.read();
if (y<135){
//cap the extreme down to 135 deg
y_servo.write(y+2);
delay(10);
}
return ;
}
