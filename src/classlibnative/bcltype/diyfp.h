// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.
//
// File: diyfp.h
//

//

#ifndef _DIYFP_H
#define _DIYFP_H

#include <clrtypes.h>

// An exteneded floating-point data structure which is required by Grisu3 algorithm.
// It defines a 64-bit significand and a 32-bit exponent,
// which is EXTENDED compare to IEEE double precision floating-point number (53 bits significand and 11 bits exponent).
//
// Original Grisu algorithm produces suboptimal results. To shorten the output (which is part of Grisu2/Grisu3's job),
// we need additional 11 bits of the significand f and larger exponent e (A larger exponent range is used to avoid overflow. A 32-bit exponent is far big enough).
// To fully understand how Grisu3 uses this data structure to get better result, please read http://www.cs.tufts.edu/~nr/cs257/archive/florian-loitsch/printf.pdf
class DiyFp
{
public:
    DiyFp()
        : m_f(0), m_e()
    {
    }

    DiyFp(UINT64 f, int e)
        : m_f(f), m_e(e)
    {
    }

    DiyFp(const DiyFp& rhs)
        : m_f(rhs.m_f), m_e(rhs.m_e)
    {
    }

    DiyFp& operator=(const DiyFp& rhs)
    {
        m_f = rhs.m_f;
        m_e = rhs.m_e;

        return *this;
    }

    UINT64 f() const
    {
        return m_f;
    }

    int e() const
    {
        return m_e;
    }

    void SetSignificand(UINT64 f)
    {
        m_f = f;
    }

    void SetExponent(int e)
    {
        m_e = e;
    }

    void Minus(const DiyFp& rhs);
    static void Minus(const DiyFp& left, const DiyFp& right, DiyFp& result);

    void Multiply(const DiyFp& rhs);
    static void Multiply(const DiyFp& left, const DiyFp& right, DiyFp& result);

    static void GenerateNormalizedDiyFp(double value, DiyFp& result);

public:
    static const int SIGNIFICAND_LENGTH = 64;

private:
    // Extended significand.
    // IEEE 754 double-precision numbers only require 53 bits significand.
    // However, in Grisu3 we need additional 11 bits so we declare m_f as UINT64.
    // Please note m_f does not include sign bit.
    UINT64 m_f;

    // Extended exponent.
    // IEEE 754 double-precision numbers only require 11 bits exponent.
    // However, in Grisu3 we need extra space to avoid overflow so we declare m_e as int.
    // Please note m_e is a biased exponent if the DiyFp instance is generated by GenerateNormalizedDiyFp().
    int m_e;
};

#endif