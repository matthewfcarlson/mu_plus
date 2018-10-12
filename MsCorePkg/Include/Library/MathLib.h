/** @file
This library supports generic XML queries based on the Xml Tree lib.


Copyright (c) 2018, Microsoft Corporation

All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

**/

#ifndef __MU_MATH_LIB__
#define __MU_MATH_LIB__

/**
Find sine of a provided double in radians

@param[in]  angle to calculate in radians

@retval the result (double)
**/
double
EFIAPI
sin_d(
  IN CONST double angleInRadians  
);


/**
Find cosine of a provided double in radians

@param[in]  angle to calculate in radians

@retval the result (double)
**/
double
EFIAPI
cos_d(
  IN CONST double angleInRadians
);

/**
Find square root of the provided double

@param[in]  the number to square root

@retval result when input >0 otherwise returns input
**/
double
EFIAPI
sqrt_d(
  IN CONST double input
);

/**
Find sine of a provided unsigned integer in degrees

@param[in]  angle to calculate in degrees

@retval the result * 100
**/
UINT32
EFIAPI
sin_u32(
  IN CONST UINT32 angleInDegrees  
);


/**
Find cosine of a provided unsigned integer in degrees

@param[in]  angle to calculate in degrees

@retval the result * 100
**/
UINT32
EFIAPI
cos_u32(
  IN CONST UINT32 angleInDegrees
);

/**
Find square root of the provided unsigned integer

@param[in]  the number to square root

@retval result when input >0 otherwise returns input
**/
UINT32
EFIAPI
sqrt_u32(
  IN CONST UINT32 input
);

/**
Find square root of the provided unsigned 64bit integer

@param[in]  the number to square root

@retval result when input >0 otherwise returns input
**/
UINT64
EFIAPI
sqrt_u64(
  IN CONST UINT32 input
);

#endif
