#include <ros.h>
#include <std_msgs/Int16.h>
#include <Servo.h>
#include <geometry_msgs/Pose2D.h>

ros::NodeHandle nh;
float x = 0.0;
float y = 0.0;
float area = 0.0;

int speed = 100;

int enA = 9;
int in1 = 8;
int in2 = 7;

int enB = 3;
int in3 = 5;
int in4 = 4;

void callback(const geometry_msgs::Pose2D& pose_message) {
    x = pose_message.x;
    y = pose_message.y;
    area = pose_message.theta;

    if ((y == 0) && (x == 0)) {
        x = 320;
        y = 230;

        off();
    }

//
    if ((220 < x && x < 420) && (130 < y && y < 330) && (area > 30000)) {
      
        delay(30); //
        
        off();
        
    } else if ((220 < x && x < 420) && (130 < y && y < 330) && (area <= 30000 && area > 3500)) {
        
        delay(30); //
        
        off();
//        
    } else {
        while (x < 220) {
            go_left();
            goto label;  //
        }
        while (x > 420) {
            go_right();
            goto label;  //
        }
    }
    label: ; //
}

ros::Subscriber<geometry_msgs::Pose2D> servo_n("pose", &callback);

void setup() {
    nh.initNode();
    nh.subscribe(servo_n);

    pinMode(13, OUTPUT);

    delay(30); //
    
    Serial.begin(9600);
    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
}

void loop() {
    digitalWrite(13, LOW);
    nh.spinOnce();
    
    delay(300); //
}


void forward() {
    analogWrite(enA, speed);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enB, speed);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}
void go_left() {
    analogWrite(enA, speed);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enB, speed);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}

void go_right() {
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
