#include "settings.h"

Settings::Settings() {}

void Settings::createSettings(QString const &name, QStringList const &data){
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString fullname = path + "/" + name + ".settings";

    QJsonObject settings
        {
            {"currency", data[0]},
            {"period", data[1]}
        };
    QJsonDocument document(settings);
    saveJson(document, fullname);
}
