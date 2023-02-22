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

}

#endif/*__PID__CONTROLLER_HPP__*/
