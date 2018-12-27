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

#include "LCRNGTest.hpp"

void LCRNGTest::advanceFrames_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u32>("frames");
    QTest::addColumn<u32>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)1 << (u32)0x00006073;
    QTest::newRow("Test 2") << (u32)0x00000000 << (u32)100 << (u32)0x451BDE44;
}

void LCRNGTest::advanceFrames()
{
    QFETCH(u32, seed);
    QFETCH(u32, frames);
    QFETCH(u32, result);

    PokeRNG rng(seed);
    rng.advanceFrames(frames);
    QCOMPARE(rng.getSeed(), result);
}

void LCRNGTest::nextUShort_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u16>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u16)0x0000;
    QTest::newRow("Test 2") << (u32)0x12345678 << (u16)0x0B71;
}

void LCRNGTest::nextUShort()
{
    QFETCH(u32, seed);
    QFETCH(u16, result);

    PokeRNG rng(seed);
    QCOMPARE(rng.nextUShort(), result);
}

void LCRNGTest::nextUInt_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u32>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)0x00006073;
    QTest::newRow("Test 2") << (u32)0x12345678 << (u32)0x0B71C18B;
}

void LCRNGTest::nextUInt()
{
    QFETCH(u32, seed);
    QFETCH(u32, result);

    PokeRNG rng(seed);
    QCOMPARE(rng.nextUInt(), result);
}

void LCRNGTest::setSeed_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u32>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)0x00000000;
    QTest::newRow("Test 2") << (u32)0x12345678 << (u32)0x12345678;
}

void LCRNGTest::setSeed()
{
    QFETCH(u32, seed);
    QFETCH(u32, result);

    PokeRNG rng(0);
    rng.setSeed(seed);
    QCOMPARE(rng.getSeed(), result);
}

void LCRNGTest::getSeed_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u32>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)0x00000000;
    QTest::newRow("Test 2") << (u32)0x12345678 << (u32)0x12345678;
}

void LCRNGTest::getSeed()
{
    QFETCH(u32, seed);
    QFETCH(u32, result);

    PokeRNG rng(seed);
    QCOMPARE(rng.getSeed(), result);
}
