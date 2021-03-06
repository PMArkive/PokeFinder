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

#ifndef RNGCACHE_HPP
#define RNGCACHE_HPP

#include <QHash>
#include <QVector>
#include <Core/Objects/Global.hpp>
#include <Core/Objects/Method.hpp>

class RNGCache
{

public:
    RNGCache() = default;
    RNGCache(Method method);
    QVector<u32> recoverLower16BitsIV(u32 first, u32 second) const;
    QVector<u32> recoverLower16BitsPID(u32 first, u32 second) const;
    void switchCache(Method MethodType);

private:
    u32 add;
    u32 k;
    u32 mult;
    QHash<u16, u16> keys;

    void populateMap();
    void setupCache(Method method);

};

#endif // RNGCACHE_HPP
