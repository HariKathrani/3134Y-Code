// Nearside Code (to do)

void autonomus(void) {

  //Set velocities
  Drivetrain.setDriveVelocity(92, percent);
  Intake.setVelocity(80, percent);

  Drivetrain.drive(forward);
  Intake.spin(forward);
  wait(4, seconds);

  Drivetrain.drive(reverse);

  wait(1, seconds);

  // Stop the drivetrain and intake
  Drivetrain.stop();
  Intake.stop();
}
