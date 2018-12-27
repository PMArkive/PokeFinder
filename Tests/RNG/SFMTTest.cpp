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

#include "SFMTTest.hpp"

void SFMTTest::advanceFrames_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u32>("frames");
    QTest::addColumn<u64>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)1 << (u64)0x0FCF240A2E0CAA58;
    QTest::newRow("Test 2") << (u32)0x00000000 << (u32)100 << (u64)0x2DF55DBA2284262D;
}

void SFMTTest::advanceFrames()
{
    QFETCH(u32, seed);
    QFETCH(u32, frames);
    QFETCH(u64, result);

    SFMT sfmt(seed);
    sfmt.advanceFrames(frames - 1);
    QCOMPARE(sfmt.nextULong(), result);
}

void SFMTTest::nextUInt_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u32>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)0x2E0CAA58;
    QTest::newRow("Test 2") << (u32)0x12345678 << (u32)0xC6B57D1E;
}

void SFMTTest::nextUInt()
{
    QFETCH(u32, seed);
    QFETCH(u32, result);

    SFMT sfmt(seed);
    QCOMPARE(sfmt.nextUInt(), result);
}

void SFMTTest::nextULong_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u64>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u64)0x0FCF240A2E0CAA58;
    QTest::newRow("Test 2") << (u32)0x12345678 << (u64)0x43C4994AC6B57D1E;
}

void SFMTTest::nextULong()
{
    QFETCH(u32, seed);
    QFETCH(u64, result);

    SFMT sfmt(seed);
    QCOMPARE(sfmt.nextULong(), result);
}

void SFMTTest::setSeed_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u32>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)0x00000000;
    QTest::newRow("Test 2") << (u32)0x12345678 << (u32)0x12345678;
}

void SFMTTest::setSeed()
{
    QFETCH(u32, seed);
    QFETCH(u32, result);

    SFMT sfmt(0);
    sfmt.setSeed(seed);
    QCOMPARE(sfmt.getSeed(), result);
}

void SFMTTest::getSeed_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u32>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)0x00000000;
    QTest::newRow("Test 2") << (u32)0x12345678 << (u32)0x12345678;
}

void SFMTTest::getSeed()
{
    QFETCH(u32, seed);
    QFETCH(u32, result);

    SFMT sfmt(seed);
    QCOMPARE(sfmt.getSeed(), result);
}
