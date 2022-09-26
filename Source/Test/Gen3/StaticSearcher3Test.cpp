﻿/*
 * This file is part of PokéFinder
 * Copyright (C) 2017-2022 by Admiral_Fish, bumba, and EzPzStreamz
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

#include "StaticSearcher3Test.hpp"
#include <Core/Gen3/Encounters3.hpp>
#include <Core/Gen3/Generators/StaticGenerator3.hpp>
#include <Core/Gen3/Searchers/StaticSearcher3.hpp>
#include <Core/Gen3/States/State3.hpp>
#include <Core/Parents/StaticTemplate.hpp>
#include <QTest>
#include <Test/Data.hpp>

using IVs = std::array<u8, 6>;

static bool operator==(const SearcherState3 &left, const json &right)
{
    return left.getPID() == right["pid"].get<u32>() && left.getStats() == right["stats"].get<std::array<u16, 6>>()
        && left.getAbilityIndex() == right["abilityIndex"].get<u16>() && left.getIVs() == right["ivs"].get<std::array<u8, 6>>()
        && left.getAbility() == right["ability"].get<u8>() && left.getGender() == right["gender"].get<u8>()
        && left.getHiddenPower() == right["hiddenPower"].get<u8>() && left.getNature() == right["nature"].get<u8>()
        && left.getLevel() == right["level"].get<u8>() && left.getShiny() == right["shiny"].get<u8>()
        && left.getSeed() == right["seed"].get<u32>() && left.getHiddenPowerStrength() == right["hiddenPowerStrength"].get<u8>();
}

static bool operator==(const SearcherState3 &left, const GeneratorState3 &right)
{
    return left.getPID() == right.getPID() && left.getStats() == right.getStats() && left.getAbilityIndex() == right.getAbilityIndex()
        && left.getIVs() == right.getIVs() && left.getAbility() == right.getAbility() && left.getGender() == right.getGender()
        && left.getHiddenPower() == right.getHiddenPower() && left.getNature() == right.getNature() && left.getLevel() == right.getLevel()
        && left.getShiny() == right.getShiny() && left.getHiddenPowerStrength() == right.getHiddenPowerStrength();
}

void StaticSearcher3Test::search_data()
{
    QTest::addColumn<IVs>("min");
    QTest::addColumn<IVs>("max");
    QTest::addColumn<Game>("version");
    QTest::addColumn<Method>("method");
    QTest::addColumn<int>("category");
    QTest::addColumn<int>("pokemon");
    QTest::addColumn<std::string>("results");

    json data = readData("static3", "staticsearcher3", "search");
    for (const auto &d : data)
    {
        QTest::newRow(d["name"].get<std::string>().data())
            << d["min"].get<IVs>() << d["max"].get<IVs>() << d["version"].get<Game>() << d["method"].get<Method>()
            << d["category"].get<int>() << d["pokemon"].get<int>() << d["results"].get<json>().dump();
    }
}

void StaticSearcher3Test::search()
{
    QFETCH(IVs, min);
    QFETCH(IVs, max);
    QFETCH(Game, version);
    QFETCH(Method, method);
    QFETCH(int, category);
    QFETCH(int, pokemon);
    QFETCH(std::string, results);

    json j = json::parse(results);

    std::array<bool, 25> natures;
    natures.fill(true);

    std::array<bool, 16> powers;
    powers.fill(true);

    const StaticTemplate *staticTemplate = Encounters3::getStaticEncounter(category, pokemon);
    StateFilter3 filter(255, 255, 255, false, min, max, natures, powers);
    StaticSearcher3 searcher(12345, 54321, version, method, Lead::None, filter);

    searcher.startSearch(min, max, staticTemplate);
    auto states = searcher.getResults();
    QCOMPARE(states.size(), j.size());

    for (size_t i = 0; i < states.size(); i++)
    {
        const auto &state = states[i];
        QVERIFY(state == j[i]);

        // Ensure generator agrees
        StaticGenerator3 generator(0, 0, 0, 12345, 54321, version, method, Lead::None, filter);
        auto generatorStates = generator.generate(state.getSeed(), staticTemplate);

        QCOMPARE(generatorStates.size(), 1);
        QVERIFY(state == generatorStates[0]);
    }
}
