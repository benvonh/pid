#ifndef __CONTROLLER_HPP__
#define __CONTROLLER_HPP__

#include "interface.hpp"

namespace pid
{
template<class... C>
class Controller : public C...
{
using T = typename Controller::_Type_;

public:
    inline T Loop(T err)
    {
        return (C::Control(err) + ...);
    }
};
}

#endif/*__CONTROLLER_HPP__*/