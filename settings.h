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

public slots:

    /*
     *
     */
    void createSettings(QString const &name, QStringList const & data);

private:
    QJsonArray settings;
};

#endif // SETTINGS_H
