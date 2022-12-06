#include "../pid/pid.hpp"

#include <iostream>

int main()
{
    pid::PI<> controller{};
    controller.Ki = 23;
    controller.Time = 1;
    std::cout << controller.Loop(5) << '\n';
}