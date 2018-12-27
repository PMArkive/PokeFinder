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

#ifndef RNGEUCLIDEANTEST_HPP
#define RNGEUCLIDEANTEST_HPP

#include <QObject>
#include <QTest>
#include <Core/RNG/RNGEuclidean.hpp>

class RNGEuclideanTest : public QObject
{
    Q_OBJECT

private slots:
    void recoverLower16BitsIV_data();
    void recoverLower16BitsIV();

    void recoverLower16BitsPID_data();
    void recoverLower16BitsPID();

    void recoverLower27BitsChannel_data();
    void recoverLower27BitsChannel();

};

#endif // RNGEUCLIDEANTEST_HPP
