/*
 * This file is part of PokéFinder
 * Copyright (C) 2017 by Admiral_Fish, bumba, and EzPzStreamz
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "RNGEuclidean.hpp"

#define ADD 0x269EC3
#define MULT 0x343FD

// See https://crypto.stackexchange.com/a/10629 for how the following math works
// Uses Euclidean divison to reduce the search space (kmax) even further then RNGCache
// Only beneficial for smaller multipliers such as XDRNG

RNGEuclidean::RNGEuclidean(Method FrameType)
{
    setupEuclidean(FrameType);
}

// Recovers origin seeds for two 16 bit calls(15 bits known)
QVector<QPair<u32, u32>> RNGEuclidean::recoverLower16BitsIV(u32 first, u32 second) const
{
    QVector<QPair<u32, u32>> origin;
    u32 fullFirst, fullSecond;

    u64 t = static_cast<u32>(((second - sub1 * first) - sub2));
    u32 kmax = static_cast<u32>((base - t) >> 31);

    for (u32 k = 0; k <= kmax; k++, t += 0x80000000)
    {
        if ((t % sub1) < 0x10000)
        {
            fullFirst = first | static_cast<u32>((t / sub1));
            fullSecond = fullFirst * MULT + ADD;
            origin.append(QPair<u32, u32>(fullFirst, fullSecond));
        }
    }
    return origin;
}

// Recovers origin seeds for two 16 bit calls
QVector<QPair<u32, u32>> RNGEuclidean::recoverLower16BitsPID(u32 first, u32 second) const
{
    QVector<QPair<u32, u32>> origin;
    u32 fullFirst, fullSecond;

    u64 t = static_cast<u32>(((second - sub1 * first) - sub2));
    u32 kmax = static_cast<u32>((base - t) >> 32);

    for (u32 k = 0; k <= kmax; k++, t += 0x100000000)
    {
        if ((t % sub1) < 0x10000)
        {
            fullFirst = first | static_cast<u32>(t / sub1);
            fullSecond = fullFirst * MULT + ADD;
            origin.append(QPair<u32, u32>(fullFirst, fullSecond));
        }
    }
    return origin;
}

// Recovers origin seeds for six 5 bit calls
QVector<u32> RNGEuclidean::recoverLower27BitsChannel(u32 hp, u32 atk, u32 def, u32 spa, u32 spd, u32 spe) const
{
    QVector<u32> origin;
    u32 first = hp << 27, fullFirst;

    u64 t = static_cast<u32>((((spd << 27) - sub1 * first) - sub2));
    u32 kmax = static_cast<u32>((base - t) >> 32);

    for (u32 k = 0; k <= kmax; k++, t += 0x100000000)
    {
        if ((t % sub1) >= 0x8000000)
        {
            continue;
        }

        fullFirst = first | static_cast<u32>((t / sub1));
        // Check if the next 4 IVs lineup
        // The euclidean divisor assures the first and last call match up
        // so there is no need to check if the last call lines up
        u32 call = fullFirst * MULT + ADD;
        if ((call >> 27) != atk)
        {
            continue;
        }

        call = call * MULT + ADD;
        if ((call >> 27) != def)
        {
            continue;
        }

        call = call * MULT + ADD;
        if ((call >> 27) != spe)
        {
            continue;
        }

        call = call * MULT + ADD;
        if ((call >> 27) != spa)
        {
            continue;
        }

        origin.append(fullFirst);
    }
    return origin;
}

void RNGEuclidean::switchEuclidean(Method frameType)
{
    setupEuclidean(frameType);
}

void RNGEuclidean::setupEuclidean(Method frameType)
{
    if (frameType == Method::Channel)
    {
        // Channel is a unique situation having 6 rng calls with each call 5 bits known
        // It is unable to use the cache method and uses a modified Euclidean approach to keep kmax as low as possible
        // Using the first and last calls we can produce a modified adder and multiplier
        // Mult:j = Mult^j
        // Add:j = Add * (1 + Mult + ... + Mult^(j-1))
        // Using j = 5 and XDRNG gives Mult = 0x284A930D and Add = 0xa2974c77
        sub1 = 0x284A930D; // Modified mult
        sub2 = 0x9A974C78; // (-)Modified add + 0x8000000 - 1
        base = 0x142549847b56cf2; // 0x7ffffff * (Modified mult + 1)
    }
    // XDColo, XD, Colo
    else
    {
        sub1 = 0x343fd; // XDRNG mult
        sub2 = 0x259ec4; // (-)XDRNG add + 0x10000 - 1
        base = 0x343fabc02; // 0xffff * (XDRNG mult + 1)
    }
}
