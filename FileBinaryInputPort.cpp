/*
 * FileBinaryInputPort.cpp - None buffering <file-binary-input-port>
 *
 *   Copyright (c) 2009  Higepon(Taro Minowa)  <higepon@users.sourceforge.jp>
 *   Copyright (c) 2009  Kokosabu(MIURA Yasuyuki)  <kokosabu@gmail.com>
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

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h> // memcpy
#include "Object.h"
#include "Object-inl.h"
#include "HeapObject.h"
#include "SString.h"
#include "Pair.h"
#include "Pair-inl.h"
#include "ByteVector.h"
#include "FileBinaryInputPort.h"
#include "Bignum.h"
#include "Symbol.h"

using namespace scheme;

FileBinaryInputPort::FileBinaryInputPort(int fd) : fd_(fd), fileName_(UC("<unknown file>")), isClosed_(false), aheadU8_(EOF), position_(0)
{
}

FileBinaryInputPort::FileBinaryInputPort(ucs4string file) : fileName_(file), isClosed_(false), aheadU8_(EOF), position_(0)
{
    fd_ = ::open(file.ascii_c_str(), O_RDONLY);
}

FileBinaryInputPort::FileBinaryInputPort(const char* file) : isClosed_(false), aheadU8_(EOF), position_(0)
{
    fileName_ = Object::makeString(file).toString()->data();
    fd_ = ::open(file, O_RDONLY);
}

FileBinaryInputPort::~FileBinaryInputPort()
{
    close();
}

int FileBinaryInputPort::open()
{
    if (INVALID_FILENO == fd_) {
        return MOSH_FAILURE;
    } else {
        return MOSH_SUCCESS;
    }
}

ucs4string FileBinaryInputPort::toString()
{
    return fileName_;
}

int FileBinaryInputPort::getU8()
{
    if (hasAheadU8()) {
        const uint8_t c = aheadU8_;
        aheadU8_ = EOF;
        position_++;
        return c;
    }

    uint8_t c;
    const int result = readFromFile(&c, 1);
    if (0 == result) {
        position_++;
        return EOF;
    } else if (result > 0) {
        position_++;
        return c;
    } else {
        MOSH_FATAL("todo");
        // todo error check. we may have isErrorOccured flag.
        return c;
    }
}

int FileBinaryInputPort::lookaheadU8()
{
    if (hasAheadU8()) {
        return aheadU8_;
    }

    uint8_t c;
    const int result = readFromFile(&c, 1);
    if (0 == result) {
        return EOF;
    } else if (result > 0) {
        aheadU8_ = c;
        return c;
    } else {
        // todo error check. we may have isErrorOccured.
        MOSH_FATAL("todo");
        return c;
    }
}

ByteVector* FileBinaryInputPort::getByteVector(uint32_t size)
{
#ifdef USE_BOEHM_GC
    uint8_t* buf = new(PointerFreeGC) uint8_t[size];
#else
    uint8_t* buf = new uint8_t[size];
#endif
    int ret;
    if (hasAheadU8()) {
        buf[0] = aheadU8_;
        aheadU8_ = EOF;
        ret = readFromFile(buf + 1, size - 1);
    } else {
        ret = readFromFile(buf, size);
    }

    if (ret < 0) {
        MOSH_FATAL("todo");
        return NULL;
    } else {
        position_ += ret;
        return new ByteVector(ret, buf);
    }
}

bool FileBinaryInputPort::isClosed() const
{
    return isClosed_;
}

int FileBinaryInputPort::close()
{
    if (!isClosed() && fd_ != INVALID_FILENO) {
        isClosed_ = true;
        if (fd_ != fileno(stdin)) {
            ::close(fd_);
        }
    }
    return MOSH_SUCCESS;
}

int FileBinaryInputPort::fileNo() const
{
    return fd_;
}

// binary-ports should support position.
bool FileBinaryInputPort::hasPosition() const
{
    return true;
}

bool FileBinaryInputPort::hasSetPosition() const
{
    return true;
}

Object FileBinaryInputPort::position() const
{
    return Bignum::makeInteger(position_);
}

bool FileBinaryInputPort::setPosition(int position)
{
    const int ret = lseek(fd_, position, SEEK_SET);
    if (position == ret) {
        position_ =  position;
        return true;
    } else {
        return false;
    }
}

int FileBinaryInputPort::readFromFile(uint8_t* buf, size_t size)
{
    for (;;) {
        const int result = read(fd_, buf, size);
        if (result < 0 && errno == EINTR) {
            // read again
            errno = 0;
        } else {
            return result;
        }
    }
}

bool FileBinaryInputPort::hasAheadU8() const
{
    return aheadU8_ != EOF;
}
