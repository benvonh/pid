# pid

Minimal PID control library.


Written in 100 lines of code, the library offers basic PID functionality. For
more specialised features such as output clamping and internal timing, you
should create helper functions or a wrapper class.

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
// Library under the `pid` namespace
using namespace pid;

// Template argument specifies data type
P<int>    proportional;
I<float>  integral;
D<double> derivative;

// Controller class can combine controller types
Controller<P<float>, I<float>>  pi; // ok
Controller<P<float>, P<float>>  pp; // error
Controller<P<float>, D<double>> pd; // error

// Controllers do not define a constructor
// and should be zero-initialised
Controller<P<float>, I<float>, D<float>> pid{};

// Aliases are defined for convenience
// Default parameter is `double`
PI<float> pi;
PID<>     pid;

// Each controller type defines its own gain field
pid.Kp = 1.0; // only for P<>
pid.Ki = 2.0; // only for I<>
pid.Kd = 3.0; // only for D<>

// Some controller types also define special member functions
double total_error = pid.GetTotalError(); // only for I<>
double prev_error  = pid.GetPrevError();  // only for D<>
// ...and field requirements
pid.Time   = 4.0; // time elapsed    - only for I<>
pid.Period = 5.0; // sampling period - only for D<>

// To run the controller, pass the error
double output = pid.Loop(6.0);
```
