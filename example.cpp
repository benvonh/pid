#include"pid.hpp"

#include<array>
#include<iostream>

int main()
{
  pid::PID<> controller{};
  controller.Kp = 10.0;
  controller.Ki = 1.0;
  controller.Kd = 2.0;

  std::array<double, 3> dts { 0.11, 0.12, 0.11 };
  std::array<double, 3> errors { 9.8, 7.6, 5.4 };

  for (size_t i = 0; i < 3; ++i)
  {
    controller.dt = dts[i];

    double output = controller(errors[i]);

    std::cout << "----------  LOOP " << i << "  ----------\n";
    std::cout << "controller.Kp  : " << controller.Kp << '\n';
    std::cout << "controller.Ki  : " << controller.Ki << '\n';
    std::cout << "controller.Kd  : " << controller.Kd << '\n';
    std::cout << "controller.dt  : " << controller.dt << '\n';
    std::cout << "error[i]       : " << errors[i] << '\n';
    std::cout << "output(error)  : " << output << '\n';
    std::cout << "prev_error : " << controller.prev_error() << '\n';
    std::cout << "total_error: " << controller.total_error() << '\n';
  }

  return 0;
}
