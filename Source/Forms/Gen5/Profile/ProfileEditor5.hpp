/*
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

#ifndef PROFILEEDITOR5_HPP
#define PROFILEEDITOR5_HPP

#include <Core/Util/Global.hpp>
#include <QDialog>

namespace Ui
{
    class ProfileEditor5;
}

class Profile5;
enum class DSType : u8;
enum class Game : u32;
enum class Language : u8;

class ProfileEditor5 : public QDialog
{
    Q_OBJECT
public:
    explicit ProfileEditor5(QWidget *parent = nullptr);
    explicit ProfileEditor5(const Profile5 &profile, QWidget *parent = nullptr);
    ProfileEditor5(Game version, Language language, DSType dsType, u64 mac, u8 vcount, u16 timer0, u8 gxstat, u8 vframe,
                   QWidget *parent = nullptr);
    ~ProfileEditor5() override;
    Profile5 getProfile();

private:
    Ui::ProfileEditor5 *ui;

    void setupModels();

private slots:
    void okay();
    void findParameters();
    void versionIndexChanged(int index);
};

#endif // PROFILEEDITOR5_HPP
