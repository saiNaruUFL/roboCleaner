
#include <IRremote.h>
//These are static variables defined to denote
//pin numbers on the arduino map to the motor-controllers
//This is used later used to control the motors to move the device
#define IR_RECEIVE_PIN 2  
#define LEFT_MOTOR_1 8
#define LEFT_MOTOR_2 9
#define RIGHT_MOTOR_1 10
#define RIGHT_MOTOR_2 11
#define MOTOR_CONTROLLER_1 3
#define MOTOR_CONTROLLER_2 4
#define MOTOR_CONTROLLER_3 5
#define MOTOR_CONTROLLER_4 6

bool isMoving = false;

//Here we initialize which type of "INPUT" or "OUTPUT"
//to all the pins used on the arduino. Since we are working with 
//motors, the arduino sends commands to the motors, thus those pins
//will be OUTPUT pins
void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);

  pinMode(LEFT_MOTOR_1, OUTPUT);
  pinMode(LEFT_MOTOR_2, OUTPUT);
  pinMode(RIGHT_MOTOR_1, OUTPUT);
  pinMode(RIGHT_MOTOR_2, OUTPUT);

  pinMode(MOTOR_CONTROLLER_1, OUTPUT);
  pinMode(MOTOR_CONTROLLER_2, OUTPUT);
  pinMode(MOTOR_CONTROLLER_3, OUTPUT);
  pinMode(MOTOR_CONTROLLER_4, OUTPUT);
}

void loop() {
  //Checks if the IR sensor reads a input value
  //in other words, did the user press a button
  if (IrReceiver.decode()) {
  
    //grabs which specific input and converts to an integer
    IrReceiver.resume();
    int move = IrReceiver.decodedIRData.command;
    Serial.println(move);
    
   
   //Based on the input number, a specific motor movements
   //will occur
    switch (move) {
      case 5:
        // Move both motors backwards
        digitalWrite(LEFT_MOTOR_1, LOW);
        digitalWrite(LEFT_MOTOR_2, HIGH);
        digitalWrite(RIGHT_MOTOR_1, LOW);
        digitalWrite(RIGHT_MOTOR_2, HIGH);
        break;
      case 0:
        // Move both motors forwards
        digitalWrite(LEFT_MOTOR_1, HIGH);
        digitalWrite(LEFT_MOTOR_2, LOW);
        digitalWrite(RIGHT_MOTOR_1, HIGH);
        digitalWrite(RIGHT_MOTOR_2, LOW);
        break;
      case 9:
        // Move right motor forwards and left backwards (right rotation spin)
        digitalWrite(RIGHT_MOTOR_1, HIGH);
        digitalWrite(RIGHT_MOTOR_2, LOW);
        digitalWrite(LEFT_MOTOR_1, LOW);
        digitalWrite(LEFT_MOTOR_2, HIGH);
        break;
      case 7: 
        // Move left motor forwards and right backwords (left rotation spin)
        digitalWrite(LEFT_MOTOR_1, HIGH);
        digitalWrite(LEFT_MOTOR_2, LOW);
        digitalWrite(RIGHT_MOTOR_1, LOW);
        digitalWrite(RIGHT_MOTOR_2, HIGH);
        break;
      case 4: 
        //Turn off washers
        digitalWrite(MOTOR_CONTROLLER_1, LOW);
        digitalWrite(MOTOR_CONTROLLER_2, LOW);
        digitalWrite(MOTOR_CONTROLLER_3, LOW);
        digitalWrite(MOTOR_CONTROLLER_4, LOW);
        break;
      case 27: 
        //Turn on washers
        digitalWrite(MOTOR_CONTROLLER_1, HIGH);
        digitalWrite(MOTOR_CONTROLLER_2, LOW);
        digitalWrite(MOTOR_CONTROLLER_3, HIGH);
        digitalWrite(MOTOR_CONTROLLER_4, LOW);
        break;  
      case 8:
        // Stop all motors
        digitalWrite(LEFT_MOTOR_1, LOW);
        digitalWrite(LEFT_MOTOR_2, LOW);
        digitalWrite(RIGHT_MOTOR_1, LOW);
        digitalWrite(RIGHT_MOTOR_2, LOW);
        isMoving = false;
        break;
    }
  }
}
