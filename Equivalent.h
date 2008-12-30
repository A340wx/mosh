/*
 * Equivalent.h - equivalent procedures.
 *
 *   Copyright (c) 2008  Higepon(Taro Minowa)  <higepon@users.sourceforge.jp>
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *   TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 *   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  $Id: Equivalent.h 261 2008-07-25 06:16:44Z higepon $
 */

#ifndef __SCHEME_EQUIVALENT__
#define __SCHEME_EQUIVALENT__

#include "Arithmetic.h"
#include "scheme.h"

namespace scheme {
    bool equal(VM* theVM, Object object1, Object object2, EqHashTable* visited);
    bool equal(VM* theVM, Object object1, Object object2);
    bool fastEqual(VM* theVM, Object object1, Object object2);

    inline bool eqv(VM* theVM, Object o1, Object o2)
    {
        if (o1.isRecord()) {
            if (o2.isRecord()) {
                Record* const record1 = o1.toRecord();
                Record* const record2 = o2.toRecord();
                return record1->rtd() == record2->rtd();
            } else {
                return false;
            }
        }

        if (o1.isNumber()) {
            if (o2.isNumber()) {
                return Arithmetic::eq(theVM, o1, o2);
            } else {
                return false;
            }
        }
        return o1.eq(o2);
    }

}; // namespace scheme

#endif // __SCHEME_EQUIVALENT__
