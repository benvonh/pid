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

#include "interface.hpp"
#include "types.hpp"

namespace pid
{
/**
 * @brief A Controller class derived from any combination of P, I and D types.
 * 
 * Types that are inherited must also inherit from Base which guarantee the
 * Control() function implementation for each component in the controller.
 * Only one of each type can be used with the same typename parameter or a
 * compilation error will occur.
 * 
 * @tparam C Comma-separated list of unique P, I or D types
 */
template<class... C>
class Controller : public C...
{
using T = typename Controller::_Type_; /**< Inherited data type */

public:
    /**
     * @brief Compute each control type and return the controller output.
     * 
     * @param err Controller input
     * @return T Controller output
     */
    inline T Control(const T err) override
    {
        return (C::Control(err) + ...);
    }
};
}

#endif/*__CONTROLLER_HPP__*/