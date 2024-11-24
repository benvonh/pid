# pid

Single header PID controller. See `pid.hpp`.

## Usage

```cpp
// Controller defined in the `pid` namespace
using namespace pid;

// Template argument specifies data type
P<int> proportional;
I<float> integral;
D<double> derivative;

// Controller class inherits P,I,D sub-classes
Controller<P<float>, I<float>>     pi;  // good
Controller<P<float>, P<float>>     pp;  // error - repeated P sub-class
Controller<P<float>, D<double>>    pd;  // error - different data types
Controller<P<int>, I<int>, D<int>> pid; // good

// Controllers do not define a constructor
Controller<P<float>, I<float>, D<float>> pid{}; // zero-initialize

// Aliases are defined for convenience
PI<float> pi;  // equivalent to the `pi` variable above
PID<>     pid; // default data type is double

// Each controller object defines a gain field
pid.Kp = 1.0; // only from P<>
pid.Ki = 2.0; // only from I<>
pid.Kd = 3.0; // only from D<>

// Some controller sub-classes also define specific methods
double totalError = pid.total_error(); // only from I<>
double prevError  = pid.prev_error();  // only from D<>

// Ensure the `dt` field is correct in every loop
pid.dt = 4.0;

// Use the controller by passing the error to the operator()
double output = pid(5.0);
```

## Examples

**Manual**

```sh
g++ -o example example.cpp
./example
```

**Nix flake**

```sh
nix build
./result/example
```
