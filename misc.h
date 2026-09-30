#ifndef _MISC_HEADER_
#define _MISC_HEADER_
#include <stdint.h>

#ifdef __CUDACC__
/*
  if compiling to cuda
  it's have an issue with overlapping of
  global and __global__ keywords
*/
#define cuda_internal static
#define cuda_global   static

#else

#define internal static
#define global   static

#endif


#define uchar    unsigned char
#define uint     unsigned int
#define bool32   int32_t
#define s8       int8_t
#define s16      int16_t
#define s32      int32_t
#define s64      int64_t
#define u8       uint8_t
#define u16      uint16_t
#define u32      uint32_t
#define u64      uint64_t
#define f32      float
#define f64      double
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1


#ifndef true
#define true 1
#define false 0
#endif
// for old c compiling
#endif
