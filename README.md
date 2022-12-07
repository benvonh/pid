# pid

A simple and naive library for PID control. See `example/main.cpp` for tl;dr.

```
pid
├── controller
│   ├── controller.hpp
│   ├── interface.hpp
│   └── types.hpp
└── pid.hpp
```

# Usage

```C++
// All controllers under the `pid` namespace
using namespace pid;

// Template argument specifies the data type
P<float> proportional_controller;
I<double> integral_controller;
D<long double> derivative_controller;

// A controller class allows for types of control
// Nested template parameters must have the same data type
Controller<P<float>, I<float>> pi_controller;  // OK
Controller<P<float>, P<float>> pp_controller;  // compile-time error
Controller<P<float>, D<double>> pd_controller; // compile-time error

// NOTE: Controllers do not define a constructor
Controller<P<float>, I<float>, D<float>> pid_controller{}; // zero-initialised

// Aliases are provided for easier controller declaration
// Default template parameter is double
PI<float> pi_controller; // same as above
PID<> pid_controller;    // same as above but with double

// Depending on the controller composition, certain fields are inherited
pid_controller.Kp = 1.0; // only with P<>
pid_controller.Ki = 2.0; // only with I<>
pid_controller.Kd = 3.0; // only with D<>

// Some control types have special member functions
pid_controller.GetTotalError(); // only with I<>
pid_controller.GetPrevError();  // only with D<>
// ...and special field requirements
pid_controller.Time = 4.0;      // total time elapsed for I<>
pid_controller.Period = 5.0;    // sampling period for D<>

// To run the controller
pid_controller.Control(6.0);
proportional_controller.Control(7.0);
```