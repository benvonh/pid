#ifndef __PID_HPP__
#define __PID_HPP__

namespace pid
{
    template<typename T> class P;
    template<typename T> class I;
    template<typename T> class D;
    template<typename T> class Base;
    template<class... C> class Controller;

    template<typename T = double>
    using PI = Controller<P<T>, I<T>>;

    template<typename T = double>
    using PD = Controller<P<T>, D<T>>;

    template<typename T = double>
    using PID = Controller<P<I>, I<T>, D<T>>;

    template<typename T>
    class Base
    {
    protected:
        using _Type_ = T;

        virtual inline T Loop(const T err) = 0;
    };

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
    protected:
        T m_Sum;

        inline virtual T Loop(const T err) override
        {
            m_Sum += err;
            return Ki * m_Sum * Time;
        }

    public:
        T Ki;
        T Time;

        inline T GetTotalError() final const
        {
            return m_Sum;
        }
    };

    template<typename T>
    class D : protected Base<T>
    {
    protected:
        T m_Err;
        
        inline virtual T Loop(const T err) override
        {
            T prev_err = m_Err;
            m_Err = err;
            return Kd * (err - prev_err) / Period;
        }

    public:
        T Kd;
        T Period;

        inline T GetPrevError() final const
        {
            return m_Err;
        }
    };

    template<class... C>
    class Controller : public C...
    {
    public:
        using T = typename Controller::_Type_;

        inline T Control(const T err) override
        {
            return (C::Control(err) + ...);
        }
    };
};

#endif/*__PID_HPP__*/
