/**
 * @file types.hpp
 * @author Benjamin von Snarski (benjaminvonsnarski@gmail.com)
 * @brief Header file for proportional, integral and derivative type definition.
 * @version 0.1
 * @date 07-12-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __TYPES_HPP__
#define __TYPES_HPP__

namespace pid
{
/**
 * @brief The proportional control type.
 * 
 * @tparam T Data type
 */
template<typename T>
class P : protected Base<T>
{
public:
    T Kp; /**< Proportional gain */

protected:
    /**
     * @brief The proportional control function.
     * 
     * @param err Controller input
     * @return T Controller output
     */
    inline T Control(const T err) override
    {
        return Kp * err;
    }
};

/**
 * @brief The integral control type.
 * 
 * @tparam T Data type
 */
template<typename T>
class I : protected Base<T>
{
public:
    T Ki; /**< Integral gain */
    T Time; /**< Total time elapsed */

public:
    /**
     * @brief Returns the total error.
     * 
     * @return T Sum of error
     */
    inline T GetTotalError() const
    {
        return m_Sum;
    }

protected:
    T m_Sum; /**< Sum of error */

protected:
    /**
     * @brief The integral control function.
     * 
     * Must update the Time field before each function call.
     * Internally updates the total error.
     * 
     * @see Time
     * @param err Control input
     * @return T Control output
     */
    inline T Control(const T err) override
    {
        m_Sum += err;
        return Ki * m_Sum * Time;
    }
};

/**
 * @brief The derivative control type.
 * 
 * @tparam T Data type
 */
template<typename T>
class D : protected Base<T>
{
public:
    T Kd; /**< Derivative gain */
    T Period; /**< Sampling period */

public:
    /**
     * @brief Returns the previous error.
     * 
     * @return T Previous error
     */
    inline T GetPrevError() const
    {
        return m_Err;
    }

protected:
    T m_Err; /**< Previous error */

protected:
    /**
     * @brief The derivative control function.
     * 
     * Must set the Period field before initial function call.
     * Internally updates the previous error.
     * 
     * @param err Control input
     * @return T Control output
     */
    inline T Control(const T err) override
    {
        T prev_err = m_Err;
        m_Err = err;
        return Kd * (err - prev_err) / Period;
    }
};
}

#endif/*__TYPES_HPP__*/