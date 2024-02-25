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
// Drivetrain           drivetrain    1, 2, 3, 4      
// Controller1          controller                    
// Intake               motor         5               
// Catapult             motor         6               
// Flaps                digital_out   A               
// Low_Hang             digital_out   B               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

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
  // ..........................................................................
  // Insert autonomous user code here.
  //LeftDriveSmart.setVelocity(100, percent);
  //RightDriveSmart.setVelocity(100, percent);
  // Drivetrain.setDriveVelocity(100, percent);
  // Intake.setVelocity(80, percent);
  // drivetrain_motors.setVelocity(100, percent);

  // Farside auton

  // Drivetrain.drive(forward);
  // wait(2, sec);
  // Intake.spinFor(forward, 1, sec);
  // Drivetrain.drive(reverse);
  // wait(2, sec);
  // RightDriveSmart.spinFor(reverse, 50, msec);
  // Drivetrain.drive(forward);
  // wait(25, msec);

  // Nearside auton

  // drivetrain_motors.spinFor(fwd, 1.5, seconds);
  // Intake.spinFor(reverse, 1, sec);
  // Drivetrain.drive(reverse);
  // wait(3,msec);
  // Drivetrain.drive(fwd);
  // wait(4, msec);
  // Drivetrain.stop();

  Drivetrain.setDriveVelocity(80, percent);
  Intake.setVelocity(80, percent);

  // Drive backwards for 3 seconds
  Drivetrain.drive(forward);
  Intake.spin(forward);
  wait(4, seconds);

  Drivetrain.drive(reverse);

  wait(1, seconds);

  // Stop the drivetrain and intake
  Drivetrain.stop();
  Intake.stop();
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
