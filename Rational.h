/*
 * Rational.h -
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
 *  $Id: Rational.h 261 2008-07-25 06:16:44Z higepon $
 */

#ifndef __SCHEME_RATIONAL__
#define __SCHEME_RATIONAL__

#include "scheme.h"

namespace scheme {

class Rational EXTEND_GC
{
public:
    Rational(int numerator, int denominator);
    Rational(mpq_t r);
    ~Rational();

    char* toString();
    double toDouble() const;
    bool equal(int number);
    bool equal(Rational* number);

    static Rational* fromFixnum(int num);
    static Object add(Rational* number1, Rational* number2);
    static Object sub(Rational* number1, Rational* number2);
    static Object mul(Rational* number1, Rational* number2);
    static Object div(Rational* number1, Rational* number2);
    static bool gt(Rational* number1, Rational* number2);
    static bool ge(Rational* number1, Rational* number2);
    static bool lt(Rational* number1, Rational* number2);
    static bool le(Rational* number1, Rational* number2);

    mpq_t r;
};

}; // namespace scheme

#endif // __SCHEME_RATIONAL__
