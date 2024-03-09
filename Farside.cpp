// Farside Auton

void autonomus(void) {
  //Setting Drive Velocity
  Drivetrain.setVelocity(100, pct);
  Intake.setVelocity(80, pct);

  Drivetrain.drive(forward);
  wait(4, seconds);

  Drivetrain.setRotation(180, deg);

  Drivetrain.drive(forward);
  Intake.spin(reverse);
  wait(1, seconds);

  Drivetrain.drive(reverse);
  wait(50, msec);

  Drivetrain.setRotation(270, deg);

  Drivetrain.drive(forward);
  Intake.spin(forward);
  wait(3, seconds);

  Intake.stop()
  Drivetrain.setRotation(210, deg);

  Drivetrain.drive(forward);
  wait(3, seconds);

  Intake.spin(reverse);
  wait(1, second);

  Drivetrain.stop()
  Intake.stop()
}
