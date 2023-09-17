# pid
Minimal PID controller for C++ and Python

## Usage
**C++**
```cpp
// Template defined in the `pid` namespace
using namespace pid;

// Template argument specifies data type
P<int> proportional;
I<float> integral;
D<double> derivative;

// Controller parent class combines P, I and D child classes
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
double totalError = pid.get_total_error(); // only for I<>
double prevError  = pid.get_prev_error();  // only for D<>

// Ensure the `dt` field is always updated during every loop
pid.dt = 4.0;

// Pass the error to the controller for the output with the () operator
double output = pid(5.0);
```
**Python**
```py
# Copy or package the `pid.py` file
import pid

# P, I and D sub-classes correspopnd to PID terms
p = pid.P()
i = pid.I()
d = pid.D()

# Sub-classes are inherited to create PI, PD and PID super-classes
pi = pid.PI()
pd = pid.PD()
pid = pid.PID()

# Each sub-class define a gain attribute
pid.Kp = 1.0 # only for P()
pid.Ki = 2.0 # only for I()
pid.Kd = 3.0 # only for D()

# Some classes also define special member functions
totalError = pid.get_total_error() # only for I()
prevError  = pid.get_prev_error()  # only for D()

# Ensure the `dt` attribute is always updated during every loop
pid.dt = 4.0

# Pass the error to the controller for the output with the `__call__` method
output = pid(5.0)
```

## Examples
**Manual**
```sh
g++ examples/example.cpp -o example
export PYTHONPATH=$PYTHONPATH:$PWD
./example
./examples/example.py
```
**Nix flake**
```sh
nix build
nix develop
./result/example
./result/example.py
```
