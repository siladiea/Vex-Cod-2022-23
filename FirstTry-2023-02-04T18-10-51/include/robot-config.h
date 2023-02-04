using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor Intake;
extern motor FlyWheel;
extern motor LBack;
extern motor RBack;
extern motor LFront;
extern motor RFront;
extern motor Rollers;
extern motor Extension;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );