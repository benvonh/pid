#include"pid.hpp"

#include<array>
#include<iostream>

int main()
{
  //---------- CONTROLLER SETUP ----------//
  // Zero-initialise PID controller with default type double
  pid::PID<> controller{};
  // Set proportional gain
  controller.Kp = 10.0;
  // Set integral gain
  controller.Ki = 1.0;
  // Set derivative gain
  controller.Kd = 2.0;

  //---------- EXAMPLE SETUP ----------//
  // Pre-generate example error values
  std::array<double, 3> error { 9.8, 7.6, 5.4 };
  // Seed random delta times
  std::srand(123);
  
  //---------- CONTROLLER EXAMPLE USAGE ----------//
  // Enter control loop
  for (size_t i = 0; i < 3; ++i)
  {
    // Get random delta time
    double dt = std::rand() / (double)RAND_MAX;
    // Set current delta time
    controller.dt = dt;
    // Execute controller
    double output = controller(error[i]);
    // Print control loop
    std::cout << "\n---------- LOOP " << i << " ----------";
    std::cout << "\ncontroller.Kp : " << controller.Kp;
    std::cout << "\ncontroller.Ki : " << controller.Ki;
    std::cout << "\ncontroller.Kd : " << controller.Kd;
    std::cout << "\ncontroller.dt : " << controller.dt;
    std::cout << "\nerror[i]      : " << error[i];
    std::cout << "\noutput(error) : " << output;
    std::cout << "\nGetPrevError  : " << controller.GetPrevError();
    std::cout << "\nGetTotalError : " << controller.GetTotalError();
  }

  return 0;
}
