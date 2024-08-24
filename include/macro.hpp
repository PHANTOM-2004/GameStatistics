/// \file
/// \brief some common macro
#pragma once

#ifndef __SELF_MACRO_HPP__
#define __SELF_MACRO_HPP__

/// \brief conditional compiling macro for debug
#define _DSA_DEBUG

/// \brief macro to get the size of the array
#define SIZEOF_ARRAY(arr) (sizeof(arr) / sizeof(arr[0]))
#endif
