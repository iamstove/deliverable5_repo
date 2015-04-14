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

#include <setjmp.h>
#include <string.h>

extern jmp_buf *currentExceptionBuffer;

#define try \
    do { \
        int exception; \
        jmp_buf lbuf; \
        jmp_buf *prev = currentExceptionBuffer; \
        currentExceptionBuffer = &lbuf; \
        switch (exception = setjmp(lbuf)) { \
        case 0: do \

#define catch(X) \
            while (false); \
            break; \
        case (X): exception = 0; do \


#define catchAll() \
            while (false); \
            break; \
        default: exception = 0; do \


#define endtry \
            while (false); \
        } \
        currentExceptionBuffer = prev; \
        if (exception) { \
            longjmp(*currentExceptionBuffer, exception); \
        } \
    } while(0)

#define throw(X) \
    do { \
        longjmp(*currentExceptionBuffer, (X)); \
    } while (false)

#define rethrow() \
    throw(exception)

#define throws(X)