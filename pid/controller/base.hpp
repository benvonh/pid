#ifndef __PID__BASE_HPP__
#define __PID__BASE_HPP__

namespace pid
{
template<typename T>
class Base
{
protected:
    using _Type_ = T;

    inline virtual T Loop(const T err) = 0;
};
}

#endif/*__PID__BASE_HPP__*/
