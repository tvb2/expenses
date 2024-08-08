QT       += core gui sql uitools widgets qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basecomponent.cpp \
    dispatch.cpp \
    editcurrency.cpp \
    main.cpp \
    mainwindow.cpp \
    database.cpp \
    profile.cpp \
    settings.cpp \
    createprofile.cpp \
    selectprofile.cpp \
    validator.cpp

HEADERS += \
    basecomponent.h \
    dispatch.h \
    editcurrency.h \
    mainwindow.h \
    database.h \
    profile.h \
    record.h \
    settings.h \
    createprofile.h \
    selectprofile.h \
    settingsbundle.h \
    validator.h

FORMS += \
    createprofile.ui \
    editcurrency.ui \
    mainwindow.ui \
    selectprofile.ui

# TRANSLATIONS += \
#     expenses_ru_RU.ts
# CONFIG += lrelease
# CONFIG += embed_translations

# Default rules for deployment.
# qnx: target.path = /tmp/$${TARGET}/bin
# else: unix:!android: target.path = /opt/$${TARGET}/bin
# !isEmpty(target.path): INSTALLS += target
