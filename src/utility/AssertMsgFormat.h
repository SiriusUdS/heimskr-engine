#pragma once

#include <iostream>

#ifndef NDEBUG
/**
 * \brief Assert macro that allows to print variable values within the error message.
 * \param[in] condition condition to check.
 * \param[in] message message to print if the condition is false.
 */
#define ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#   define ASSERT(condition, message) do { } while (false)
#endif
