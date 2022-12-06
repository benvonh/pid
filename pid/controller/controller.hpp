/**
 * @file controller.hpp
 * @author Benjamin von Snarski (benjaminvonsnarski@gmail.com)
 * @brief Header file for controller definition.
 * @version 0.1
 * @date 06-12-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __CONTROLLER_HPP__
#define __CONTROLLER_HPP__

namespace pid
{
/**
 * @brief A Controller class derived from any combination of P, I and D types.
 * 
 * Types that are inherited must also inherit from Base which guarantee the
 * Control() function implementation. Only one of each type can be used with the
 * same typename parameter or a compilation error will occur.
 * 
 * @tparam C Comma-separated list of P, I and D types
 */
template<class... C>
class Controller : public C...
{
using T = typename Controller::_Type_; /**< Inherited data type */

public:
    /**
     * @brief Compute each control type and return its sum.
     * 
     * @param err Controller input
     * @return T Controller output
     */
    inline T Loop(T err)
    {
        return (C::Control(err) + ...);
    }
};
}

#include "interface.hpp"

#endif/*__CONTROLLER_HPP__*/