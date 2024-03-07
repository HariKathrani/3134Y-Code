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
void inertial_rotation(vex::turnType direction, double degree) {
  Drivetrain.turnFor(direction, degree, deg); 
}

/*

All Code starts and is below this line.


*/
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
  Drivetrain.setDriveVelocity(92, percent);
  Intake.setVelocity(80, percent);
  /* 3/1/24
  // Drive backwards for 4 seconds
  Drivetrain.drive(forward);
  Intake.spin(forward);
  wait(4, seconds);

  Drivetrain.drive(reverse);

  wait(1, seconds);

  // Stop the drivetrain and intake
  Drivetrain.stop();
  Intake.stop();
  */
  Drivetrain.drive(reverse);
  wait(1.5, seconds);
  inertial_rotation(left, 50);
  Drivetrain.drive(reverse);
  wait(2.5, seconds);

  inertial_rotation(right, 180);

  Drivetrain.drive(forward);
  wait(50, msec);

  inertial_rotation(right, 150);

  Drivetrain.drive(forward);
  Intake.spin(reverse);
  wait(2.5, seconds);

  inertial_rotation(left, 70);
  Flaps.set(true);
  Drivetrain.drive(forward);
  Intake.spin(reverse);
  wait(2, seconds);

  Flaps.set(false);
  Drivetrain.drive(reverse);
  Intake.stop();
  wait(1, seconds);

  Drivetrain.stop();
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
