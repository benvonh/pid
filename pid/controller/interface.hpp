#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

namespace pid
{
template<typename T>
class Base
{
protected:
    using _Type_ = T;
protected:
    virtual inline T Control(T err) = 0;
};

template<typename T>
class P : protected Base<T>
{
public:
    T Kp;

protected:
    inline T Control(T err) override
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

public:
    inline T GetTotalError() const
    {
        return m_Sum;
    }

protected:
    T m_Sum;

protected:
    inline T Control(T err) override
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

public:
    inline T GetPrevError() const
    {
        return m_Err;
    }

protected:
    T m_Err;

protected:
    inline T Control(T err) override
    {
        T prev_err = m_Err;
        m_Err = err;
        return Kd * (err - prev_err) / Period;
    }
};
}

#endif/*__INTERFACE_HPP__*/