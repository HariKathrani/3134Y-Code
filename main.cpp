/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    1, 2, 3, 4      
// Intake               motor         7               
// Flywheel             motor         8               
// FlapA                digital_out   A               
// FlapB                digital_out   B               
// Outside_Flap         digital_out   C               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor leftMotorA = motor(PORT12, ratio6_1, false); //5
motor leftMotorB = motor(PORT20, ratio6_1, false); //18
motor leftMotorC = motor(PORT15, ratio6_1, false); //16
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB, leftMotorC);
motor rightMotorA = motor(PORT5, ratio6_1, true); //12
motor rightMotorB = motor(PORT18, ratio6_1, true); //20
motor rightMotorC = motor(PORT16, ratio6_1, true); //15
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB, rightMotorC);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 299.24, 381, 368.29999999999995, mm, 0.3333333333333333);
motor Intake = motor(PORT7, ratio6_1, false);
motor Flywheel = motor(PORT19, ratio6_1, false);
digital_out FlapA = digital_out(Brain.ThreeWirePort.A);
digital_out FlapB = digital_out(Brain.ThreeWirePort.B);
digital_out Outside_Flap = digital_out(Brain.ThreeWirePort.C);
motor_group drivetrain_motors = motor_group(leftMotorA, leftMotorB, leftMotorC, rightMotorA, rightMotorB, rightMotorC);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1LeftShoulderControlMotorsStopped = true;
bool Controller1RightShoulderControlMotorsStopped = true;
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;
bool Flaps1 = false;
bool Flaps2 = false;
bool flywheel_control = false;
bool flywheel_control_reverse = false;
// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  LeftDriveSmart.setVelocity(100, percent);
  RightDriveSmart.setVelocity(100, percent);
  drivetrain_motors.setVelocity(100, percent);
  Intake.setVelocity(100, percent);
  drivetrain_motors.spinFor(fwd, 1.5, seconds);
  Intake.spinFor(fwd, 2, sec);
  LeftDriveSmart.spinFor(fwd, .5, seconds);
  Intake.spinFor(reverse, .5, seconds);
  drivetrain_motors.spinFor(fwd, 1, sec);
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    if(RemoteControlCodeEnabled) {
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3 + Axis1
      // right = Axis3 - Axis1
      int drivetrainLeftSideSpeed = Controller1.Axis3.position() - Controller1.Axis1.position();
      int drivetrainRightSideSpeed = Controller1.Axis3.position() + Controller1.Axis1.position();
      
      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftDriveSmart.stop();
          // tell the code that the left motor has been stopped
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          // stop the right drive motor
          RightDriveSmart.stop();
          // tell the code that the right motor has been stopped
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }
    }
      // check the ButtonR1/ButtonR2 status to control Intake
      if (Controller1.ButtonR1.pressing()) {
        Intake.spin(fwd, 100, percent);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonR2.pressing()) {
        Intake.spin(reverse, 100, percent);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (!Controller1RightShoulderControlMotorsStopped) {
        Intake.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1RightShoulderControlMotorsStopped = true;
      }
        if (Controller1.ButtonUp.pressing()) {
          Flaps1 =! Flaps1;
          FlapA.set(Flaps1);
          FlapB.set(Flaps1);
          // If this doesn't work check the value of the boolean
        } else {
          FlapA.set(false);
          FlapB.set(false);
        }
        if (Controller1.ButtonDown.pressing()) {
          Flaps1 = false;
          FlapA.set(false);
          FlapB.set(false);
        }
        if (Controller1.ButtonRight.pressing()) {
          Flaps2 =! Flaps2;
          Outside_Flap.set(Flaps2);
        } else {
          Outside_Flap.set(false);
        }
        if (Controller1.ButtonLeft.pressing()) {
          Flaps2 = false;
          Outside_Flap.set(false);
        }
        if (Controller1.ButtonL1.pressing()) {
          flywheel_control = true;
        } else if (Controller1.ButtonL2.pressing()) {
          flywheel_control = false;
        }
        if (flywheel_control==true) {
          Flywheel.spin(forward, 85.7142857, percent);
          Controller1LeftShoulderControlMotorsStopped = false;
        } else if (flywheel_control==false) {
          Flywheel.stop();
          Controller1LeftShoulderControlMotorsStopped = true;
        }
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
