/**
 * This code will drive 2 bipoler stepper motors
 * using 2 Adafruit DRV8833
 * connected to UNO pins 2-5 driver 1 and 6-9 driver 2
 * 
 * 10k Pot controls Motor RPM
 * connected to UNO Pins A0 pot 1 and A1 pot 2
 * 
 * Lock Buttons
 * connected to UNO Pin A2 and A3
 * 
 * LCD
 * connected to UNO Pins A4 and A5
 * 
 **/

 
 // $Id: MultiStepper.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $
#include <AccelStepper.h>
#include <Stepper.h>

//number of seconds to wait in-between pot checks
#define UPDATETIME 30

// Define some steppers and the pins the will use
AccelStepper stepper1; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper2(AccelStepper::FULL4WIRE, 6, 7, 8, 9);

//assign Arduino pin connected to potentiometer
//analog pins should be prefixed with "A"
  const int PotPin1 = 0;
  const int PotPin2 = 1;
  
//assign a variable for analog reading from potentiometer
  //currnetSpeed1 = 0;
  //currentSpeed2 = 0;
  //int motorSpeeds [2];
  
void setup()
{    
  // initialize the serial communications:
  Serial.begin(9600);
  
  //declare the potentiometer pins as an INPUTs
  pinMode(PotPin1, INPUT);
  pinMode(PotPin2, INPUT);

  //stepper1.setAcceleration(300);
  stepper1.moveTo(50);
   
  //stepper2.setAcceleration(300);
  stepper2.moveTo(50);
}

//at the start of this loop, read the pots and set the new speeds
//then run the motors until the time for the next check
void loop()
{
    static float current_speed = 0;         //holds current motor speed in steps/sec
    unsigned long targetTime = millis() + 1000*UPDATETIME;

    // read the potentiometer value:
    int potReading1 = analogRead(PotPin1);
    int potReading2 = analogRead(PotPin2);
  
    // map it to a range from 0 to 100:
    int motorSpeed1 = map(potReading1, 0, 1023, 1, 150);
    int motorSpeed2 = map(potReading2, 0, 1023, 1, 150);

    //update the stepper to run at this new speed
    stepper1.setSpeed(motorSpeed1);
    stepper2.setSpeed(motorSpeed2);
    
    //stay in this loop until the next time you need to check the pots
    while(millis() < targetTime)
    {
        //run the motors for a bit before checking the time, for efficiency
        for(int count = 1000; count > 0; count--)
        {
            stepper1.runSpeed();
            stepper2.runSpeed();
        }
    }

    //store motor speed values
    //motorSpeeds [0] = motorSpeed1;
    //motorSpeeds [1] = motorSpeed2;

    //currentSpeed1 = motorSpeed [0];
    //currentSpeed2 = motorSpeed [1];
}

