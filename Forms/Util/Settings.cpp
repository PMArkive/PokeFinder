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

#include "Settings.hpp"
#include "ui_Settings.h"

Settings::Settings(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose, false);
    setAttribute(Qt::WA_DeleteOnClose);

    svg.load(QString(":/svg/background.svg"));

    QSettings setting;
    QString lang = setting.value("language", "en").toString();

    const QStringList langs = { "zh_Hans_CN", "en", "fr", "de", "it", "ja", "ko", "es" };
    ui->buttonGroup->buttons()[langs.indexOf(lang)]->setChecked(true);

    ui->pushButtonChinese->setImage(":/svg/chinese.svg");
    ui->pushButtonEnglish->setImage(":/svg/english.svg");
    ui->pushButtonFrench->setImage(":/svg/french.svg");
    ui->pushButtonGerman->setImage(":/svg/german.svg");
    ui->pushButtonItalian->setImage(":/svg/italian.svg");
    ui->pushButtonJapanese->setImage(":/svg/japanese.svg");
    ui->pushButtonKorean->setImage(":/svg/korean.svg");
    ui->pushButtonSpanish->setImage(":/svg/spanish.svg");
}

Settings::~Settings()
{
    delete ui;
}

void Settings::paintEvent(QPaintEvent *event)
{
    if (event->type() == QPaintEvent::Paint)
    {
        QPainter painter(this);
        svg.render(&painter, this->rect());
    }
}

void Settings::changeLanguage(const QString &newLang)
{
    QSettings setting;
    QString currLang = setting.value("language", "en").toString();

    if (currLang != newLang)
    {
        setting.setValue("language", newLang);

        QMessageBox message(QMessageBox::Question, tr("Language changed"), tr("Please restart for changes to take effect. Restart now?"), QMessageBox::Yes | QMessageBox::No);
        if (message.exec() == QMessageBox::Yes)
        {
            QProcess::startDetached(QApplication::applicationFilePath());
            QApplication::quit();
        }
    }
}

void Settings::on_pushButtonChinese_clicked()
{
    changeLanguage("zh_Hans_CN");
}

void Settings::on_pushButtonEnglish_clicked()
{
    changeLanguage("en");
}

void Settings::on_pushButtonFrench_clicked()
{
    changeLanguage("fr");
}

void Settings::on_pushButtonGerman_clicked()
{
    changeLanguage("de");
}

void Settings::on_pushButtonItalian_clicked()
{
    changeLanguage("it");
}

void Settings::on_pushButtonJapanese_clicked()
{
    changeLanguage("ja");
}

void Settings::on_pushButtonKorean_clicked()
{
    changeLanguage("ko");
}

void Settings::on_pushButtonSpanish_clicked()
{
    changeLanguage("es");
}
