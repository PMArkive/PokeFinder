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

#include "Stationary4.hpp"
#include "ui_Stationary4.h"

Stationary4::Stationary4(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Stationary4)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose, false);

    updateProfiles();
    setupModels();

    qRegisterMetaType<QVector<Frame4>>("QVector<Frame4>");
}

Stationary4::~Stationary4()
{
    QSettings setting;
    setting.setValue("stationary4Profile", ui->comboBoxProfiles->currentIndex());
    setting.setValue("stationary4MinDelay", ui->textBoxSearcherMinDelay->text());
    setting.setValue("stationary4MaxDelay", ui->textBoxSearcherMaxDelay->text());
    setting.setValue("stationary4MinFrame", ui->textBoxSearcherMinFrame->text());
    setting.setValue("stationary4MaxFrame", ui->textBoxSearcherMaxFrame->text());

    delete ui;
    delete g;
    delete s;
    delete searcherMenu;
}

void Stationary4::updateProfiles()
{
    profiles = Profile4::loadProfileList();
    profiles.insert(profiles.begin(), Profile4());

    ui->comboBoxProfiles->clear();

    for (const auto &profile : profiles)
    {
        ui->comboBoxProfiles->addItem(profile.getProfileName());
    }

    QSettings setting;
    int val = setting.value("stationary4Profile").toInt();
    if (val < ui->comboBoxProfiles->count())
    {
        ui->comboBoxProfiles->setCurrentIndex(val >= 0 ? val : 0);
    }
}

void Stationary4::setupModels()
{
    ui->tableViewGenerator->setModel(g);
    ui->tableViewSearcher->setModel(s);

    ui->textBoxGeneratorSeed->setValues(InputType::Seed32Bit);
    ui->textBoxGeneratorTID->setValues(InputType::TIDSID);
    ui->textBoxGeneratorSID->setValues(InputType::TIDSID);
    ui->textBoxGeneratorStartingFrame->setValues(InputType::Frame32Bit);
    ui->textBoxGeneratorMaxResults->setValues(InputType::Frame32Bit);
    ui->textBoxGeneratorDelay->setValues(InputType::Frame32Bit);

    ui->textBoxSearcherTID->setValues(InputType::TIDSID);
    ui->textBoxSearcherSID->setValues(InputType::TIDSID);
    ui->textBoxSearcherMinDelay->setValues(InputType::Delay);
    ui->textBoxSearcherMaxDelay->setValues(InputType::Delay);
    ui->textBoxSearcherMinFrame->setValues(InputType::Frame32Bit);
    ui->textBoxSearcherMaxFrame->setValues(InputType::Frame32Bit);

    ui->comboBoxSearcherLead->setItemData(0, Lead::Search);
    ui->comboBoxSearcherLead->setItemData(1, Lead::Synchronize);
    ui->comboBoxSearcherLead->setItemData(2, Lead::CuteCharm);
    ui->comboBoxSearcherLead->setItemData(3, Lead::None);

    ui->comboBoxGeneratorLead->addItem(tr("None"));
    ui->comboBoxGeneratorLead->addItems(Nature::getNatures());

    ui->comboBoxGeneratorNature->setup();
    ui->comboBoxSearcherNature->setup();

    ui->comboBoxGeneratorHiddenPower->setup();
    ui->comboBoxSearcherHiddenPower->setup();

    QAction *seedToTime = new QAction(tr("Generate times for seed"), this);
    connect(seedToTime, &QAction::triggered, this, &Stationary4::seedToTime);

    searcherMenu->addAction(seedToTime);

    QSettings setting;
    if (setting.contains("stationary4MinDelay")) ui->textBoxSearcherMinDelay->setText(setting.value("stationary4MinDelay").toString());
    if (setting.contains("stationary4MaxDelay")) ui->textBoxSearcherMaxDelay->setText(setting.value("stationary4MaxDelay").toString());
    if (setting.contains("stationary4MinFrame")) ui->textBoxSearcherMinFrame->setText(setting.value("stationary4MinFrame").toString());
    if (setting.contains("stationary4MaxFrame")) ui->textBoxSearcherMaxFrame->setText(setting.value("stationary4MaxFrame").toString());
}

void Stationary4::updateView(const QVector<Frame4> &frames, int progress)
{
    s->addItems(frames);
    ui->progressBar->setValue(progress);
}

void Stationary4::refreshProfiles()
{
    emit alertProfiles(4);
}

void Stationary4::on_pushButtonGenerate_clicked()
{
    g->clear();
    g->setMethod(static_cast<Method>(ui->comboBoxGeneratorMethod->currentData().toInt()));

    u32 seed = ui->textBoxGeneratorSeed->text().toUInt(nullptr, 16);
    u32 startingFrame = ui->textBoxGeneratorStartingFrame->text().toUInt();
    u32 maxResults = ui->textBoxGeneratorMaxResults->text().toUInt();
    u16 tid = ui->textBoxGeneratorTID->text().toUShort();
    u16 sid = ui->textBoxGeneratorSID->text().toUShort();
    u32 offset = 0;
    if (ui->checkBoxGeneratorDelay->isChecked())
    {
        offset = ui->textBoxGeneratorDelay->text().toUInt();
    }

    int genderRatioIndex = ui->comboBoxGeneratorGenderRatio->currentIndex();
    Generator4 generator = Generator4(maxResults, startingFrame, seed, tid, sid, offset, static_cast<Method>(ui->comboBoxGeneratorMethod->currentData().toInt()));
    FrameCompare compare = FrameCompare(ui->ivFilterGenerator->getEvals(), ui->ivFilterGenerator->getValues(),
                                        ui->comboBoxGeneratorGender->currentIndex(), genderRatioIndex, ui->comboBoxGeneratorAbility->currentIndex(),
                                        ui->comboBoxGeneratorNature->getChecked(), ui->comboBoxGeneratorHiddenPower->getChecked(),
                                        ui->checkBoxGeneratorShinyOnly->isChecked(), ui->checkBoxGeneratorDisableFilters->isChecked());

    generator.setEncounterType(Stationary);
    if (ui->pushButtonGeneratorLead->text() == tr("Cute Charm"))
    {
        generator.setLeadType(static_cast<Lead>(ui->comboBoxGeneratorLead->currentData().toInt()));
    }
    else
    {
        int num = ui->comboBoxGeneratorLead->currentIndex();
        if (num == 0)
        {
            generator.setLeadType(Lead::None);
        }
        else
        {
            generator.setLeadType(Lead::Synchronize);
            generator.setSynchNature(Nature::getAdjustedNature(static_cast<u32>(ui->comboBoxGeneratorLead->currentIndex() - 1)));
        }
    }

    QVector<Frame4> frames = generator.generate(compare);
    g->setModel(frames);
}

void Stationary4::on_pushButtonSearch_clicked()
{
    s->clear();
    s->setMethod(static_cast<Method>(ui->comboBoxSearcherMethod->currentData().toInt()));

    ui->pushButtonSearch->setEnabled(false);
    ui->pushButtonCancel->setEnabled(true);

    u16 tid = ui->textBoxSearcherTID->text().toUShort();
    u16 sid = ui->textBoxSearcherSID->text().toUShort();

    int genderRatioIndex = ui->comboBoxSearcherGenderRatio->currentIndex();
    FrameCompare compare = FrameCompare(ui->ivFilterSearcher->getEvals(), ui->ivFilterSearcher->getValues(), ui->comboBoxSearcherGender->currentIndex(),
                                        genderRatioIndex, ui->comboBoxSearcherAbility->currentIndex(), ui->comboBoxSearcherNature->getChecked(),
                                        ui->comboBoxSearcherHiddenPower->getChecked(), ui->checkBoxSearcherShinyOnly->isChecked(), false);
    Searcher4 searcher = Searcher4(tid, sid, static_cast<u32>(genderRatioIndex), ui->textBoxSearcherMinDelay->text().toUInt(), ui->textBoxSearcherMaxDelay->text().toUInt(),
                                   ui->textBoxSearcherMinFrame->text().toUInt(), ui->textBoxSearcherMaxFrame->text().toUInt(), compare, static_cast<Method>(ui->comboBoxSearcherMethod->currentData().toInt()));
    searcher.setLeadType(static_cast<Lead>(ui->comboBoxSearcherLead->currentData().toInt()));

    QVector<u8> min = ui->ivFilterSearcher->getLower();
    QVector<u8> max = ui->ivFilterSearcher->getUpper();

    int maxProgress = 1;
    for (int i = 0; i < 6; i++)
    {
        maxProgress *= max[i] - min[i] + 1;
    }

    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(maxProgress);

    auto *search = new StationarySearcher4(searcher, min, max);
    auto *timer = new QTimer();

    connect(search, &StationarySearcher4::finished, timer, &QTimer::deleteLater);
    connect(search, &StationarySearcher4::finished, timer, &QTimer::stop);
    connect(search, &StationarySearcher4::finished, this, [ = ] { ui->pushButtonSearch->setEnabled(true); ui->pushButtonCancel->setEnabled(false); });
    connect(search, &StationarySearcher4::finished, this, [ = ] { updateView(search->getResults(), search->currentProgress()); });
    connect(timer, &QTimer::timeout, this, [ = ] { updateView(search->getResults(), search->currentProgress()); });
    connect(ui->pushButtonCancel, &QPushButton::clicked, search, &StationarySearcher4::cancelSearch);

    search->start();
    timer->start(1000);
}

void Stationary4::on_comboBoxProfiles_currentIndexChanged(int index)
{
    if (index < 0)
    {
        return;
    }

    auto profile = profiles.at(index);
    QString tid = QString::number(profile.getTID());
    QString sid = QString::number(profile.getSID());

    ui->textBoxGeneratorTID->setText(tid);
    ui->textBoxGeneratorSID->setText(sid);
    ui->textBoxSearcherTID->setText(tid);
    ui->textBoxSearcherSID->setText(sid);
    ui->labelProfileTIDValue->setText(tid);
    ui->labelProfileSIDValue->setText(sid);
    ui->labelProfileGameValue->setText(profile.getVersionString());

    bool flag = profile.getVersion() & Game::HGSS;

    ui->comboBoxGeneratorMethod->clear();
    ui->comboBoxGeneratorMethod->addItem(tr("Method 1"), Method::Method1);
    ui->comboBoxGeneratorMethod->addItem(flag ? tr("Method K") : tr("Method J"), flag ? Method::MethodK : Method::MethodJ);
    ui->comboBoxGeneratorMethod->addItem(tr("Wondercard IVs"), Method::WondercardIVs);

    ui->comboBoxSearcherMethod->clear();
    ui->comboBoxSearcherMethod->addItem(tr("Method 1"), Method::Method1);
    ui->comboBoxSearcherMethod->addItem(flag ? tr("Method K") : tr("Method J"), flag ? Method::MethodK : Method::MethodJ);
    ui->comboBoxSearcherMethod->addItem(tr("Wondercard IVs"), Method::WondercardIVs);
}

void Stationary4::on_pushButtonGeneratorLead_clicked()
{
    ui->comboBoxGeneratorLead->clear();
    QString text = ui->pushButtonGeneratorLead->text();
    if (text == tr("Synchronize"))
    {
        ui->pushButtonGeneratorLead->setText(tr("Cute Charm"));
        ui->comboBoxGeneratorLead->setEnabled(true);

        ui->comboBoxGeneratorLead->addItem(tr("♂ Lead"), Lead::CuteCharmFemale);
        ui->comboBoxGeneratorLead->addItem(tr("♀ Lead (50% ♂ Target)"), Lead::CuteCharm50M);
        ui->comboBoxGeneratorLead->addItem(tr("♀ Lead (75% ♂ Target)"), Lead::CuteCharm75M);
        ui->comboBoxGeneratorLead->addItem(tr("♀ Lead (25% ♂ Target)"), Lead::CuteCharm25M);
        ui->comboBoxGeneratorLead->addItem(tr("♀ Lead (87.5% ♂ Target)"), Lead::CuteCharm875M);
    }
    else
    {
        ui->pushButtonGeneratorLead->setText(tr("Synchronize"));

        ui->comboBoxGeneratorLead->addItem("None");
        ui->comboBoxGeneratorLead->addItems(Nature::getNatures());
    }
}

void Stationary4::seedToTime()
{
    QModelIndex index = ui->tableViewSearcher->currentIndex();
    auto *time = new SeedtoTime4(s->data(s->index(index.row(), 0), Qt::DisplayRole).toString(), profiles[ui->comboBoxProfiles->currentIndex()]);
    time->show();
    time->raise();
}

void Stationary4::on_tableViewSearcher_customContextMenuRequested(const QPoint &pos)
{
    if (s->rowCount() == 0)
    {
        return;
    }

    searcherMenu->popup(ui->tableViewSearcher->viewport()->mapToGlobal(pos));
}

void Stationary4::on_pushButtonProfileManager_clicked()
{
    auto *manager = new ProfileManager4();
    connect(manager, &ProfileManager4::updateProfiles, this, &Stationary4::refreshProfiles);
    manager->show();
}


StationarySearcher4::StationarySearcher4(const Searcher4 &searcher, const QVector<u8> &min, const QVector<u8> &max)
{
    this->searcher = searcher;
    this->min = min;
    this->max = max;
    cancel = false;
    progress = 0;

    connect(this, &StationarySearcher4::finished, this, &StationarySearcher4::deleteLater);
}

void StationarySearcher4::run()
{
    for (u8 a = min[0]; a <= max[0]; a++)
    {
        for (u8 b = min[1]; b <= max[1]; b++)
        {
            for (u8 c = min[2]; c <= max[2]; c++)
            {
                for (u8 d = min[3]; d <= max[3]; d++)
                {
                    for (u8 e = min[4]; e <= max[4]; e++)
                    {
                        for (u8 f = min[5]; f <= max[5]; f++)
                        {
                            if (cancel)
                            {
                                return;
                            }

                            auto frames = searcher.search(a, b, c, d, e, f);
                            progress++;

                            QMutexLocker locker(&mutex);
                            results.append(frames);
                        }
                    }
                }
            }
        }
    }
}

int StationarySearcher4::currentProgress() const
{
    return progress;
}

QVector<Frame4> StationarySearcher4::getResults()
{
    QMutexLocker locker(&mutex);
    auto data(results);
    results.clear();
    return data;
}

void StationarySearcher4::cancelSearch()
{
    cancel = true;
}
