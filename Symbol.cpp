/*
 * Symbol.cpp - Builtin Symbols.
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
 *  $Id$
 */

#include "Object.h"
#include "Object-inl.h"
#include "Symbol.h"
using namespace scheme;

Symbols Symbol::symbols;
Object Symbol::QUOTE;
Object Symbol::QUASIQUOTE;
Object Symbol::UNQUOTE;
Object Symbol::UNQUOTE_SPLICING;
Object Symbol::AFTER;
Object Symbol::BEFORE;
Object Symbol::TOP_LEVEL;
Object Symbol::SYNTAX;
Object Symbol::QUASISYNTAX;
Object Symbol::UNSYNTAX;
Object Symbol::UNSYNTAX_SPLICING;


void Symbol::initBuitinSymbols()
{
    QUOTE             = Symbol::intern(UC("quote"));
    QUASIQUOTE        = Symbol::intern(UC("quasiquote"));
    UNQUOTE           = Symbol::intern(UC("unquote"));
    UNQUOTE_SPLICING  = Symbol::intern(UC("unquote-splicing"));
    AFTER             = Symbol::intern(UC("after"));
    BEFORE            = Symbol::intern(UC("before"));
    TOP_LEVEL         = Symbol::intern(UC("top level "));
    SYNTAX            = Symbol::intern(UC("syntax"));
    QUASISYNTAX       = Symbol::intern(UC("quasisyntax"));
    UNSYNTAX          = Symbol::intern(UC("unsyntax"));
    UNSYNTAX_SPLICING = Symbol::intern(UC("unsyntax-splicing"));
}
