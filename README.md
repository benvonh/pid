# pid

Minimal PID control library.

## Example

```C++
#include "pid/pid.hpp"

int main()
{
    pid::PID<> controller{};
    double error = 10.0;
    double period = 0.1;

    controller.Kp = 1.0;
    controller.Ki = 2.0;
    controller.Kd = 3.0;

    controller.Period = period;

    for (double time = 0.0; time < 1.0; time += period)
    {
        controller.Time = time;

        double output = controller.Loop(error);
        double prev_err = controller.GetPrevError();
        double total_err = controller.GetTotalError();
    }

    return 0;
}
```

## Usage

```C++
// Library defined in the `pid` namespace
using namespace pid;

// Template argument specifies data type
P<int> proportional;
I<float> integral;
D<double> derivative;

// Controller class combines P, I and D types
Controller<P<float>, I<float>> pi;      // ok
Controller<P<float>, P<float>> pp;      // error
Controller<P<float>, D<double>> pd;     // error
Controller<P<int>, I<int>, D<int>> pid; // ok

// Controllers do not define a constructor
Controller<P<float>, I<float>, D<float>> pid{}; // zero-initialise

// Aliases are defined for convenience
PI<float> pi;  // equivalent to `pi` above
PID<>     pid; // default template double

// Each controller type defines a gain field
pid.Kp = 1.0; // only for P<>
pid.Ki = 2.0; // only for I<>
pid.Kd = 3.0; // only for D<>

// Some controller types also define special member functions
double total_error = pid.GetTotalError(); // only for I<>
double prev_error  = pid.GetPrevError();  // only for D<>
// ...and field requirements
pid.Time   = 4.0; // only for I<> - time elapsed
pid.Period = 5.0; // only for D<> - sampling period

// Pass the error to run the control loop
double output = pid.Loop(6.0);
```
