#include"../pid.hpp"

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
  // Pre-generate example dt values
  std::array<double, 3> dts { 0.11, 0.12, 0.11 };
  // Pre-generate example error values
  std::array<double, 3> errors { 9.8, 7.6, 5.4 };
  
  //---------- CONTROLLER EXAMPLE USAGE ----------//
  // Enter control loop
  for (size_t i = 0; i < 3; ++i)
  {
    // Set current delta time
    controller.dt = dts[i];
    // Execute controller
    double output = controller(errors[i]);
    // Print control loop
    std::cout << "----------  LOOP " << i << "  ----------\n";
    std::cout << "controller.Kp  : " << controller.Kp << '\n';
    std::cout << "controller.Ki  : " << controller.Ki << '\n';
    std::cout << "controller.Kd  : " << controller.Kd << '\n';
    std::cout << "controller.dt  : " << controller.dt << '\n';
    std::cout << "error[i]       : " << errors[i] << '\n';
    std::cout << "output(error)  : " << output << '\n';
    std::cout << "get_prev_error : " << controller.get_prev_error() << '\n';
    std::cout << "get_total_error: " << controller.get_total_error() << '\n';
  }

  return 0;
}
