#ifndef __PID__CONTROLLER_HPP__
#define __PID__CONTROLLER_HPP__

#include "base.hpp"
#include "types.hpp"

namespace pid
{
template<class... C>
class Controller : public C...
{
public:
    using T = typename Controller::_Type_;

    inline T Loop(const T err) override
    {
        return (C::Loop(err) + ...);
    }
};

template<typename T = double>
using PI = Controller<P<T>, I<T>>;

template<typename T = double>
using PD = Controller<P<T>, D<T>>;

template<typename T = double>
using PID = Controller<P<T>, I<T>, D<T>>;
}

#endif/*__PID__CONTROLLER_HPP__*/
