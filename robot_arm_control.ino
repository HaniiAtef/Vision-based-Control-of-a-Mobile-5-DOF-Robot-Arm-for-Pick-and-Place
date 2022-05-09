#include <Servo.h>
Servo servo;
Servo servo1;
Servo servo2;
Servo servo3;
int posServo = 0; 
int posServo1=0;
int posServo2=0;
int posServo3=0;
const int dirpin=28;
const int steppin=30;
const int stepsPerRevolution=200; 
int stepsFor10cmUp=0;
int stepsFor10cmDown=0;
int cyclesUp=6;
int cyclesDown=6;
int dataSerial;
int trig=24;
int echo=26;
long duration;
int distance;
int FrontRightMotor1=2;
int FrontRightMotor2=3;
int FrontLeftMotor1=5;
int FrontLeftMotor2=6;
int BackRightMotor1=11;
int BackRightMotor2=12;
int BackLeftMotor1=8;
int BackLeftMotor2=9;
int PwmEnaAFRM=4;
int PwmEnaBFLM=7;
int PwmEnaABRM=13;
int PwmEnaBBLM=10;
int fr;
int r;
int c;
int l;
int fl;
int pinfr=22;
int pinr=24;
int pinc=26;
int pinl=28;
int pinfl=30;
int maxSpeedleft=45;
int maxSpeedright=55;
float kp=45;
float kd=25;
float error=0,P=0,D=0,PD_value=0;
float prev_error=0;
void moveDown(){
 
 digitalWrite(dirpin,LOW);
 for (int cyc=0; cyc <= cyclesDown; cyc++){
 for(int x=0;x<stepsPerRevolution;x++){
 digitalWrite(steppin,HIGH);
 delayMicroseconds(1000);
 digitalWrite(steppin,LOW);
 delayMicroseconds(1000);
 
 }
 delay(1000); 
 }
 }
void moveUp(){
 
 digitalWrite(dirpin,HIGH);
 for (int cyc=0; cyc <= cyclesUp; cyc++){
 for(int x=0;x<stepsPerRevolution;x++){
 digitalWrite(steppin,HIGH);
 delayMicroseconds(1000);
 digitalWrite(steppin,LOW);
 delayMicroseconds(1000);
 
 }
 delay(1000); 
 }
 }
void From0to90Servo(){
 for (posServo = 0; posServo <= 90; posServo += 1) { 
 // in steps of 1 degree
 servo.write(posServo); 
 delay(25); 
 }
 //servo.detach();
}
void From90to0Servo(){
 for (posServo = 90; posServo >= 0; posServo -= 1) { 
 servo.write(posServo); 
 delay(25); 
 }
 }
void From90to180Servo(){
 for (posServo = 90; posServo <= 180; posServo += 1) { 
 // in steps of 1 degree
 servo.write(posServo); 
 delay(25); 
 }
 //servo.detach();
}
void From180to90Servo(){
 for (posServo = 180; posServo >= 90; posServo -= 1) { 
 servo.write(posServo); 
 delay(25); 
 }
 //servo.detach();
 }
void From0to90Servo1(){
 for (posServo1 = 0; posServo1 <= 90; posServo1 += 1) { 
 // in steps of 1 degree

 servo1.write(posServo1); 
 delay(25); 
 }
}
void From90to0Servo1(){
 for (posServo1 = 90; posServo1 >= 0; posServo1 -= 1) { 
 servo1.write(posServo1); 
 delay(25); 
 }
 }
void From90to180Servo1(){
 for (posServo1 = 90; posServo1 <= 180; posServo1 += 1) { 
 // in steps of 1 degree
 servo1.write(posServo1); 
 delay(25); 
 }
}
void From180to90Servo1(){
 for (posServo1 = 180; posServo1 >= 90; posServo1 -= 1) { 
 servo1.write(posServo1); 
 delay(25); 
 }
 }
void From180to0Servo(){
 for (posServo = 180; posServo >= 0; posServo -= 1) { 
 servo.write(posServo); 
 delay(25); 
 }

 //servo.detach();
 }
void From180to0Servo1(){
 for (posServo1 = 180; posServo1 >= 0; posServo1 -= 1) { 
 servo1.write(posServo1); 
 delay(25); 
 }
 }
void stopp(){
 digitalWrite(FrontRightMotor1,LOW);
 //digitalWrite(FrontRightMotor2,LOW);
 digitalWrite(FrontLeftMotor1,LOW);
 //digitalWrite(FrontLeftMotor2,HIGH);
 digitalWrite(BackRightMotor1,LOW);
 //digitalWrite(BackRightMotor2,HIGH);
 //digitalWrite(BackLeftMotor1,HIGH);
 digitalWrite(BackLeftMotor2,LOW);
 
}
void setup() {
 // put your setup code here, to run once:
 
 servo.attach(32);
 servo1.attach(34);
 servo2.attach(38);
 servo3.attach(40);
 pinMode(steppin,OUTPUT);
 pinMode(dirpin,OUTPUT);
 Serial.begin(9600);
 pinMode(trig,OUTPUT);
 pinMode(echo,INPUT);
 pinMode(pinfr,INPUT);
 pinMode(pinr,INPUT);
 pinMode(pinc,INPUT);
 pinMode(pinl,INPUT);
 pinMode(pinfl,INPUT);
 pinMode(FrontRightMotor1,OUTPUT);
 pinMode(BackRightMotor1,OUTPUT);
 pinMode(FrontLeftMotor1,OUTPUT);
 pinMode(BackLeftMotor1,OUTPUT);
 pinMode(FrontRightMotor2,OUTPUT);
 pinMode(BackRightMotor2,OUTPUT);
 pinMode(FrontLeftMotor2,OUTPUT);
 pinMode(BackLeftMotor2,OUTPUT);
 pinMode(PwmEnaAFRM,OUTPUT);
 pinMode(PwmEnaBFLM,OUTPUT);
 pinMode(PwmEnaABRM,OUTPUT);
 pinMode(PwmEnaBBLM,OUTPUT);
}
void forward(){
 digitalWrite(FrontRightMotor1,HIGH);
 //digitalWrite(FrontRightMotor2,HIGH);
 digitalWrite(FrontLeftMotor1,HIGH);
 //digitalWrite(FrontLeftMotor2,HIGH);
 digitalWrite(BackRightMotor1,HIGH);
 //digitalWrite(BackRightMotor2,HIGH);
 //digitalWrite(BackLeftMotor1,HIGH);
 digitalWrite(BackLeftMotor2,HIGH);
 
 
}
void loop() {
 digitalWrite(trig,LOW);
 delayMicroseconds(2);
 digitalWrite(trig,HIGH);
 delayMicroseconds(10);
 digitalWrite(trig,LOW);
 duration=pulseIn(echo,HIGH);
 distance=duration*0.034/2;
 Serial.print("Distance: ");
 Serial.print(distance);
 Serial.println(" cm");
 delay(10);
 fr=digitalRead(pinfr);
 r=digitalRead(pinr);
 c=digitalRead(pinc);
 l=digitalRead(pinl);
 fl=digitalRead(pinfl);
 
 if(distance>5){
 if (fr==0 && r==0 && c == 1 && l==0 && fl==0){
 error=0;}
 else if (fr==0 && r==1 && c == 0 && l==0 && fl==0){
 error=1;}
 else if (fr==1 && r==0 && c == 0 && l==0 && fl==0){
 error=2;}
 
 else if (fr==1 && r==1 && c == 0 && l==0 && fl==0){
 error=2;}
 
 else if (fr==0 && r==1 && c == 1 && l==0 && fl==0){
 error=1;}
 
 else if (fr==0 && r==0 && c == 0 && l==1 && fl==0){
 error=-1;}
 else if (fr==0 && r==0 && c == 0 && l==0 && fl==1){
 error=-2;}
 
 else if (fr==0 && r==0 && c == 1 && l==1 && fl==0){
 error=-1;}
 else if (fr==0 && r==0 && c == 0 && l==0 && fl==0){
 error=0;}
 
 else if (fr==0 && r==0 && c == 0 && l==1 && fl==1){
 error=-2;}
 
 else if (fr==1 && r==1 && c == 0 && l==0 && fl==0){
 error=2;}
 else if (fr==0 && r==0 && c == 0 && l==1 && fl==1){
 error=-2;}
 //forward();
 P=error;
 D=error - prev_error;
 
 PD_value=(kp*P)+(kd*D);
 error=prev_error;
 
 int left_motor_speed = maxSpeedleft + PD_value;
 int right_motor_speed = maxSpeedright - PD_value;
 
 left_motor_speed = constrain(left_motor_speed, 0, 255);
 right_motor_speed = constrain(right_motor_speed, 0, 255);
 
 analogWrite(PwmEnaAFRM, right_motor_speed); 
 analogWrite(PwmEnaABRM, right_motor_speed);
 analogWrite(PwmEnaBFLM, left_motor_speed); 
 analogWrite(PwmEnaBBLM, left_motor_speed);
 forward();
 
 }
 else{
 stopp();
 
 
 }
while(Serial.available()){
 
 dataSerial=Serial.read();
 if(dataSerial == '0'){ /// starting position 
 servo.write(0);
 delay(2000);
 servo1.write(0);
 delay(2000);
 
 
 }
 else if (dataSerial == '1'){// matching correct bar code
 stopp();
 delay(2000);
 From0to90Servo();
 delay(2000);
 From0to90Servo1();
 delay(2000);
 servo3.write(60);
 delay(2000);
 servo.write(30);
 servo2.write(25);
 delay(2000);
 servo2.write(160);
 delay(2000);
 From90to180Servo();
 delay(2000);
 From90to180Servo1();
 delay(2000);
 servo3.write(30);
 delay(2000);
 servo3.write(30);
 servo2.write(25);
 delay(2000);
 servo2.write(160);
 delay(2000);
 From180to0Servo();
 delay(2000);
 From180to0Servo1();
 delay(2000);
 } 
 else if (dataSerial == '2'){// correct match but the upper barcode
 stopp();
 moveUp();
 delay(2000);
 From0to90Servo();
 delay(2000);
 From0to90Servo1();
 delay(2000);
 servo3.write(60);
 delay(2000);
 servo3.write(30);
 servo2.write(25);
 delay(2000);
 servo2.write(160);
 delay(2000);
 From90to180Servo();
 delay(2000);
 From90to180Servo1();
 delay(2000);
 moveDown();
 servo3.write(60);
 delay(2000);
 servo3.write(30);
 servo2.write(25);
 delay(2000);
 servo2.write(160);
 delay(2000);
 From180to0Servo();
 delay(2000);
 From180to0Servo1();
 delay(2000);
 
 } 
 
 }
}
