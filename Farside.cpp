// Farside Auton

void autonomus(void) {
  Drivetrain.setVelocity(100, pct);
  Intake.setVelocity(80, pct);

  Drivetrain.driveFor(forward, 38, inches);
  Intake.spinFor(forward, 2, seconds);

  Intake.spinFor(reverse, 1, second)

  Drivetrain.driveFor(reverse, 3, inches);
  Drivetrain.setRotation(
}
