/* Copyright (c) 2007, Christian Hujer
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

#ifndef ACEUNITLOGGING_H

#define ACEUNITLOGGING_H 1

#include "AceUnit.h"

#define ACEUNIT_LOGGING_STYLE_SIMPLE 1

#define ACEUNIT_LOGGING_STYLE_FULL 2

#ifndef ACEUNIT_LOGGING_STYLE

#ifdef ACEUNIT_EMBEDDED
#define ACEUNIT_LOGGING_STYLE ACEUNIT_LOGGING_STYLE_SIMPLE
#else
#define ACEUNIT_LOGGING_STYLE ACEUNIT_LOGGING_STYLE_FULL
#endif
#endif

#if ACEUNIT_LOGGING_STYLE == ACEUNIT_LOGGING_STYLE_FULL

#define ACEUNIT_LOG_RUNNER
#endif

#if ACEUNIT_LOGGING_STYLE == ACEUNIT_LOGGING_STYLE_FULL

#define ACEUNIT_LOG_SUITE
#endif

#if ACEUNIT_LOGGING_STYLE == ACEUNIT_LOGGING_STYLE_FULL

#define ACEUNIT_LOG_FIXTURE
#endif

#if ACEUNIT_LOGGING_STYLE == ACEUNIT_LOGGING_STYLE_FULL

#define ACEUNIT_LOG_TESTCASE
#endif

/* Note: Logging of failures cannot be turned off. */

typedef struct {

#ifdef ACEUNIT_LOG_RUNNER

    void(*runnerStarted)(void);
#endif

#ifdef ACEUNIT_LOG_SUITE

    void(*suiteStarted)(SuiteId_t const suiteId);
#endif

#ifdef ACEUNIT_LOG_FIXTURE

    void(*fixtureStarted)(const FixtureId_t fixture);
#endif

#ifdef ACEUNIT_LOG_TESTCASE

    void(*testCaseStarted)(TestCaseId_t testCase);
#endif

    void(*testCaseFailed)(const AssertionError_t *error);

#ifdef ACEUNIT_LOG_TESTCASE

    void(*testCaseEnded)(TestCaseId_t testCase);
#endif

#ifdef ACEUNIT_LOG_FIXTURE

    void(*fixtureEnded)(FixtureId_t fixture);
#endif

#ifdef ACEUNIT_LOG_SUITE

    void(*suiteEnded)(SuiteId_t const suiteId);
#endif

#ifdef ACEUNIT_LOG_RUNNER

    void(*runnerEnded)(void);
#endif

} TestLogger_t;

/* TODO if somebody knows a simplier way... */
#if   !defined(ACEUNIT_LOG_RUNNER) && !defined(ACEUNIT_LOG_SUITE) && !defined(ACEUNIT_LOG_FIXTURE) && !defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    testCaseFailed\
}
#elif !defined(ACEUNIT_LOG_RUNNER) && !defined(ACEUNIT_LOG_SUITE) && !defined(ACEUNIT_LOG_FIXTURE) &&  defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    testCaseStarted,\
    testCaseFailed,\
    testCaseEnded\
}
#elif !defined(ACEUNIT_LOG_RUNNER) && !defined(ACEUNIT_LOG_SUITE) &&  defined(ACEUNIT_LOG_FIXTURE) && !defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    fixtureStarted,\
    testCaseFailed,\
    fixtureEnded,\
}
#elif !defined(ACEUNIT_LOG_RUNNER) && !defined(ACEUNIT_LOG_SUITE) &&  defined(ACEUNIT_LOG_FIXTURE) &&  defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    fixtureStarted,\
    testCaseStarted,\
    testCaseFailed,\
    testCaseEnded,\
    fixtureEnded,\
}
#elif !defined(ACEUNIT_LOG_RUNNER) &&  defined(ACEUNIT_LOG_SUITE) && !defined(ACEUNIT_LOG_FIXTURE) && !defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    suiteStarted,\
    testCaseFailed,\
    suiteEnded,\
}
#elif !defined(ACEUNIT_LOG_RUNNER) &&  defined(ACEUNIT_LOG_SUITE) && !defined(ACEUNIT_LOG_FIXTURE) &&  defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    suiteStarted,\
    testCaseStarted,\
    testCaseFailed,\
    testCaseEnded,\
    suiteEnded\
}
#elif !defined(ACEUNIT_LOG_RUNNER) &&  defined(ACEUNIT_LOG_SUITE) &&  defined(ACEUNIT_LOG_FIXTURE) && !defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    suiteStarted,\
    fixtureStarted,\
    testCaseFailed,\
    fixtureEnded,\
    suiteEnded\
}
#elif !defined(ACEUNIT_LOG_RUNNER) &&  defined(ACEUNIT_LOG_SUITE) &&  defined(ACEUNIT_LOG_FIXTURE) &&  defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    suiteStarted,\
    fixtureStarted,\
    testCaseStarted,\
    testCaseFailed,\
    testCaseEnded,\
    fixtureEnded,\
    suiteEnded\
}
#elif  defined(ACEUNIT_LOG_RUNNER) && !defined(ACEUNIT_LOG_SUITE) && !defined(ACEUNIT_LOG_FIXTURE) && !defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    runnerStarted,\
    testCaseFailed,\
    runnerEnded\
}
#elif  defined(ACEUNIT_LOG_RUNNER) && !defined(ACEUNIT_LOG_SUITE) && !defined(ACEUNIT_LOG_FIXTURE) &&  defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    runnerStarted,\
    testCaseStarted,\
    testCaseFailed,\
    testCaseEnded,\
    runnerEnded\
}
#elif  defined(ACEUNIT_LOG_RUNNER) && !defined(ACEUNIT_LOG_SUITE) &&  defined(ACEUNIT_LOG_FIXTURE) && !defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    runnerStarted,\
    fixtureStarted,\
    testCaseFailed,\
    fixtureEnded,\
    runnerEnded\
}
#elif  defined(ACEUNIT_LOG_RUNNER) && !defined(ACEUNIT_LOG_SUITE) &&  defined(ACEUNIT_LOG_FIXTURE) &&  defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    runnerStarted,\
    fixtureStarted,\
    testCaseStarted,\
    testCaseFailed,\
    testCaseEnded,\
    fixtureEnded,\
    runnerEnded\
}
#elif  defined(ACEUNIT_LOG_RUNNER) &&  defined(ACEUNIT_LOG_SUITE) && !defined(ACEUNIT_LOG_FIXTURE) && !defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    runnerStarted,\
    suiteStarted,\
    testCaseFailed,\
    suiteEnded,\
    runnerEnded\
}
#elif  defined(ACEUNIT_LOG_RUNNER) &&  defined(ACEUNIT_LOG_SUITE) && !defined(ACEUNIT_LOG_FIXTURE) &&  defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    runnerStarted,\
    suiteStarted,\
    testCaseStarted,\
    testCaseFailed,\
    testCaseEnded,\
    suiteEnded,\
    runnerEnded\
}
#elif  defined(ACEUNIT_LOG_RUNNER) &&  defined(ACEUNIT_LOG_SUITE) &&  defined(ACEUNIT_LOG_FIXTURE) && !defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    runnerStarted,\
    suiteStarted,\
    fixtureStarted,\
    testCaseFailed,\
    fixtureEnded,\
    suiteEnded,\
    runnerEnded\
}
#elif  defined(ACEUNIT_LOG_RUNNER) &&  defined(ACEUNIT_LOG_SUITE) &&  defined(ACEUNIT_LOG_FIXTURE) &&  defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    runnerStarted,\
    suiteStarted,\
    fixtureStarted,\
    testCaseStarted,\
    testCaseFailed,\
    testCaseEnded,\
    fixtureEnded,\
    suiteEnded,\
    runnerEnded\
}
#else
#error Internal error, missing log combination.
#endif

#endif /* ACEUNITLOGGING_H */
