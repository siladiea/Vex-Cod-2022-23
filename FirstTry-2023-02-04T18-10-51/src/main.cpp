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
// Intake               motor         6               
// FlyWheel             motor         10              
// LBack                motor         11              
// RBack                motor         12              
// LFront               motor         19              
// RFront               motor         20              
// Rollers              motor         7               
// Extension            motor         9               
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
  digital_out pneum = digital_out( Brain.ThreeWirePort.A);
  pneum.set( false );

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
  // ..........................................................................
Rollers.setVelocity(127, percent);
Rollers.startRotateFor(vex::directionType::fwd, 460, vex::rotationUnits::deg);

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

  //Drivetrain
  RFront.spin(vex::directionType::rev, Controller1.Axis3.value() - Controller1.Axis1.value() - Controller1.Axis4.value(), vex::velocityUnits::pct);
  RBack.spin(vex::directionType::rev, Controller1.Axis3.value() - Controller1.Axis1.value() + Controller1.Axis4.value(), vex::velocityUnits::pct);
  LFront.spin(vex::directionType::rev, Controller1.Axis3.value() + Controller1.Axis1.value() + Controller1.Axis4.value(),  vex::velocityUnits::pct);
  LBack.spin(vex::directionType::rev, Controller1.Axis3.value() + Controller1.Axis1.value() - Controller1.Axis4.value(), vex::velocityUnits::pct);



  //INTAKE 
  if(Controller1.ButtonR1.pressing()){
    Intake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  }

  else if(Controller1.ButtonR2.pressing()){
    Intake.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  }

  else{
    Intake.stop(vex::brakeType::brake);
  }

    if(Controller1.ButtonA.pressing()){
      Rollers.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    }

    else if(Controller1.ButtonB.pressing()){
      Rollers.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    }

    else{
      Rollers.stop(vex::brakeType::brake);
    }


  //OUTTAKE
  if(Controller1.ButtonL2.pressing()){
    FlyWheel.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  }

  else{
    FlyWheel.stop(vex::brakeType::coast);
  }
  //Pneumatics
  digital_out pneum = digital_out( Brain.ThreeWirePort.A);
  if(Controller1.ButtonL1.pressing()) {
      pneum.set( true );
      this_thread::sleep_for(500);
      pneum.set( false );
  }

    //Extension
  if(Controller1.ButtonX.pressing()){
    Extension.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  }
  else if(Controller1.ButtonY.pressing()){
    Extension.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  }
  else{
    Extension.stop(vex::brakeType::brake);
  }
  
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
