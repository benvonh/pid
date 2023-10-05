// MIT License
//
// Copyright (c) 2023 Benjamin von Snarski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#pragma once

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
