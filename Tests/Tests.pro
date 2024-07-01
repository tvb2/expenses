QT += core testlib gui widgets sql
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES += \
tst_databasetest.cpp \
../database.cpp

HEADERS += \
    ../database.h \

