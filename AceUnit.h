/* Copyright (c) 2007-2008, Christian Hujer
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of the AceUnit developers nor the
*       names of its contributors may be used to endorse or promote products
  *       derived from this software without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
  * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
  * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
  * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
  * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  */
 
 #ifndef ACEUNIT_H
 
 #define ACEUNIT_H 1
 
 #ifdef ACEUNIT_CONFIG_FILE
 #include ACEUNIT_CONFIG_FILE
 #endif
 
 /* Auto-definition of ACEUNIT_C_MODE if it is not defined. */
 #if !defined(ACEUNIT_C_MODE)
 #if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
 /* C99 or better environment: Default to using C99. */
 #define ACEUNIT_C_MODE ACEUNIT_C_MODE_C99_INCLUDES
 #else
 /* <C99: Use its own definitions. */
 #define ACEUNIT_C_MODE ACEUNIT_C_MODE_C89
 #endif
 #endif
 
 #define ACEUNIT_C_MODE_C99_INCLUDES 1
 
 #define ACEUNIT_C_MODE_C89 2
 
 #define ACEUNIT_C_MODE_PROPRIETARY 3
 
 #if ACEUNIT_C_MODE == ACEUNIT_C_MODE_C99_INCLUDES
 #include <stddef.h>
 #include <stdint.h>
 #include <stdbool.h>
 #elif ACEUNIT_C_MODE == ACEUNIT_C_MODE_C89
 #ifndef __int8_t_defined
 #define __int8_t_defined
 
 typedef signed char int8_t;
 typedef signed short int int16_t;
 typedef signed long int int32_t;
 typedef unsigned char uint8_t;
 typedef unsigned short int uint16_t;
 typedef unsigned long int uint32_t;
 #endif
 #ifndef _SIZE_T_DEFINED
 #ifndef _SIZE_T_DEFINED_
 
 typedef long unsigned int size_t;
 #endif
 #endif
 #ifndef __bool_true_false_are_defined
 
 #if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
 #define bool _Bool
 #else
 #define bool int
 #endif
 
 #define true 1
 
 #define false 0
 
 #define __bool_true_false_are_defined 1
 #endif
 #ifndef NULL
 
 #if defined(__cplusplus)
 #define NULL 0
 #else
 #define NULL ((void *) 0)
 #endif
 #endif
 #elif ACEUNIT_C_MODE == ACEUNIT_C_MODE_PROPRIETARY
 /* no definitions for proprietary mode */
 #else
 #error Unknown value for ACEUNIT_C_MODE
 #endif
 
 #include "AceUnitAnnotations.h"
 
 #define ACEUNIT_ASSERTION_STYLE_RETURN 1
 
 #define ACEUNIT_ASSERTION_STYLE_ASSERT 2
 
 #define ACEUNIT_ASSERTION_STYLE_ABORT 3
 
 #define ACEUNIT_ASSERTION_STYLE_LONGJMP 4
 
 #define ACEUNIT_ASSERTION_STYLE_CUSTOM 5
 
 #ifndef ACEUNIT_ASSERTION_STYLE
 
 #ifdef ACEUNIT_CUSTOM_ASSERT
 #define ACEUNIT_ASSERTION_STYLE ACEUNIT_ASSERTION_STYLE_CUSTOM
 #else
 #define ACEUNIT_ASSERTION_STYLE ACEUNIT_ASSERTION_STYLE_LONGJMP
 #endif
 #endif
 
 #if ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_CUSTOM
 #ifndef ACEUNIT_CUSTOM_ASSERT
 #error You MUST define ACEUNIT_CUSTOM_ASSERT when using ACEUNIT_ASSERTION_STYLE_CUSTOM.
 #endif
 #endif
 
 /* Abort style specific configuration. */
 #if ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_RETURN
     /* nothing special */
 #elif ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_ASSERT
     #include <assert.h>
 #elif ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_ABORT
     #include <stdlib.h>
 #elif ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_LONGJMP
     #ifdef ACEUNIT_SETJMP_INCLUDE
     #include ACEUNIT_SETJMP_INCLUDE
     #elif defined(ACEUNIT_SKIP_SETJMP_INCLUDE)
     #else
     #include <setjmp.h>
     #endif
 #elif ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_CUSTOM
     /* nothing special */
 #else
     #error Unknown value for ACEUNIT_ASSERTION_STYLE.
 #endif
 
 #if ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_RETURN
     #define ACEUNIT_ABORT return
 #elif ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_ASSERT
     #define ACEUNIT_ABORT assert(0)
 #elif ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_ABORT
     #define ACEUNIT_ABORT abort()
 #elif ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_LONGJMP
     #define ACEUNIT_ABORT longjmp(runnerData->jmpBuf, 1)
 #elif ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_CUSTOM
     #define ACEUNIT_ABORT ACEUNIT_CUSTOM_ASSERT
 #else
     #error Unexpected internal error.
 #endif
 
 typedef unsigned short int AceTestId_t;
 
 #define NO_TEST ((AceTestId_t) 0)
 
 #define ALL_TESTS ((AceTestId_t) -1)
 
 typedef unsigned short int AceGroupId_t;
 
 typedef AceTestId_t SuiteId_t;
 
 typedef SuiteId_t FixtureId_t;
 
 typedef AceTestId_t TestCaseId_t;
 
 #define TestCaseId_NULL 0
 
 #ifdef ACEUNIT_EMBEDDED
 typedef uint16_t linenumber_t;
 #else
 typedef int linenumber_t;
 #endif
 
 typedef struct {
 
     linenumber_t lineNumber;
 
 #ifndef ACEUNIT_EMBEDDED
 
     const char *message;
 #endif
 
 } AssertionId_t;
 
 #ifdef ACEUNIT_EMBEDDED
 #define newAssertionError(message) { AssertionId_t assertion = { __LINE__ }; recordError(A_FIXTURE_ID, assertion); } ACEUNIT_ABORT
 #else
 #define newAssertionError(message) { AssertionId_t assertion = { __LINE__, message }; recordError(A_FIXTURE_ID, assertion); } ACEUNIT_ABORT
 #endif
 
 typedef struct {
 
     FixtureId_t fixtureId;
 
     TestCaseId_t testId;
 
     AssertionId_t assertionId;
 
 } AssertionError_t;
 
 #include "AceUnitAssert.h"
 
 typedef void(*testMethod_t)(void);
 
 typedef struct TestSuite_tt {
 
     /* Implementation note: Take care that the beginning of TestSuite_t is identical to that of TestFixture_t! */
 
     SuiteId_t const id;
 
 #ifndef ACEUNIT_EMBEDDED
 
     const char *name;
 #endif
 
     const struct TestSuite_tt *const *const suites;
 
 } TestSuite_t;
 
 #ifdef ACEUNIT_LOOP
 
 typedef uint16_t aceunit_loop_t;
 #endif
 
 typedef struct {
 
     /* Implementation note: Take care that the beginning of TestFixture_t is identical to that of TestSuite_t! */
 
     FixtureId_t const id;
 
 #ifndef ACEUNIT_EMBEDDED
 
     const char *const name;
 #endif
 
 #ifdef ACEUNIT_SUITES
 
     const TestSuite_t *const *const suites;
 #endif
 
     const TestCaseId_t *const testIds;
 
 #ifndef ACEUNIT_EMBEDDED
 
     const char *const *const testNames;
 #endif
 
 #ifdef ACEUNIT_LOOP
 
     const aceunit_loop_t *const loops;
 #endif
 
 #ifdef ACEUNIT_GROUP
 
     const AceGroupId_t *const groups;
 #endif
 
     const testMethod_t *const testCase;
 
     const testMethod_t *const before;
 
     const testMethod_t *const after;
 
     const testMethod_t *const beforeClass;
 
     const testMethod_t *const afterClass;
 
 } TestFixture_t;
 
 extern void recordError(const FixtureId_t fixtureId, const AssertionId_t assertionId);
 
 #if defined(ACEUNIT_GROUP) || defined(_doxygen)
 extern void runFixture(const TestFixture_t *const fixture, AceGroupId_t group);
 #else
 extern void runFixture(const TestFixture_t *const fixture);
 #endif
 
 #if defined(ACEUNIT_GROUP) || defined(_doxygen)
 extern void runSuite(const TestSuite_t *const suite, AceGroupId_t group);
 #else
 extern void runSuite(const TestSuite_t *const suite);
 #endif
 
 #if ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_LONGJMP
 #include "AceUnitData.h"
 #endif
 
 #endif /* ACEUNIT_H */
