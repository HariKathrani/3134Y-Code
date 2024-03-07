using namespace vex;

extern brain Brain;

// VEXcode devices
extern drivetrain Drivetrain;
extern controller Controller1;
extern motor Intake;
extern motor Hang_Motor;
extern digital_out Flaps;
extern digital_out Rachet;
extern motor_group LeftDriveSmart;
extern motor_group RightDriveSmart;
extern inertial Inertial1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
