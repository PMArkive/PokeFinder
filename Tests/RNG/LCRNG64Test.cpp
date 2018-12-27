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

#include "LCRNG64Test.hpp"

void LCRNG64Test::advanceFrames_data()
{
    QTest::addColumn<u64>("seed");
    QTest::addColumn<u32>("frames");
    QTest::addColumn<u64>("result");

    QTest::newRow("Test 1") << (u64)0x0000000000000000 << (u32)1 << (u64)0x0000000000269EC3;
    QTest::newRow("Test 2") << (u64)0x0000000000000000 << (u32)100 << (u64)0xE7FE42E93C4FC074;
}

void LCRNG64Test::advanceFrames()
{
    QFETCH(u64, seed);
    QFETCH(u32, frames);
    QFETCH(u64, result);

    BWRNG rng(seed);
    rng.advanceFrames(frames);
    QCOMPARE(rng.getSeed(), result);
}

void LCRNG64Test::nextUInt_data()
{
    QTest::addColumn<u64>("seed");
    QTest::addColumn<u32>("result");

    QTest::newRow("Test 1") << (u64)0x0000000000000000 << (u32)0x00000000;
    QTest::newRow("Test 2") << (u64)0x0123456789ABCDEF << (u32)0x1DB90D64;
}

void LCRNG64Test::nextUInt()
{
    QFETCH(u64, seed);
    QFETCH(u32, result);

    BWRNG rng(seed);
    QCOMPARE(rng.nextUInt(), result);
}

void LCRNG64Test::nextULong_data()
{
    QTest::addColumn<u64>("seed");
    QTest::addColumn<u64>("result");

    QTest::newRow("Test 1") << (u64)0x0000000000000000 << (u64)0x0000000000269EC3;
    QTest::newRow("Test 2") << (u64)0x0123456789ABCDEF << (u64)0x1DB90D64B7ACC50E;
}

void LCRNG64Test::nextULong()
{
    QFETCH(u64, seed);
    QFETCH(u64, result);

    BWRNG rng(seed);
    QCOMPARE(rng.nextULong(), result);
}

void LCRNG64Test::setSeed_data()
{
    QTest::addColumn<u64>("seed");
    QTest::addColumn<u64>("result");

    QTest::newRow("Test 1") << (u64)0x0000000000000000 << (u64)0x0000000000000000;
    QTest::newRow("Test 2") << (u64)0x0123456789ABCDEF << (u64)0x0123456789ABCDEF;
}

void LCRNG64Test::setSeed()
{
    QFETCH(u64, seed);
    QFETCH(u64, result);

    BWRNG rng(0);
    rng.setSeed(seed);
    QCOMPARE(rng.getSeed(), result);
}

void LCRNG64Test::getSeed_data()
{
    QTest::addColumn<u64>("seed");
    QTest::addColumn<u64>("result");

    QTest::newRow("Test 1") << (u64)0x0000000000000000 << (u64)0x0000000000000000;
    QTest::newRow("Test 2") << (u64)0x0123456789ABCDEF << (u64)0x0123456789ABCDEF;
}

void LCRNG64Test::getSeed()
{
    QFETCH(u64, seed);
    QFETCH(u64, result);

    BWRNG rng(seed);
    QCOMPARE(rng.getSeed(), result);
}
