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

#include "MTRNGTest.hpp"

void MTRNGTest::advanceFrames_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u32>("frames");
    QTest::addColumn<u32>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)1 << (u32)0x8C7F0AAC;
    QTest::newRow("Test 2") << (u32)0x00000000 << (u32)100 << (u32)0x53364B8C;
}

void MTRNGTest::advanceFrames()
{
    QFETCH(u32, seed);
    QFETCH(u32, frames);
    QFETCH(u32, result);

    MersenneTwister mt(seed);
    mt.advanceFrames(frames - 1);
    QCOMPARE(mt.nextUInt(), result);
}

void MTRNGTest::nextUInt_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u32>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)0x8C7F0AAC;
    QTest::newRow("Test 2") << (u32)0x12345678 << (u32)0xC6979343;
}

void MTRNGTest::nextUInt()
{
    QFETCH(u32, seed);
    QFETCH(u32, result);

    MersenneTwister mt(seed);
    QCOMPARE(mt.nextUInt(), result);
}

void MTRNGTest::nextUShort_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u16>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u16)0x8C7F;
    QTest::newRow("Test 2") << (u32)0x12345678 << (u16)0xC697;
}

void MTRNGTest::nextUShort()
{
    QFETCH(u32, seed);
    QFETCH(u16, result);

    MersenneTwister mt(seed);
    QCOMPARE(mt.nextUShort(), result);
}

void MTRNGTest::setSeed_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u32>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)0x00000000;
    QTest::newRow("Test 2") << (u32)0x12345678 << (u32)0x12345678;
}

void MTRNGTest::setSeed()
{
    QFETCH(u32, seed);
    QFETCH(u32, result);

    MersenneTwister mt(0);
    mt.setSeed(seed);
    QCOMPARE(mt.getSeed(), result);
}

void MTRNGTest::getSeed_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u32>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)0x00000000;
    QTest::newRow("Test 2") << (u32)0x12345678 << (u32)0x12345678;
}

void MTRNGTest::getSeed()
{
    QFETCH(u32, seed);
    QFETCH(u32, result);

    MersenneTwister mt(seed);
    QCOMPARE(mt.getSeed(), result);
}


void MTRNGTest::advanceFramesUntempered_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u32>("frames");
    QTest::addColumn<u32>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)1 << (u32)0x91A10D12;
    QTest::newRow("Test 2") << (u32)0x00000000 << (u32)100 << (u32)0xE1A62B04;
}

void MTRNGTest::advanceFramesUntempered()
{
    QFETCH(u32, seed);
    QFETCH(u32, frames);
    QFETCH(u32, result);

    MersenneTwisterUntempered mt(seed);
    mt.advanceFrames(frames - 1);
    QCOMPARE(mt.nextUInt(), result);
}

void MTRNGTest::nextUIntUntempered_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u32>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)0x91A10D12;
    QTest::newRow("Test 2") << (u32)0x12345678 << (u32)0x9BEE8D37;
}

void MTRNGTest::nextUIntUntempered()
{
    QFETCH(u32, seed);
    QFETCH(u32, result);

    MersenneTwisterUntempered mt(seed);
    QCOMPARE(mt.nextUInt(), result);
}

void MTRNGTest::nextUShortUntempered_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u16>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u16)0x91A1;
    QTest::newRow("Test 2") << (u32)0x12345678 << (u16)0x9BEE;
}

void MTRNGTest::nextUShortUntempered()
{
    QFETCH(u32, seed);
    QFETCH(u16, result);

    MersenneTwisterUntempered mt(seed);
    QCOMPARE(mt.nextUShort(), result);
}

void MTRNGTest::setSeedUntempered_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u32>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)0x00000000;
    QTest::newRow("Test 2") << (u32)0x12345678 << (u32)0x12345678;
}

void MTRNGTest::setSeedUntempered()
{
    QFETCH(u32, seed);
    QFETCH(u32, result);

    MersenneTwisterUntempered mt(0);
    mt.setSeed(seed);
    QCOMPARE(mt.getSeed(), result);
}

void MTRNGTest::getSeedUntempered_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u32>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)0x00000000;
    QTest::newRow("Test 2") << (u32)0x12345678 << (u32)0x12345678;
}

void MTRNGTest::getSeedUntempered()
{
    QFETCH(u32, seed);
    QFETCH(u32, result);

    MersenneTwisterUntempered mt(seed);
    QCOMPARE(mt.getSeed(), result);
}


void MTRNGTest::advanceFramesFast_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u32>("frames");
    QTest::addColumn<u32>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)1 << (u32)0x8CBF29B3;
    QTest::newRow("Test 2") << (u32)0x00000000 << (u32)100 << (u32)0x53B65F41;
}

void MTRNGTest::advanceFramesFast()
{
    QFETCH(u32, seed);
    QFETCH(u32, frames);
    QFETCH(u32, result);

    MersenneTwisterFast mt(seed, 227);
    mt.advanceFrames(frames - 1);
    QCOMPARE(mt.nextUInt(), result);
}

void MTRNGTest::nextUIntFast_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u32>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)0x8CBF29B3;
    QTest::newRow("Test 2") << (u32)0x12345678 << (u32)0xC6D5A2E6;
}

void MTRNGTest::nextUIntFast()
{
    QFETCH(u32, seed);
    QFETCH(u32, result);

    MersenneTwisterFast mt(seed, 227);
    QCOMPARE(mt.nextUInt(), result);
}

void MTRNGTest::nextUShortFast_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u16>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u16)0x8CBF;
    QTest::newRow("Test 2") << (u32)0x12345678 << (u16)0xC6D5;
}

void MTRNGTest::nextUShortFast()
{
    QFETCH(u32, seed);
    QFETCH(u16, result);

    MersenneTwisterFast mt(seed, 227);
    QCOMPARE(mt.nextUShort(), result);
}

void MTRNGTest::setSeedFast_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u32>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)0x00000000;
    QTest::newRow("Test 2") << (u32)0x12345678 << (u32)0x12345678;
}

void MTRNGTest::setSeedFast()
{
    QFETCH(u32, seed);
    QFETCH(u32, result);

    MersenneTwisterFast mt(0, 227);
    mt.setSeed(seed);
    QCOMPARE(mt.getSeed(), result);
}

void MTRNGTest::getSeedFast_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u32>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)0x00000000;
    QTest::newRow("Test 2") << (u32)0x12345678 << (u32)0x12345678;
}

void MTRNGTest::getSeedFast()
{
    QFETCH(u32, seed);
    QFETCH(u32, result);

    MersenneTwisterFast mt(seed, 227);
    QCOMPARE(mt.getSeed(), result);
}
