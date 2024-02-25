#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftMotorA = motor(PORT17, ratio6_1, true);
motor leftMotorB = motor(PORT18, ratio6_1, true);
motor leftMotorC = motor(PORT19, ratio6_1, true);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB, leftMotorC);
motor rightMotorA = motor(PORT13, ratio6_1, false);
motor rightMotorB = motor(PORT2, ratio6_1, false);
motor rightMotorC = motor(PORT7, ratio6_1, false);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB, rightMotorC);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 299.24, 314.325, 228.6, mm, 0.5);
controller Controller1 = controller(primary);
motor Intake = motor(PORT15, ratio6_1, false);
motor Hang_Motor = motor(PORT5, ratio36_1, false);
digital_out Flaps = digital_out(Brain.ThreeWirePort.A);
digital_out Low_Hang = digital_out(Brain.ThreeWirePort.B);
// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1LeftShoulderControlMotorsStopped = true;
bool Controller1RightShoulderControlMotorsStopped = true;
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;
bool Flaps_Control = false;
bool Hang_Control = false;
bool intake_control = false;
//Function to prevent multiple toggles at once
void waitForButtonRelease(vex::controller::button button) {
    while (button.pressing()) {
        wait(20, msec);
    }
}
// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
            // Tank Control drivetrain
      // left = Axis3
      // right = Axis2
      int drivetrainLeftSideSpeed = Controller1.Axis3.position();
      int drivetrainRightSideSpeed = Controller1.Axis2.position();
      
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
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed * 0.92, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }
      //For the Hang Motor
      if (Controller1.ButtonL1.pressing()) {
        Hang_Motor.setStopping(hold);
        Hang_Motor.spin(forward, 100, percent);
        Controller1LeftShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonL2.pressing()) {
        Hang_Motor.spin(reverse, 100, percent);
        Controller1LeftShoulderControlMotorsStopped = false;
      } else if (!Controller1LeftShoulderControlMotorsStopped) {
        Hang_Motor.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1LeftShoulderControlMotorsStopped = true;
      }
      //For the intake
      if (Controller1.ButtonR1.pressing()) {
            // If intake is currently not spinning forward, start it
            if (!intake_control) {
                Intake.spin(forward, 100, percent);
                intake_control = true;
            }
        } else if (Controller1.ButtonR2.pressing()) {
            // If R2 is pressed, spin intake in reverse
            Intake.spin(reverse, 100, percent);
            intake_control = false; // Update direction
        } else {
            // If neither button is pressed, stop the intake
            Intake.stop();
            intake_control = false; // Update direction
        }
        // Hang and Flaps Control
        if (Controller1.ButtonUp.pressing()) {
            // Toggle direction
            Flaps_Control = !Flaps_Control;
            // Wait for button release to prevent multiple toggles in one press
            waitForButtonRelease(Controller1.ButtonUp);
        } else if (Controller1.ButtonX.pressing()) {
            // Toggle direction
            Hang_Control = !Hang_Control;
            // Wait for button release to prevent multiple toggles in one press
            waitForButtonRelease(Controller1.ButtonX);
        }
        if (Hang_Control) {
          Low_Hang.set(true);
        } else if (Flaps_Control) {
          Flaps.set(true);
        } else {
          Low_Hang.set(false);
          Flaps.set(false);
        }
    // wait before repeating the process
    wait(20, msec);
  } else {
  return 0;
  }
}
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}
