#ifndef __PID_HPP__
#define __PID_HPP__

namespace pid
{
template<typename T>
class Base
{
public:
  T dt;

  virtual const T operator()(const T err) = 0;

protected:
  using _Type_ = T;
};

template<typename T>
class P : virtual public Base<T>
{
public:
  T Kp;

  virtual const T operator()(const T err) override
  {
    return Kp * err;
  }
};

template<typename T>
class I : virtual public Base<T>
{
public:
  T Ki;

  virtual inline const T get_total_error() const final
  {
    return m_Sum;
  }

  virtual const T operator()(const T err) override
  {
    m_Sum += err * this->dt;
    return Ki * m_Sum;
  }

private:
  T m_Sum;
};

template<typename T>
class D : virtual public Base<T>
{
public:
  T Kd;

  virtual inline const T get_prev_error() const final
  {
    return m_Prev;
  }

  virtual const T operator()(const T err) override
  {
    T out = (err - m_Prev) / this->dt;
    m_Prev = err;
    return Kd * out;
  }

private:
  T m_Prev;
};

template<class... C>
class Controller : public C...
{
public:
  using T = typename Controller::_Type_;

  const T operator()(const T err) override
  {
    return (C::operator()(err) + ...);
  }
};

template<typename T=double>
using PI = Controller<P<T>, I<T>>;

template<typename T=double>
using PD = Controller<P<T>, D<T>>;

template<typename T=double>
using PID = Controller<P<T>, I<T>, D<T>>;
}

#endif/*__PID_HPP__*/
