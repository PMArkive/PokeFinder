lessThan(QT_MAJOR_VERSION, 5):error("You need at least Qt 5.11 to build PokeFinder")
equals(QT_MAJOR_VERSION, 5):lessThan(QT_MINOR_VERSION, 11):error("You need at least Qt 5.11 to build PokeFinder")

QT += network widgets
CONFIG += c++1z

TARGET = PokeFinder
TEMPLATE = app
VERSION = 2.2.0
QMAKE_TARGET_DESCRIPTION = PokeFinder
QMAKE_TARGET_COPYRIGHT = Admiral_Fish

RC_ICONS += Images/pokefinder.ico
ICON += Images/pokefinder.icns

DEFINES += QT_DEPRECATED_WARNINGS

TRANSLATIONS += \
    Translations/PokeFinder_en.ts \
    Translations/PokeFinder_fr.ts \
    Translations/PokeFinder_es.ts \
    Translations/PokeFinder_de.ts \
    Translations/PokeFinder_it.ts \
    Translations/PokeFinder_ja.ts \
    Translations/PokeFinder_ko.ts \
    Translations/PokeFinder_zh_Hans_CN.ts

RESOURCES += \
    resources.qrc

FORMS += \
    Forms/Controls/IVFilter.ui \
    Forms/Gen3/Eggs3.ui \
    Forms/Gen3/GameCubeRTC.ui \
    Forms/Gen3/IDs3.ui \
    Forms/Gen3/JirachiPattern.ui \
    Forms/Gen3/PIDtoIVs.ui \
    Forms/Gen3/PokeSpot.ui \
    Forms/Gen3/ProfileManager3.ui \
    Forms/Gen3/ProfileManager3NewEdit.ui \
    Forms/Gen3/SeedToTime3.ui \
    Forms/Gen3/Stationary3.ui \
    Forms/Gen3/Wild3.ui \
    Forms/Gen4/Eggs4.ui \
    Forms/Gen4/IDs4.ui \
    Forms/Gen4/ProfileManager4.ui \
    Forms/Gen4/ProfileManager4NewEdit.ui \
    Forms/Gen4/RoamerMap.ui \
    Forms/Gen4/SearchCalls.ui \
    Forms/Gen4/SearchCoinFlips.ui \
    Forms/Gen4/SeedtoTime4.ui \
    Forms/Gen4/Stationary4.ui \
    Forms/Gen4/Wild4.ui \
    Forms/Util/IVtoPID.ui \
    Forms/Util/Researcher.ui \
    Forms/MainWindow.ui \
    Forms/Util/Timer.ui

HEADERS += \
    Core/Gen3/Egg3.hpp \
    Core/Gen3/EncounterArea3.hpp \
    Core/Gen3/Encounters3.hpp \
    Core/Gen3/Frame3.hpp \
    Core/Gen3/Generator3.hpp \
    Core/Gen3/NatureLock.hpp \
    Core/Gen3/Profile3.hpp \
    Core/Gen3/Searcher3.hpp \
    Core/Gen4/Egg4.hpp \
    Core/Gen4/EncounterArea4.hpp \
    Core/Gen4/Encounters4.hpp \
    Core/Gen4/Frame4.hpp \
    Core/Gen4/Generator4.hpp \
    Core/Gen4/HGSSRoamer.hpp \
    Core/Gen4/Profile4.hpp \
    Core/Gen4/Searcher4.hpp \
    Core/Objects/Egg.hpp \
    Core/Objects/Encounter.hpp \
    Core/Objects/EncounterArea.hpp \
    Core/Objects/EncounterSlot.hpp \
    Core/Objects/Frame.hpp \
    Core/Objects/FrameCompare.hpp \
    Core/Objects/Game.hpp \
    Core/Objects/Generator.hpp \
    Core/Objects/Global.hpp \
    Core/Objects/Lead.hpp \
    Core/Objects/Method.hpp \
    Core/Objects/Nature.hpp \
    Core/Objects/Power.hpp \
    Core/Objects/Profile.hpp \
    Core/Objects/Searcher.hpp \
    Core/Objects/Utilities.hpp \
    Core/RNG/IRNG.hpp \
    Core/RNG/IRNG64.hpp \
    Core/RNG/LCRNG.hpp \
    Core/RNG/LCRNG64.hpp \
    Core/RNG/MTRNG.hpp \
    Core/RNG/RNGCache.hpp \
    Core/RNG/RNGEuclidean.hpp \
    Core/RNG/SFMT.hpp \
    Core/RNG/TinyMT.hpp \
    Core/Translator.hpp \
    Forms/Controls/CheckList.hpp \
    Forms/Controls/IVFilter.hpp \
    Forms/Controls/Label.hpp \
    Forms/Controls/TableView.hpp \
    Forms/Controls/TextBox.hpp \
    Forms/Gen3/Eggs3.hpp \
    Forms/Gen3/GameCubeRTC.hpp \
    Forms/Gen3/IDs3.hpp \
    Forms/Gen3/JirachiPattern.hpp \
    Forms/Gen3/PIDtoIVs.hpp \
    Forms/Gen3/PokeSpot.hpp \
    Forms/Gen3/ProfileManager3.hpp \
    Forms/Gen3/ProfileManager3NewEdit.hpp \
    Forms/Gen3/SeedToTime3.hpp \
    Forms/Gen3/Stationary3.hpp \
    Forms/Gen3/Wild3.hpp \
    Forms/Gen4/Eggs4.hpp \
    Forms/Gen4/IDs4.hpp \
    Forms/Gen4/ProfileManager4.hpp \
    Forms/Gen4/ProfileManager4NewEdit.hpp \
    Forms/Gen4/RoamerMap.hpp \
    Forms/Gen4/SearchCalls.hpp \
    Forms/Gen4/SearchCoinFlips.hpp \
    Forms/Gen4/SeedtoTime4.hpp \
    Forms/Gen4/Stationary4.hpp \
    Forms/Gen4/Wild4.hpp \
    Forms/Util/IVtoPID.hpp \
    Forms/Util/Researcher.hpp \
    Forms/MainWindow.hpp \
    Models/Gen3/Egg3Model.hpp \
    Models/Gen3/PokeSpotModel.hpp \
    Models/Gen3/Profile3Model.hpp \
    Models/Gen3/Searcher3Model.hpp \
    Models/Gen3/Stationary3Model.hpp \
    Models/Gen3/Wild3Model.hpp \
    Models/Gen4/Egg4Model.hpp \
    Models/Gen4/Profile4Model.hpp \
    Models/Gen4/Searcher4Model.hpp \
    Models/Gen4/SeedtoTime4Model.hpp \
    Models/Gen4/Stationary4Model.hpp \
    Models/Gen4/Wild4Model.hpp \
    Models/ResearcherModel.hpp \
    Util/DateTime.hpp \
    Util/ResearcherFrame.hpp \
    Util/TableUtility.hpp \
    Forms/Util/Timer.hpp

SOURCES += \
    Core/Gen3/Egg3.cpp \
    Core/Gen3/EncounterArea3.cpp \
    Core/Gen3/Encounters3.cpp \
    Core/Gen3/Frame3.cpp \
    Core/Gen3/Generator3.cpp \
    Core/Gen3/NatureLock.cpp \
    Core/Gen3/Profile3.cpp \
    Core/Gen3/Searcher3.cpp \
    Core/Gen4/Egg4.cpp \
    Core/Gen4/EncounterArea4.cpp \
    Core/Gen4/Encounters4.cpp \
    Core/Gen4/Frame4.cpp \
    Core/Gen4/Generator4.cpp \
    Core/Gen4/HGSSRoamer.cpp \
    Core/Gen4/Profile4.cpp \
    Core/Gen4/Searcher4.cpp \
    Core/Objects/Egg.cpp \
    Core/Objects/EncounterArea.cpp \
    Core/Objects/EncounterSlot.cpp \
    Core/Objects/Frame.cpp \
    Core/Objects/FrameCompare.cpp \
    Core/Objects/Generator.cpp \
    Core/Objects/Nature.cpp \
    Core/Objects/Power.cpp \
    Core/Objects/Profile.cpp \
    Core/Objects/Searcher.cpp \
    Core/Objects/Utilities.cpp \
    Core/RNG/LCRNG.cpp \
    Core/RNG/LCRNG64.cpp \
    Core/RNG/MTRNG.cpp \
    Core/RNG/RNGCache.cpp \
    Core/RNG/RNGEuclidean.cpp \
    Core/RNG/SFMT.cpp \
    Core/RNG/TinyMT.cpp \
    Core/Translator.cpp \
    Forms/Controls/CheckList.cpp \
    Forms/Controls/IVFilter.cpp \
    Forms/Controls/Label.cpp \
    Forms/Controls/TableView.cpp \
    Forms/Controls/TextBox.cpp \
    Forms/Gen3/Eggs3.cpp \
    Forms/Gen3/GameCubeRTC.cpp \
    Forms/Gen3/IDs3.cpp \
    Forms/Gen3/JirachiPattern.cpp \
    Forms/Gen3/PIDtoIVs.cpp \
    Forms/Gen3/PokeSpot.cpp \
    Forms/Gen3/ProfileManager3.cpp \
    Forms/Gen3/ProfileManager3NewEdit.cpp \
    Forms/Gen3/SeedToTime3.cpp \
    Forms/Gen3/Stationary3.cpp \
    Forms/Gen3/Wild3.cpp \
    Forms/Gen4/Eggs4.cpp \
    Forms/Gen4/IDs4.cpp \
    Forms/Gen4/ProfileManager4.cpp \
    Forms/Gen4/ProfileManager4NewEdit.cpp \
    Forms/Gen4/RoamerMap.cpp \
    Forms/Gen4/SearchCalls.cpp \
    Forms/Gen4/SearchCoinFlips.cpp \
    Forms/Gen4/SeedtoTime4.cpp \
    Forms/Gen4/Stationary4.cpp \
    Forms/Gen4/Wild4.cpp \
    Forms/Util/IVtoPID.cpp \
    Forms/Util/Researcher.cpp \
    Forms/MainWindow.cpp \
    Models/Gen3/Egg3Model.cpp \
    Models/Gen3/PokeSpotModel.cpp \
    Models/Gen3/Profile3Model.cpp \
    Models/Gen3/Searcher3Model.cpp \
    Models/Gen3/Stationary3Model.cpp \
    Models/Gen3/Wild3Model.cpp \
    Models/Gen4/Egg4Model.cpp \
    Models/Gen4/Profile4Model.cpp \
    Models/Gen4/Searcher4Model.cpp \
    Models/Gen4/SeedtoTime4Model.cpp \
    Models/Gen4/Stationary4Model.cpp \
    Models/Gen4/Wild4Model.cpp \
    Models/ResearcherModel.cpp \
    Util/DateTime.cpp \
    Util/ResearcherFrame.cpp \
    main.cpp \
    Util/TableUtility.cpp \
    Forms/Util/Timer.cpp
