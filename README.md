# pid
Minimal PID controller in C++

```C++
// Template defined in the `pid` namespace
using namespace pid;

// Template argument specifies data type
P<int> proportional;
I<float> integral;
D<double> derivative;

// Controller class combines P, I and D objects
Controller<P<float>, I<float>>     pi;  // ok
Controller<P<float>, P<float>>     pp;  // error
Controller<P<float>, D<double>>    pd;  // error
Controller<P<int>, I<int>, D<int>> pid; // ok

// Controllers do not define a constructor
Controller<P<float>, I<float>, D<float>> pid{}; // zero-initialise

// Aliases are defined for convenience
PI<float> pi;  // equivalent to `pi` above
PID<>     pid; // default type double

// Each controller object defines a gain field
pid.Kp = 1.0; // only for P<>
pid.Ki = 2.0; // only for I<>
pid.Kd = 3.0; // only for D<>

// Some controller types also define special member functions
double total_error = pid.GetTotalError(); // only for I<>
double prev_error  = pid.GetPrevError();  // only for D<>

// Ensure the `dt` field is always updated before every loop
pid.dt = 4.0;

// Pass the error to the controller for the output
double output = pid(5.0);
```
