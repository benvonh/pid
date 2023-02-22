#ifndef __PID_HPP__
#define __PID_HPP__

#include "controller/controller.hpp"

namespace pid
{
template<typename T = double>
using PI = Controller<P<T>, I<T>>;

template<typename T = double>
using PD = Controller<P<T>, D<T>>;

template<typename T = double>
using PID = Controller<P<T>, I<T>, D<T>>;
};

#endif/*__PID_HPP__*/
