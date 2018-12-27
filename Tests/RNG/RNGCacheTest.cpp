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

#include "RNGCacheTest.hpp"

void RNGCacheTest::recoverLower16BitsIV_data()
{
    QTest::addColumn<u32>("first");
    QTest::addColumn<u32>("second");
    QTest::addColumn<u32>("method");
    QTest::addColumn<QVector<u32>>("result");

    QVector<u32> test1 = { 0x00000000, 0x000067D3, 0x0000C907 };
    QVector<u32> test2 = { 0x7FFF305A, 0x7FFF982D, 0x7FFFF961 };
    QVector<u32> test3 = { 0x7C1FF9B6 };

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)0x00000000 << (u32)Method::Method1 << test1;
    QTest::newRow("Test 2") << (u32)0x7FFF0000 << (u32)0x7FFF0000 << (u32)Method::Method2 << test2;
    QTest::newRow("Test 3") << (u32)0x7C1F0000 << (u32)0x7FFF0000 << (u32)Method::Method4 << test3;
}

void RNGCacheTest::recoverLower16BitsIV()
{
    QFETCH(u32, first);
    QFETCH(u32, second);
    QFETCH(u32, method);
    QFETCH(QVector<u32>, result);

    RNGCache cache(static_cast<Method>(method));
    QVector<u32> data = cache.recoverLower16BitsIV(first, second);

    QCOMPARE(data.size(), result.size());
    for (int i = 0; i < data.size(); i++)
    {
        QCOMPARE(data[i], result[i]);
    }
}

void RNGCacheTest::recoverLower16BitsPID_data()
{
    QTest::addColumn<u32>("first");
    QTest::addColumn<u32>("second");
    QTest::addColumn<QVector<u32>>("result");

    QVector<u32> test1 = { 0x00000000, 0x000067D3 };
    QVector<u32> test2 = { 0x56788560, 0x5678ED33 };
    QVector<u32> test3 = { 0xBEEF3CB8, 0xBEEFA48B };

    // For PID all methods generate the same PID
    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)0x00000000 << test1;
    QTest::newRow("Test 2") << (u32)0x56780000 << (u32)0x12340000 << test2;
    QTest::newRow("Test 3") << (u32)0xBEEF0000 << (u32)0xDEAD0000 << test3;
}

void RNGCacheTest::recoverLower16BitsPID()
{
    QFETCH(u32, first);
    QFETCH(u32, second);
    QFETCH(QVector<u32>, result);

    RNGCache cache(Method::Method1);
    QVector<u32> data = cache.recoverLower16BitsPID(first, second);

    QCOMPARE(data.size(), result.size());
    for (int i = 0; i < data.size(); i++)
    {
        QCOMPARE(data[i], result[i]);
    }
}
