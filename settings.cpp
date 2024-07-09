#include "settings.h"

Settings::Settings() {}

void Settings::createSettings(QString const &name, QStringList const &data){
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString fullname = path + "/" + name + ".settings";

    QJsonObject settings
        {
            {"currency", data[0]},
            {"period", data[1]},
        };
    /*
     * add non-regular categories
     */
/*
 * how to construct object
 * rates with currency rates for various currencies
    QJsonObject rates;
    rates["USD"] = "1.35";
    rates["RUB"] = "65";
    QJsonArray r;
    r.push_back(rates);
    settings.insert("rates",r);
*/
    QJsonObject categories;
    categories["Grocery"];
    categories["Fuel"];
    categories["Cafes, restraurants"];
    categories["Entertainment"];
    categories["Public_transport"];
    categories["Communications"];
    categories["Utilities"];
    categories["Kids education/development"];
    categories["Alcohol"];
    categories["Car maintenance"];
    categories["House maintenance"];
    categories["Insurances"];
    categories["Medical"];
    categories["Hygiene"];
    categories["Detergents"];
    categories["Clothes"];
    categories["Presents"];

    QJsonArray cat;
    cat.push_back(categories);
    settings.insert("regular",cat);

    QJsonDocument document(settings);
    saveJson(document, fullname);
}

void Settings::readSettings(QString const &name){
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    path += "/" + name + ".settings";
    this->config = loadJson(path);
    this->settings = this->config.object();
    qDebug() << "Settings: file loaded: " << path;
}
