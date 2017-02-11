#include <Servo.h>
#include <uSTimer2.h>

#define LIGHTSENSOR
Servo servo_ArmMotor;
Servo servo_GripMotor;

const int ci_Ultrasonic_Ping = 2;   //input plug
const int ci_Ultrasonic_Data = 3;   //output plug
const int ci_Arm_Motor = 10;
const int ci_Grip_Motor = 11;
const int ci_Light_Sensor=A3;
const int ci_Grip_Motor_Open = 140;         // Experiment to determine appropriate value
const int ci_Grip_Motor_Closed = 90;        //  "
const int ci_Arm_Servo_Retracted = 55;      //  "
const int ci_Arm_Servo_Extended = 120;      //  "
unsigned long ul_Echo_Time;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ci_Ultrasonic_Ping, OUTPUT);
  pinMode(ci_Ultrasonic_Data, INPUT);
  // set up arm motors
  pinMode(ci_Arm_Motor, OUTPUT);
  servo_ArmMotor.attach(ci_Arm_Motor);
  pinMode(ci_Grip_Motor, OUTPUT);
  servo_GripMotor.attach(ci_Grip_Motor);
  servo_ArmMotor.write(ci_Arm_Servo_Extended);
  servo_GripMotor.write(ci_Grip_Motor_Open);
}

void loop() {
  // put your main code here, to run repeatedly:
  Ping();
}
void Ping()
{
  //Ping Ultrasonic
  //Send the Ultrasonic Range Finder a 10 microsecond pulse per tech spec
  digitalWrite(ci_Ultrasonic_Ping, HIGH);
  delayMicroseconds(10);  //The 10 microsecond pause where the pulse in "high"
  digitalWrite(ci_Ultrasonic_Ping, LOW);
  //use command pulseIn to listen to Ultrasonic_Data pin to record the
  //time that it takes from when the Pin goes HIGH until it goes LOW
  ul_Echo_Time = pulseIn(ci_Ultrasonic_Data, HIGH, 10000);

  // Print Sensor Readings
  #ifdef ULTRASONIC
  Serial.print("Time (microseconds): ");
  Serial.print(ul_Echo_Time, DEC);
  Serial.print(", Inches: ");
  Serial.print(ul_Echo_Time / 148); //divide time by 148 to get distance in inches
  Serial.print(", cm: ");
  Serial.println(ul_Echo_Time / 58); //divide time by 58 to get distance in cm
  #endif
  #ifdef LIGHTSENSOR
  Serial.print("Light sensor val: ");
  Serial.print(checkLightSensor());
  #endif
}
int checkLightSensor()
{
  return analogRead(ci_Light_Sensor);
}
