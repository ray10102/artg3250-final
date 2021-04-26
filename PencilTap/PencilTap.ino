/*
  SparkFun Inventor’s Kit
  Circuit 5A - Motor Basics

  Learn how to control one motor with the motor driver.

  This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
  This code is completely free for any use.

  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v41
  Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
*/

//PIN VARIABLES
//the motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 13;           //control pin 1 on the motor driver for the right motor
const int AIN2 = 12;            //control pin 2 on the motor driver for the right motor
const int PWMA = 11;            //speed control pin on the motor driver for the right motor

int switchPin = 7;             //switch to turn the robot on and off
int ledPin = 6;
bool analog = false; 

//VARIABLES
int motorSpeed = 0;       //starting speed for the motor
int temp = 0; // temporary read of serial
int bpm;
int totalCycleTime;
void setup() { 
  pinMode(switchPin, INPUT_PULLUP);   //set this as a pullup to sense whether the switch is flipped

  //set the motor control pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);                       //begin serial communication with the computer

  Serial.println("Started");    //Prompt to get input in the serial monitor.
}

void loop() {

  if (Serial.available() > 0) {         //if the user has entered something in the serial monitor
    temp = Serial.parseInt();     //set the motor speed equal to the number in the serial message

    if (temp != 0) {
      bpm = temp;
      motorSpeed = -255 * bpm / 120;
      totalCycleTime = 60000 / bpm; // amount of time in milliseconds for one tap cycle (milliseconds per minute divided by taps per minute)
      Serial.print("Motor speed: ");
      Serial.println(motorSpeed);
      Serial.print("Taps Per Minute: ");
      Serial.println(bpm);
      Serial.print("Time Per Cycle: ");
      Serial.println(totalCycleTime);
    }
  }
  if (digitalRead(7) == LOW) {          //if the switch is on...
    spinMotor(motorSpeed);
    delay(totalCycleTime * 3 / 5);
    spinMotor(-motorSpeed);
    delay(totalCycleTime / 5);
    spinMotor(0);
    delay(totalCycleTime / 5);
  } else {                             //if the switch is off...
    spinMotor(0);                   //turn the motor off
  }
}

/********************************************************************************/
void spinMotor(int motorSpeed)                       //function for driving the right motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(AIN1, HIGH);                         //set pin 1 to high
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMA, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}
