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

#include "TinyMTTest.hpp"

void TinyMTTest::advanceFrames_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u32>("frames");
    QTest::addColumn<u32>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)1 << (u32)0x7C159927;
    QTest::newRow("Test 2") << (u32)0x00000000 << (u32)100 << (u32)0xED0BFAF9;
}

void TinyMTTest::advanceFrames()
{
    QFETCH(u32, seed);
    QFETCH(u32, frames);
    QFETCH(u32, result);

    TinyMT tiny(seed);
    tiny.advanceFrames(frames - 1);
    QCOMPARE(tiny.nextUInt(), result);
}

void TinyMTTest::nextUInt_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u32>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)0x7C159927;
    QTest::newRow("Test 2") << (u32)0x12345678 << (u32)0x93E35314;
}

void TinyMTTest::nextUInt()
{
    QFETCH(u32, seed);
    QFETCH(u32, result);

    TinyMT tiny(seed);
    QCOMPARE(tiny.nextUInt(), result);
}

void TinyMTTest::nextUShort_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u16>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u16)0x7C15;
    QTest::newRow("Test 2") << (u32)0x12345678 << (u16)0x93E3;
}

void TinyMTTest::nextUShort()
{
    QFETCH(u32, seed);
    QFETCH(u16, result);

    TinyMT tiny(seed);
    QCOMPARE(tiny.nextUShort(), result);
}

void TinyMTTest::setSeed_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u32>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)0x00000000;
    QTest::newRow("Test 2") << (u32)0x12345678 << (u32)0x12345678;
}

void TinyMTTest::setSeed()
{
    QFETCH(u32, seed);
    QFETCH(u32, result);

    TinyMT tiny((u32)0);
    tiny.setSeed(seed);
    QCOMPARE(tiny.getSeed(), result);
}

void TinyMTTest::getSeed_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<u32>("result");

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)0x00000000;
    QTest::newRow("Test 2") << (u32)0x12345678 << (u32)0x12345678;
}

void TinyMTTest::getSeed()
{
    QFETCH(u32, seed);
    QFETCH(u32, result);

    TinyMT tiny(seed);
    QCOMPARE(tiny.getSeed(), result);
}

void TinyMTTest::getState_data()
{
    QTest::addColumn<u32>("seed");
    QTest::addColumn<QVector<u32>>("result");

    QVector<u32> test1 = { 0x78A495AE, 0x60127F96, 0x0D6F15E9, 0x1969DE6C };
    QVector<u32> test2 = { 0x30814D70, 0xE940D010, 0xE0FA3141, 0x21F8CF22 };

    QTest::newRow("Test 1") << (u32)0x00000000 << test1;
    QTest::newRow("Test 2") << (u32)0x12345678 << test2;
}

void TinyMTTest::getState()
{
    QFETCH(u32, seed);
    QFETCH(QVector<u32>, result);

    TinyMT tiny(seed);
    u32 *states = tiny.getState();
    for (u8 i = 0; i < 4; i++)
    {
        QCOMPARE(states[i], result[i]);
    }
}
