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

#ifndef ACEUNITANNOTATIONS_H

#define ACEUNITANNOTATIONS_H 1

#ifdef ACEUNIT_STATIC_ANNOTATIONS
#define ACEUNIT_ANNOTATION static
#else
#define ACEUNIT_ANNOTATION
#endif

#define ACEUNIT_DIRECT_ANNOTATION ACEUNIT_ANNOTATION

#define ACEUNIT_META_ANNOTATION ACEUNIT_ANNOTATION

#define A_Test             ACEUNIT_DIRECT_ANNOTATION

#define A_Loop(times)      ACEUNIT_META_ANNOTATION

#define A_Before           ACEUNIT_DIRECT_ANNOTATION

#define A_After            ACEUNIT_DIRECT_ANNOTATION

#define A_BeforeClass      ACEUNIT_DIRECT_ANNOTATION

#define A_AfterClass       ACEUNIT_DIRECT_ANNOTATION

#define A_Ignore           ACEUNIT_META_ANNOTATION

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L) && defined(ACEUNIT_C99)
#define A_Group(...)       ACEUNIT_META_ANNOTATION
#else
#define A_Group(group)
#endif

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L) && defined(ACEUNIT_C99)
#define A_FixtureGroup(...)
#else
#define A_FixtureGroup(group)
#endif

#endif /* ACEUNITANNOTATIONS_H */