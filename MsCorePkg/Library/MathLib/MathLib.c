/** @file
XmlTreeQueryLib

This library supports generic XML queries based on the XmlTreeLib. 

Copyright (c) 2016, Microsoft Corporation

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
#include <Uefi.h>
#include <Library/MathLib.h>

/**
Find sine of a provided double in radians

@param[in]  angle to calculate in radians

@retval the result (double)
**/
double
EFIAPI
sin_d(
  IN CONST double angleInRadians  
){
    //Using taylor series expansions
    //https://en.wikipedia.org/wiki/Trigonometric_functions#Series_definitions
    //so far seems comparable performance to the build in sin function from math.h
    //first range modify it to be within 0 and 2 pi
    while (radians > 2* MU_PI){
        radians -= 2*MU_PI;
    }
    while (radians < -2* MU_PI){
        radians += 2*MU_PI;
    }
    
    //compute the first iteration
    //Formula is sum over N to infinity with x being the radians
    // -1^n x^(2n+1)
    //----------------
    //    (2n+1)!
    double previousValue = radians; //x0
    int16_t multiply = -1; //we subtract first possibly faster
    uint32_t iterationCount = 5; //
    double top = radians * radians * radians; //x^3
    long denom = 3*2; //3!
    double value = previousValue - (top/denom);

    //iterate 7 iterations
    for (iterationCount;iterationCount <= 19;iterationCount+=2){ 
        previousValue = value;
        denom *= iterationCount * (iterationCount-1); //n * n-1 * (previous compued n-2!)
        top *= radians * radians; // x^2 * (previous computed x^n-2)
        multiply *= -1; //invert the sign
        //could be possibly faster to not use multiply but a conditional move?
        value = previousValue + (multiply*top/denom);
    }
    //checking for convergence provides neglieble speedup and a drop in accuracy.

    return value;
}


/**
Find cosine of a provided double in radians

@param[in]  angle to calculate in radians

@retval the result (double)
**/
double
EFIAPI
cos_d(
  IN CONST double angleInRadians
){
    //Using taylor series expansions
    //https://en.wikipedia.org/wiki/Trigonometric_functions#Series_definitions
    //so far seems to be slightly slower to built in COS
    //first range modify it to be within 0 and 2 pi
    while (radians > 2* MU_PI){
        radians -= 2*MU_PI;
    }
    while (radians < -2* MU_PI){
        radians += 2*MU_PI;
    }
    
    //compute the first iteration
    //Formula is sum over N to infinity with x being the radians
    // -1^n x^(2n)
    //----------------
    //    (2n)!
    double previousValue = 1; //x0
    int16_t multiply = -1; //we subtract first possibly faster
    uint32_t iterationCount = 4; //we start at four
    double top = radians * radians; //x^2
    long denom = 2; //2!
    double value = previousValue - (top/denom);

    //iterate 7 iterations
    for (iterationCount;iterationCount <= 20;iterationCount+=2){ 
        previousValue = value;
        denom *= iterationCount * (iterationCount-1); //n * n-1 * (previous compued n-2!)
        top *= radians * radians; // x^2 * (previous computed x^n-2)
        multiply *= -1; //invert the sign
        //could be possibly faster to not use multiply but a conditional move?
        value = previousValue + (multiply*top/denom);
    }
    //checking for convergence provides neglieble speedup and a drop in accuracy.

}

/**
Find square root of the provided double
Currently not very fast -> needs setup
@param[in]  the number to square root

@retval result when input >0 otherwise returns input
**/
double
EFIAPI
sqrt_d(
  IN CONST double input
){
    Uint64 firstGuess = (long)input;
    int iters = 2;
    double x = 0;
    double prevX = -1;

    //if we get anything under 0 or is zero return what we got
    if (input <= 0) return input;

    //find a reasonable first approximation for faster convergence
    // sqrt(input) = sqrt(a) * 2^n roughly equals 2^n
    // We find the highest order bit and xor everything else
    Uint64 highestOrderBit = hibit(firstGuess) /2;
    //then we get the position of the highest or'd bit
    //we might need to use another function other than clzl since that relies on BSR
    //this should output a bsrl on x86 and polyfill it in on ARM64
    Uint64 highestOrderBitPosition = 64 - __builtin_clzl(highestOrderBit);
    
    //our first guess is then just 2 ^ (n/2)
    firstGuess = 1 << highestOrderBitPosition/2;

    //make sure our first guess is at least above zero
    if (firstGuess == 0) firstGuess = 1;

    //do a few iteration using Heron's method
    //https://en.wikipedia.org/wiki/Methods_of_computing_square_roots
    x = (double)firstGuess;

    //do 7 iterations
    //any further iterations yields no accuracy benefits
    //quadratic convergent so we get 4x the precision each iteration 
    for (int i=0;i<6 && x != 0 && prevX != x;i++){
        prevX = x;
        x = .5 * (prevX + (input/prevX));
    }

    return x;
}

/**
Find sine of a provided unsigned integer in degrees

@param[in]  angle to calculate in degrees

@retval the result * 100
**/
UINT32
EFIAPI
sin_u32(
  IN CONST UINT32 angleInDegrees
){
    return 0;
}


/**
Find cosine of a provided unsigned integer in degrees

@param[in]  angle to calculate in degrees

@retval the result * 100
**/
UINT32
EFIAPI
cos_u32(
  IN CONST UINT32 angleInDegrees
){
    return 0;
}

/**
Find square root of the provided unsigned integer

@param[in]  the number to square root

@retval result when input >0 otherwise returns input
**/
UINT32
EFIAPI
sqrt_u32(
  IN CONST UINT32 input
){
    UINT32 res = 0;
    UINT32 bit = 1 << 30; // The second-to-top bit is set: 1 << 30 for 32 bits
 
    // "bit" starts at the highest power of four <= the argument.
    while (bit > num)
        bit >>= 2;
        
    while (bit != 0) {
        //if num is more than result + bit
        if (num >= res + bit) {
            num -= res + bit;
            res += bit << 1;
        }
        
        res >>= 1;
        bit >>= 2;
    }
    return res;
}

/**
Find square root of the provided unsigned 64bit integer

@param[in]  the number to square root

@retval result when input >0 otherwise returns input
**/
UINT64
EFIAPI
sqrt_u64(
  IN CONST UINT32 input
){
    UINT64 res = 0;
    UINT64 bit = 1 << 62; // The second-to-top bit is set: 1 << 62 for 32 bits
 
    // "bit" starts at the highest power of four <= the argument.
    while (bit > num)
        bit >>= 2;
        
    while (bit != 0) {
        //if num is more than result + bit
        if (num >= res + bit) {
            num -= res + bit;
            res += bit << 1;
        }
        
        res >>= 1;
        bit >>= 2;
    }
    return res;
}

