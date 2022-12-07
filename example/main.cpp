#include "pid/pid.hpp"

int main()
{
    // Create PID controller with type double
    pid::PID<> controller;

    // Set controller gains
    controller.Kp = 1.0;
    controller.Ki = 2.0;
    controller.Kd = 3.0;

    // Set sampling period
    controller.Period = 1.0;

    // Run control loop 
    for (double i = 1.0; i < 10.0; i++)
    {
        // Update total time elapsed
        controller.Time = i;

        // Get controller output (input = time in this example)
        double output = controller.Control(i);
    }

    // Get previous and total error
    double prev_error = controller.GetPrevError();
    double total_error = controller.GetTotalError();

    return 0;
}