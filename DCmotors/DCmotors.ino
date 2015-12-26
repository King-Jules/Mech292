/*Controlling DC motors with Ardudroid App via bluetooth HC05 Connector
 * written by Julien Brillon @ McGill University, Mechanical Engineering
 * Mech 292 - Robot/golf ball mechanism
 */
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *Arm = AFMS.getMotor(1); // for connection M1 - MECHANISM / ARM
Adafruit_DCMotor *Motor1 = AFMS.getMotor(2);  //for connection M2 - LEFT MOTOR
Adafruit_DCMotor *Motor2 = AFMS.getMotor(4);   // for connection M4 - RIGHT MOTOR

int state = 0;

void setup() {
  AFMS.begin();
  Serial.begin(9600);
}

void loop() {
  while (Serial.available()>0){
    state = Serial.read();
  
  // 0 = Brake / Stop all motors
  if (state == '0') {
    Motor1->setSpeed(0);
    Motor2->setSpeed(0);
    Arm->setSpeed(0);
    Motor1->run(BRAKE);
    Motor2->run(BRAKE);
    Arm->run(BRAKE);

    Serial.println("Brake");
  }

  // 1 = Backwards
  else if (state == '1'){
    Motor1->setSpeed(100); 
    Motor2->setSpeed(100);
    Motor1->run(FORWARD);
    Motor2->run(FORWARD);

    Serial.println("Backwards");
  }

  // 2 = Forwards
  else if (state == '2'){
    Motor1->setSpeed(100);
    Motor2->setSpeed(100);
    Motor1->run(BACKWARD);
    Motor2->run(BACKWARD);

    Serial.println("Forwards");
  }

  // 3 = Turn Left
  else if (state == '3'){
    Motor1->setSpeed(20); //Set 100 to turn slow
    Motor2->setSpeed(20);
    Motor1->run(FORWARD);
    Motor2->run(BACKWARD);
  
    Serial.println("Turn Left by 90deg");
  }

  // 4 = Turn Right
  else if (state == '4'){
    Motor1->setSpeed(70); //Set 50 to turn slow
    Motor2->setSpeed(70);
    Motor1->run(BACKWARD);
    Motor2->run(FORWARD);
    delay(700);        // waits for a second
    Motor1->setSpeed(0);
    Motor2->setSpeed(0);
    Arm->setSpeed(0);
    Motor1->run(BRAKE);
    Motor2->run(BRAKE);
    Arm->run(BRAKE);

    Serial.println("Turn Right");
  }

  // 5 = Mechanism UP
  else if (state == '5'){
    Motor1->setSpeed(0);
    Motor2->setSpeed(0);
    Arm->setSpeed(255); 
    Motor1->run(BRAKE);
    Motor2->run(BRAKE);
    Arm->run(FORWARD);
    delay(190);        // waits for a second
    Motor1->setSpeed(0);
    Motor2->setSpeed(0);
    Arm->setSpeed(0);
    Motor1->run(BRAKE);
    Motor2->run(BRAKE);
    Arm->run(BRAKE);

    Serial.println("Arm Down");
  }

  // 6 = Mechanism DOWN
  else if (state == '6'){
    Motor1->setSpeed(0);
    Motor2->setSpeed(0);
    Arm->setSpeed(170);
    Motor1->run(BRAKE);
    Motor2->run(BRAKE);
    Arm->run(BACKWARD);
    delay(150);        //waits for a second
    Motor1->setSpeed(0);
    Motor2->setSpeed(0);
    Arm->setSpeed(0);
    Motor1->run(BRAKE);
    Motor2->run(BRAKE);
    Arm->run(BRAKE);

    Serial.println("Arm Up");
  }

  // 7 = Slow Backwards for pickup/dropping ball
  else if (state == '7'){
    Motor1->setSpeed(35);
    Motor2->setSpeed(35);
    Motor1->run(FORWARD);
    Motor2->run(FORWARD);
    /*delay(300);        //waits for a second
    Motor1->setSpeed(0);
    Motor2->setSpeed(0);
    Arm->setSpeed(0);
    Motor1->run(BRAKE);
    Motor2->run(BRAKE);
    Arm->run(BRAKE);*/

    Serial.println("Slow");
  }

  // 8 = MAX SPEED - Forwards
  else if (state == '8'){
    Motor1->setSpeed(255); //255 = max speed
    Motor2->setSpeed(255);
    Arm->setSpeed(255);
    Motor1->run(BACKWARD);
    Motor2->run(BACKWARD);
    Arm->run(FORWARD);

    Serial.println("Max Speed");
  }

  else if (state == '9'){
    Motor1->setSpeed(20); //Set 100 to turn slow
    Motor2->setSpeed(20);
    Motor1->run(BACKWARD);
    Motor2->run(FORWARD);
  
    Serial.println("Turn Left");
  }
 
  }

}
