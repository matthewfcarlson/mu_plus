
/**
@file 
Define structure and test data for math lib.


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
#ifndef MATH_LIB_TEST_DATA_H
#define MATH_LIB_TEST_DATA_H

typedef struct {
  double start;
  double end;
  double step;  // the step
  const double* data; // the data to compare against
} MathLibContext;

const double SIN_START_POINT = -6;
const double SIN_STOP_POINT = 6;
const double SIN_STEP = 1;
const double SIN_DATA[] = {0.5,1.0};

MathLibContext SIN_CONTEXT = {SIN_START_POINT, SIN_STOP_POINT, SIN_STEP, SIN_DATA };


const double COS_START_POINT = -6;
const double COS_STOP_POINT = 6;
const double COS_STEP = 1;
const double COS_DATA[] = {0.5,1.0};

MathLibContext COS_CONTEXT = {COS_START_POINT, COS_STOP_POINT, COS_STEP, COS_DATA };


const double SQRT_START_POINT = -6;
const double SQRT_STOP_POINT = 6;
const double SQRT_STEP = 1;
const double SQRT_DATA[] = {0.5,1.0};

MathLibContext SQRT_CONTEXT = {SQRT_START_POINT, SQRT_STOP_POINT, SQRT_STEP, SQRT_DATA };


#endif