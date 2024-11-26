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
#include "statistics.h"
#include "createprofile.h"
#include "selectprofile.h"
#include "mainwindow.h"
#include "record.h"
#include "settingsbundle.h"
#include "editcurrency.h"

class Dispatch : public QObject
{
    Q_OBJECT
public:
    Profile *profile;
    Database *db;
    Settings *settings;
    Statistics *stats;
    MainWindow *mW;

    Dispatch(Profile *pr, Database *databs, Settings *st, Statistics *statistics)
        : profile(pr)
        , db(databs)
        , settings(st)
        , stats(statistics)
    {
        QObject::connect(this->db, &Database::total, stats, &Statistics::addTot);
        QObject::connect(this->db, &Database::totalNonReg, stats, &Statistics::setTotalNonReg);
        QObject::connect(this->db, &Database::nonReg, stats, &Statistics::addNonReg);

        QObject::connect(this->db, &Database::updateStartDate, this->settings, &Settings::setStartDate);
        QObject::connect(this->db, &Database::updateStartDate, this->stats, &Statistics::startDate);
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

void updateTotals();

public slots:
/**
 * @brief perform all routines required when new profile is created
 * @param name
 * @param settings
 */
    void newProfileCreated(QString const &name, QVariantMap const &settings);

    /**
    * starting main window
    * - populate MainW with info from Settings (categories, currencies etc)
    * - when new expense record is available, send it to Database
    * - manage currency edits
    */
    void startMainW();

    void editCurrency(SettingsBundle const &bundle);

    void newRecordRequest(Record const &record);

    void updateRecord(int64_t rowid);

    void averages();

    void allRecordsRequest();

};

#endif // DISPATCH_H
