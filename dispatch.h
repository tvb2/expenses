#ifndef DISPATCH_H
#define DISPATCH_H

#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QObject>
#include <QVector>
#include <QStringList>

#include "profile.h"
#include "database.h"
#include "settings.h"
#include "createprofile.h"
#include "selectprofile.h"
#include "mainwindow.h"
#include "record.h"

class Dispatch : public QObject
{
    Q_OBJECT
public:
    Profile *profile;
    Database *db;
    Settings *settings;

    Dispatch(Profile *pr, Database *databs, Settings *st)
        : profile(pr)
        , db(databs)
        , settings(st)
    {

    }

/**
 * take care of all startup routines
 */
void Launcher();

/**
 * create new profile, settings and database
 */
void createNew();

/**
 * select profile and configure DB and Settings
 */
void setProfile(QString const & name);

/*
 * overload select profile from multiple choice
 */
void selectProfile();

public slots:
/**
 * @brief perform all routines required when new profile is created
 * @param name
 * @param settings
 */
void newProfileCreated(QString const &name, QVariantMap const &settings);
    /**
    * starting main window
    */
    void startMainW();
};

#endif // DISPATCH_H
