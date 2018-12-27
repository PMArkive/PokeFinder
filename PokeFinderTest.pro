lessThan(QT_MAJOR_VERSION, 5):error("You need at least Qt 5.11 to test PokeFinder")
equals(QT_MAJOR_VERSION, 5):lessThan(QT_MINOR_VERSION, 11):error("You need at least Qt 5.11 to test PokeFinder")

QT -= gui
QT += testlib

CONFIG += c++1z console
CONFIG -= app_bundle
DEFINES += QT_DEPRECATED_WARNINGS

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Tests/RNG/LCRNGTest.hpp \
    Core/RNG/LCRNG.hpp \
    Core/RNG/IRNG.hpp \
    Core/RNG/IRNG64.hpp \
    Core/RNG/LCRNG64.hpp \
    Core/RNG/MTRNG.hpp \
    Core/RNG/RNGCache.hpp \
    Core/RNG/RNGEuclidean.hpp \
    Core/RNG/SFMT.hpp \
    Core/RNG/TinyMT.hpp \
    Tests/RNG/LCRNG64Test.hpp \
    Tests/RNG/MTRNGTest.hpp \
    Tests/RNG/RNGCacheTest.hpp \
    Tests/RNG/RNGEuclideanTest.hpp \
    Tests/RNG/SFMTTest.hpp \
    Tests/RNG/TinyMTTest.hpp

SOURCES += \
    Tests/RNG/LCRNGTest.cpp \
    Core/RNG/LCRNG.cpp \
    Core/RNG/LCRNG64.cpp \
    Core/RNG/MTRNG.cpp \
    Core/RNG/RNGCache.cpp \
    Core/RNG/RNGEuclidean.cpp \
    Core/RNG/SFMT.cpp \
    Core/RNG/TinyMT.cpp \
    Tests/RNG/LCRNG64Test.cpp \
    Tests/main.cpp \
    Tests/RNG/MTRNGTest.cpp \
    Tests/RNG/RNGCacheTest.cpp \
    Tests/RNG/RNGEuclideanTest.cpp \
    Tests/RNG/SFMTTest.cpp \
    Tests/RNG/TinyMTTest.cpp

