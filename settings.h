#ifndef SETTINGS_H
#define SETTINGS_H

#include "basecomponent.h"

#include <QObject>
#include <QJsonDocument>
#include <QVariantMap>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QStandardPaths>
#include <QDir>
#include <map>
#include "settingsbundle.h"


class Settings : public QObject, public BaseComponent
{
    Q_OBJECT
private:
    std::map<QString, SettingsBunlde> accounts;

    QString fullpath;//full path
    QString name;

    /*
     * update values in corresponding section "rates", "general"
     */
    void updateMap(QString const & profile, QString section, QVariantMap const &m);

public:
    Settings();

    QJsonDocument loadJson(QString const &fileName) {
        QFile jsonFile(fileName);
        jsonFile.open(QFile::ReadOnly);
        return QJsonDocument().fromJson(jsonFile.readAll());
    }

    void saveJson(QJsonDocument document, QString const &fileName) {
        QFile jsonFile(fileName);
        jsonFile.open(QFile::WriteOnly);
        jsonFile.write(document.toJson());
    }

    //used only for tests
    void jsonTests();

    /**
     * @brief get default period for statistics
     * @return default period for statistics
     */
    QString getDefaultPeriod();

    /*
     * add single default (regular) category
     */
    void addRegCat(QString const &cat){
        this->accounts[this->name].regCat.push_back(cat);
        this->accounts[this->name].settings.insert("Regual",QJsonValue::fromVariant(this->accounts[this->name].regCat));
        saveJson(QJsonDocument(this->accounts[this->name].settings), this->fullpath);
    }

    /*
     * add single non-regular category
     */
    void addNonRegCat(QString const &cat){
        this->accounts[this->name].nonRegCat.push_back(cat);
        this->accounts[this->name].settings.insert("NonRegular",QJsonValue::fromVariant(this->accounts[this->name].nonRegCat));
        saveJson(QJsonDocument(this->accounts[this->name].settings), this->fullpath);
    }

    /*
     * remove non-regular category (if exists). Removing is allowed
     */
    void remNonRegCat(QString const &cat){
        if(this->accounts[this->name].nonRegCat.contains(cat)){
            this->accounts[this->name].nonRegCat.removeOne(cat);
        }
    }

    /**
     * Name of profile only
     * @param name
     */
    void setCurrentSettings(QString const &newName);

    /**
     * @brief getRegCats
     * @return a list of regular categories
     */
    QVariantList const & getRegCats(){

        return this->accounts[this->name].regCat;
    }

signals:
    /**
     * data to populate MainW
     */
    void transmitSettings(SettingsBunlde const &settings);

public slots:

    /*
     * create settings file
     */
    void createSettings(QString const &newName, QVariantMap const & gen);

    /*
     * read settings from file
     */
    void readSettings(QString const &newName);

};

#endif // SETTINGS_H
