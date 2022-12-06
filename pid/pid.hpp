/**
 * @file pid.hpp
 * @author Benjamin von Snarski (benjaminvonsnarski@gmail.com)
 * @brief Header file for pid library.
 * @version 0.1
 * @date 06-12-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __PID_HPP__
#define __PID_HPP__

#include "controller/controller.hpp"

namespace pid
{
/**
 * @brief Alias to a Controller with P and I terms.
 * 
 * @tparam T Data type
 */
template<typename T = double>
using PI = Controller<P<T>, I<T>>;

/**
 * @brief Alias to a Controller with P and D terms.
 * 
 * @tparam T Data type
 */
template<typename T = double>
using PD = Controller<P<T>, D<T>>;

/**
 * @brief Alias to a Controller with P, I and D terms.
 * 
 * @tparam T Data type
 */
template<typename T = double>
using PID = Controller<P<T>, I<T>, D<T>>;
}

#endif/*__PID_HPP__*/