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

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QProcess>
#include <QSettings>
#include <QSvgRenderer>

namespace Ui
{
    class Settings;
}

class Settings : public QMainWindow
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings() override;

private:
    Ui::Settings *ui;
    QSvgRenderer svg;

    void paintEvent(QPaintEvent *event) override;
    void changeLanguage(const QString &lang);

private slots:
    void on_pushButtonChinese_clicked();
    void on_pushButtonEnglish_clicked();
    void on_pushButtonFrench_clicked();
    void on_pushButtonGerman_clicked();
    void on_pushButtonItalian_clicked();
    void on_pushButtonJapanese_clicked();
    void on_pushButtonKorean_clicked();
    void on_pushButtonSpanish_clicked();

};

#endif // SETTINGS_HPP
