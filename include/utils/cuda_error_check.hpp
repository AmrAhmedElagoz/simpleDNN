#pragma once

#include <driver_types.h>


#ifndef _DEBUG
//if not in debug mode then return the same input 
#define cuda_check(x) (x)

// if we in debug mode then we need a function that takes the result of a cuda call and return
// what the error is and where it happends
#else
// #x gives us the name of the function, __FILE__ gives us the error file and __LINE__ the error line
#define cuda_check(x) cuda_call_check(x, #x, __FILE__, __LINE__)

#endif  //_DEBUG

void cuda_call_check(cudaError_t result, const char *function_name, const char *filename, int line_name);