/**
 * @file interface.hpp
 * @author Benjamin von Snarski (benjaminvonsnarski@gmail.com)
 * @brief Header file for base control interface.
 * @version 0.1
 * @date 07-12-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

namespace pid
{
/**
 * @brief An abstract base class interface for derived controllers.
 * 
 * @tparam T Data type
 */
template<typename T>
class Base
{
protected:
    using _Type_ = T; /**< Inheritable data type */
protected:
    /**
     * @brief The control function to be implemented.
     * 
     * @param err Controller input
     * @return T Controller output
     */
    virtual inline T Control(const T err) = 0;
};
}

#endif/*__INTERFACE_HPP__*/
