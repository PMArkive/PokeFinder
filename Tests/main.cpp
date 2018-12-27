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

#include <Tests/RNG/LCRNGTest.hpp>
#include <Tests/RNG/LCRNG64Test.hpp>
#include <Tests/RNG/MTRNGTest.hpp>
#include <Tests/RNG/RNGCacheTest.hpp>
#include <Tests/RNG/RNGEuclideanTest.hpp>
#include <Tests/RNG/SFMTTest.hpp>
#include <Tests/RNG/TinyMTTest.hpp>

#include <QDebug>

int main()
{
    int failCount;
    auto runTest = [ &failCount ](QObject * test)
    {
        failCount += QTest::qExec(test);
    };

    LCRNGTest lcrngTest;
    LCRNG64Test lcrng64Test;
    MTRNGTest mtrngTest;
    RNGCacheTest rngcacheTest;
    RNGEuclideanTest rngeuclideanTest;
    SFMTTest sfmtTest;
    TinyMTTest tinymtTest;

    runTest(&lcrngTest);
    runTest(&lcrng64Test);
    runTest(&mtrngTest);
    runTest(&rngcacheTest);
    runTest(&rngeuclideanTest);
    runTest(&sfmtTest);
    runTest(&tinymtTest);

    qDebug() << "Failed tests: " + QString::number(failCount);
    return failCount;
}
