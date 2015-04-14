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

#ifndef ACEUNITDATA_H

#define ACEUNITDATA_H 1

#include "AceUnit.h"

typedef struct {

    AssertionError_t *recentError;

    AssertionError_t recentErrorData;

    TestCaseId_t currentTestId;

    unsigned short testCaseCount;

    unsigned short testCaseFailureCount;

#if ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_LONGJMP

    jmp_buf jmpBuf;
#endif

#ifdef ACEUNIT_EXPLICIT_MESSAGES

#ifdef ACEUNIT_EXPLICIT_MESSAGES_INLINE_BUFFER
    char explicitMsgBuf[ACEUNIT_EXPLICIT_MSG_BUF_SIZE];
#else
    char *explicitMsgBuf;
#endif
#endif
#ifdef ACEUNIT_RUNNERDATA_EXTENSION
    /* Extension hook to add your own fields to AceUnitRunnerData_t. */
    ACEUNIT_RUNNERDATA_EXTENSION
#endif

} AceUnitRunnerData_t;

extern AceUnitRunnerData_t *runnerData;

#endif /* ACEUNITDATA_H */