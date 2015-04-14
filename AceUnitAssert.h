/* Copyright (c) 2008, Christian Hujer
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

#ifndef ACEUNITASSERT_H

#define ACEUNITASSERT_H 1

#include "AceUnit.h"

#ifdef ACEUNIT_EXPLICIT_MESSAGES
#include <stdio.h> /* for snprintf(). */
#endif

#define fail(message) newAssertionError(message)

#define assertTrue(message, condition) do { if (!(condition)) { fail(message); } } while (false)

#define assertFalse(message, condition) do { if (condition) { fail(message); } } while (false)

#ifdef ACEUNIT_EXPLICIT_MESSAGES
#define assertEquals(message, expected, actual) \
    do { \
        int32_t lexpected = (expected); \
        int32_t lactual = (actual); \
        if (lexpected != lactual) { \
            snprintf(runnerData->explicitMsgBuf, ACEUNIT_EXPLICIT_MSG_BUF_SIZE, "%s (expected: %d, actual: %d)", message, lexpected, lactual); \
            fail(runnerData->explicitMsgBuf); \
        } \
    } while (false)
#else
#define assertEquals(message, expected, actual) do { if (!((expected) == (actual))) { fail(message); } } while (false)
#endif

#ifdef ACEUNIT_EXPLICIT_MESSAGES
#define assertNotEquals(message, unexpected, actual) \
    do { \
        int32_t lunexpected = unexpected; \
        int32_t lactual = actual; \
        if (lunexpected == lactual) { \
            snprintf(runnerData->explicitMsgBuf, ACEUNIT_EXPLICIT_MSG_BUF_SIZE, "%s (unexpected: %d, actual: %d)", message, lunexpected, lactual); \
            fail(runnerData->explicitMsgBuf); \
        } \
    } while (false)
#else
#define assertNotEquals(message, unexpected, actual) do { if ((unexpected) == (actual)) { fail(message); } } while (false)
#endif

#define assertNotNull(message, ptr) do { if (NULL == (ptr)) { fail(message); } } while (false)

#define assertNull(message, ptr) do { if (NULL != (ptr)) { fail(message); } } while (false)

#endif /* ACEUNITASSERT_H */