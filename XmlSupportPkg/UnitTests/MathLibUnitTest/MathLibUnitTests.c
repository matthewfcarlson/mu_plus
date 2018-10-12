/**
Unit-tests UEFI shell app for XmlTreeQueryLib.


Copyright (c) 2017, Microsoft Corporation

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
#include "MathLibUnitTests.h"



/**
Test Node count function on known count
**/
UNIT_TEST_STATUS
EFIAPI
TestSine(
  IN UNIT_TEST_FRAMEWORK_HANDLE  Framework,
  IN UNIT_TEST_CONTEXT           Context
)
{
  UINTN Index = 0;
  double current;
  MathLibContext *MathContext = (MathLibContext*)Context;  
  double result;
  double totalErrorSquared = 0;
  double maxError = 0;
  double totalAllowedError = MathContext.maxTotalError;
  double maxAllowedError = MathContext.maxError;

  double error = 0;


  for (current= MathContext.start;current < MathLibContext.stop; current+= MathContext.step){
    result = sin_d(current);
    error = result - MathContext.data[Index];
    error *= error;
    totalErrorSquared += error;
    if (error > maxError) maxError = error;
    UT_ASSERT_TRUE(maxError < maxAllowedError);
    Index++;
  }

  UT_ASSERT_TRUE(totalErrorSquared < totalAllowedError);

  return UNIT_TEST_PASSED;
}

//----------------------------------------------------
// UEFI main
//----------------------------------------------------
EFI_STATUS
EFIAPI
UefiMain(
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE* SystemTable)
{
  EFI_STATUS                Status;
  UNIT_TEST_FRAMEWORK       *Fw = NULL;
  UNIT_TEST_SUITE           *TestSuite;
  CHAR16  ShortName[100];
  ShortName[0] = L'\0';

  UnicodeSPrint(&ShortName[0], sizeof(ShortName), L"%a", gEfiCallerBaseName); 
    DEBUG((DEBUG_INFO, "%s v%s\n", UNIT_TEST_APP_NAME, UNIT_TEST_APP_VERSION));

  //
  // Start setting up the test framework for running the tests.
  //
  Status = InitUnitTestFramework(&Fw, UNIT_TEST_APP_NAME, ShortName, UNIT_TEST_APP_VERSION);
  if (EFI_ERROR(Status))
  {
    DEBUG((DEBUG_ERROR, "Failed in InitUnitTestFramework. Status = %r\n", Status));
    goto EXIT;
  }

  Status = CreateUnitTestSuite(&TestSuite, Fw, L"Math Lib Test Suite ", L"Common.MathLib", NULL, NULL);
  if (EFI_ERROR(Status))
  {
    DEBUG((DEBUG_ERROR, "Failed in CreateUnitTestSuite for Math Lib Test Suite %r\n", Status));
    Status = EFI_OUT_OF_RESOURCES;
    goto EXIT;
  }

  AddTestCase(TestSuite, L"Check Sine is within a reasonable error", L"Common.MathLib.Sine", TestSine, NULL, NULL, &SIN_CONTEXT);

  AddTestCase(TestSuite, L"Check cosine is within a reasonable error", L"Common.MathLib.Cos", TestCos, NULL, NULL, &COS_CONTEXT);

  AddTestCase(TestSuite, L"Check sqrt is within a reasonable error", L"Common.MathLib.Sqrt", TestSqrt, NULL, NULL, &SQRT_CONTEXT);
  
  //Run Tests
  Status = RunAllTestSuites(Fw);

  
 
EXIT:
  //Clean up Node Tree for query
  if (mNode != NULL)
  {
    FreeXmlTree(&mNode);
  }

  if (Fw != NULL)
  {
    FreeUnitTestFramework(Fw);
  }

  return Status;
}