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
  virtual T operator()(const T err) = 0;

  T dt;

protected:
  using ValueType = T;
};

template<typename T>
class P : virtual public Base<T>
{
public:
  T operator()(const T err) override
  {
    return Kp * err;
  }

  T Kp;
};

template<typename T>
class I : virtual public Base<T>
{
public:
  T operator()(const T err) override
  {
    M_sum += err * this->dt;
    return Ki * M_sum;
  }

  virtual T total_error() const final
  {
    return M_sum;
  }

  T Ki;

private:
  T M_sum;
};

template<typename T>
class D : virtual public Base<T>
{
public:
  T operator()(const T err) override
  {
    T out = (err - m_Prev) / this->dt;
    m_Prev = err;
    return Kd * out;
  }

  virtual T last_error() const final
  {
    return m_Prev;
  }

  T Kd;

private:
  T m_Prev;
};

template<class... C>
class Controller : public C...
{
  using T = typename Controller::ValueType;

public:
  T operator()(const T err) override
  {
    return (C::operator()(err) + ...);
  }
};

template<typename T = double>
using PI = Controller<P<T>, I<T>>;

template<typename T = double>
using PD = Controller<P<T>, D<T>>;

template<typename T = double>
using PID = Controller<P<T>, I<T>, D<T>>;
}
