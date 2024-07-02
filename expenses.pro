QT       += core gui sql uitools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basecomponent.cpp \
    concretedispatch.cpp \
    database.cpp \
    dispatch.cpp \
    main.cpp \
    mainwindow.cpp \
    profile.cpp \
    settings.cpp \
    widgets/createprofile.cpp \

HEADERS += \
    basecomponent.h \
    concretedispatch.h \
    database.h \
    dispatch.h \
    mainwindow.h \
    profile.h \
    settings.h \
    widgets/createprofile.h \

FORMS += \
    widgets/createprofile.ui \
    mainwindow.ui

# TRANSLATIONS += \
#     expenses_ru_RU.ts
# CONFIG += lrelease
# CONFIG += embed_translations

# Default rules for deployment.
# qnx: target.path = /tmp/$${TARGET}/bin
# else: unix:!android: target.path = /opt/$${TARGET}/bin
# !isEmpty(target.path): INSTALLS += target
