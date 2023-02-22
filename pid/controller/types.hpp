#ifndef __PID__TYPES_HPP__
#define __PID__TYPES_HPP__

#include "base.hpp"

namespace pid
{

template<typename T>
class P : protected Base<T>
{
public:
    T Kp;

protected:
    inline virtual T Loop(const T err) override
    {
        return Kp * err;
    }
};

template<typename T>
class I : protected Base<T>
{
public:
    T Ki;
    T Time;

    inline virtual T GetTotalError() const final
    {
        return m_Sum;
    }

protected:
    T m_Sum;

    inline virtual T Loop(const T err) override
    {
        m_Sum += err;
        return Ki * m_Sum * Time;
    }
};

template<typename T>
class D : protected Base<T>
{
public:
    T Kd;
    T Period;

    inline virtual T GetPrevError() const final
    {
        return m_Err;
    }

protected:
    T m_Err;
    
    inline virtual T Loop(const T err) override
    {
        T prev_err = m_Err;
        m_Err = err;
        return Kd * (err - prev_err) / Period;
    }
};

}

#endif/*__PID__TYPES_HPP__*/
