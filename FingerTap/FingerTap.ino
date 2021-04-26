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
      motorSpeed = temp;
      Serial.print("Motor Speed: ");      //print the speed that the motor is set to run at
      Serial.println(motorSpeed);
    }
  }

  if (digitalRead(7) == LOW) {          //if the switch is on...
    spinMotor(motorSpeed);
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
