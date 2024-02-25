using namespace vex;

extern brain Brain;

// VEXcode devices
extern drivetrain Drivetrain;
extern controller Controller1;
extern motor Intake;
extern motor Hang_Motor;
extern digital_out Flaps;
extern digital_out Low_Hang;
extern motor_group LeftDriveSmart;
extern motor_group RightDriveSmart;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
