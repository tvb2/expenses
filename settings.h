#ifndef SETTINGS_H
#define SETTINGS_H

#include "basecomponent.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class Settings : public BaseComponent
{
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

    /*
     * update values in corresponding section "rates", "general"
     */
    void updateMap(QString section, QVariantMap const &m);

    /*
     * add single default (regular) category
     */
    void addRegCat(QString const &cat){
        this->regCat.push_back(cat);
        this->settings.insert("Regual",QJsonValue::fromVariant(this->regCat));
        saveJson(QJsonDocument(this->settings), this->fullname);
    }


    /*
     * add single non-regular category
     */
    void addNonRegCat(QString const &cat){
        this->nonRegCat.push_back(cat);
        this->settings.insert("NonRegular",QJsonValue::fromVariant(this->nonRegCat));
        saveJson(QJsonDocument(this->settings), this->fullname);
    }

    /*
     * remove non-regular category (if exists). Removing is allowed
     */
    void remNonRegCat(QString const &cat){
        if(nonRegCat.contains(cat)){
            nonRegCat.removeOne(cat);
        }
    }

public slots:

    /*
     * create settings file
     */
    void createSettings(QString const &name, QVariantMap const & gen);

    /*
     * read settings from file
     */
    void readSettings(QString const &name);

private:
    QJsonObject settings;

    QVariantMap exchRates;
    QVariantMap general;

    QVariantList regCat;
    QVariantList nonRegCat;

    QString fullname;
};

#endif // SETTINGS_H
