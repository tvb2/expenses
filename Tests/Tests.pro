QT += core testlib gui widgets sql uitools
CONFIG += c++17 qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES += \
tst_databasetest.cpp \
../database.cpp \
../settings.cpp \

HEADERS += \
../basecomponent.h \
../database.h \
../settings.h \
