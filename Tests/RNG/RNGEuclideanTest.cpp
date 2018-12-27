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

#include "RNGEuclideanTest.hpp"

using QVectorPair = QVector<QPair<u32, u32>>;

void RNGEuclideanTest::recoverLower16BitsIV_data()
{
    QTest::addColumn<u32>("first");
    QTest::addColumn<u32>("second");
    QTest::addColumn<QVectorPair>("result");

    QVectorPair test1 = { QPair<u32, u32>(0x00004E59, 0x000057B8), QPair<u32, u32>(0x0000C3F0, 0x800012F3) };
    QVectorPair test2 = { QPair<u32, u32>(0x7FFF14C6, 0x7FFFF871), QPair<u32, u32>(0x7FFF8A5D, 0xFFFFB3AC), QPair<u32, u32>(0x7FFFFFF4, 0x7FFF6EE7) };
    QVectorPair test3 = { QPair<u32, u32>(0x7C1F3869, 0x7FFFD988), QPair<u32, u32>(0x7C1FAE00, 0xFFFF94C3) };

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)0x00000000 << test1;
    QTest::newRow("Test 2") << (u32)0x7FFF0000 << (u32)0x7FFF0000 << test2;
    QTest::newRow("Test 3") << (u32)0x7C1F0000 << (u32)0x7FFF0000 << test3;
}

void RNGEuclideanTest::recoverLower16BitsIV()
{
    QFETCH(u32, first);
    QFETCH(u32, second);
    QFETCH(QVectorPair, result);

    RNGEuclidean euclidean(Method::XDColo);
    QVectorPair data = euclidean.recoverLower16BitsIV(first, second);

    QCOMPARE(data.size(), result.size());
    for (int i = 0; i < data.size(); i++)
    {
        QCOMPARE(data[i], result[i]);
    }
}

void RNGEuclideanTest::recoverLower16BitsPID_data()
{
    QTest::addColumn<u32>("first");
    QTest::addColumn<u32>("second");
    QTest::addColumn<QVectorPair>("result");

    QVectorPair test1 = { QPair<u32, u32>(0x00004E59, 0x000057B8) };
    QVectorPair test2 = { QPair<u32, u32>(0x8765ECC3, 0x4321A47A) };
    QVectorPair test3 = { QPair<u32, u32>(0xBEEF7F2F, 0xDEAD9D36) };

    QTest::newRow("Test 1") << (u32)0x00000000 << (u32)0x00000000 << test1;
    QTest::newRow("Test 2") << (u32)0x87650000 << (u32)0x43210000 << test2;
    QTest::newRow("Test 3") << (u32)0xBEEF0000 << (u32)0xDEAD0000 << test3;
}

void RNGEuclideanTest::recoverLower16BitsPID()
{
    QFETCH(u32, first);
    QFETCH(u32, second);
    QFETCH(QVectorPair, result);

    RNGEuclidean euclidean(Method::XDColo);
    QVectorPair data = euclidean.recoverLower16BitsPID(first, second);

    QCOMPARE(data.size(), result.size());
    for (int i = 0; i < data.size(); i++)
    {
        QCOMPARE(data[i], result[i]);
    }
}

void RNGEuclideanTest::recoverLower27BitsChannel_data()
{
    QTest::addColumn<QVector<u8>>("ivs");
    QTest::addColumn<QVector<u32>>("result");

    QVector<u8> ivs1 = { 0, 0, 0, 0, 0, 0 };
    QVector<u8> ivs2 = { 31, 31, 31, 31, 31, 31 };
    QVector<u8> ivs3 = { 31, 0, 31, 31, 31, 31 };

    QVector<u32> test1 = { 0x0528C041 };
    QVector<u32> test2 = { 0xFBA5085C, 0xFBCB9DE0, 0xFD156C92, 0xFD3C0216 };
    QVector<u32> test3 = { 0xFC87A6C9, 0xFCAE3C4D, 0xFE9211B6 };

    QTest::newRow("Test 1") << ivs1 << test1;
    QTest::newRow("Test 2") << ivs2 << test2;
    QTest::newRow("Test 3") << ivs3 << test3;
}

void RNGEuclideanTest::recoverLower27BitsChannel()
{
    QFETCH(QVector<u8>, ivs);
    QFETCH(QVector<u32>, result);

    RNGEuclidean euclidean(Method::Channel);
    QVector<u32> data = euclidean.recoverLower27BitsChannel(ivs[0], ivs[1], ivs[2], ivs[3], ivs[4], ivs[5]);

    QCOMPARE(data.size(), result.size());
    for (int i = 0; i < data.size(); i++)
    {
        QCOMPARE(data[i], result[i]);
    }
}
