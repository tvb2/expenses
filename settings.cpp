#include "settings.h"

Settings::Settings() {}

void Settings::createSettings(QString const &name, QVariantMap const & gen){
    //current path. If folder doesn't exist, create it (supposed to be iterative)
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(path);
    if (!dir.exists())
        dir.mkpath(".");
    this->fullname = path + "/" + name + ".settings";

    //populate default regular categories first time
    this->regCat = {
        "Grocery",
        "Fuel",
        "Cafes, restraurants",
        "Entertainment",
        "Public_transport",
        "Communications",
        "Utilities",
        "Kids education/development",
        "Alcohol",
        "Car maintenance",
        "House maintenance",
        "Insurances",
        "Medical",
        "Hygiene",
        "Detergents",
        "Clothes",
        "Presents"
    };
    this->settings.insert("Regular",QJsonValue::fromVariant(this->regCat));

    this->updateMap("general", gen);
}

void Settings::readSettings(QString const &name){
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    path += "/" + name + ".settings";
    QJsonDocument config = loadJson(path);
    this->settings = config.object();
    QVariantMap t = this->settings.toVariantMap();
    this->general  = t["General"].toMap();
    this->exchRates= t["ExchRates"].toMap();
    this->regCat = t["Regular"].toList();
    this->nonRegCat = t["NonRegular"].toList();

    qDebug() << "Settings: file loaded: " << path;
}

//used only for tests
void Settings::jsonTests(){
    //current path. If folder doesn't exist, create it (supposed to be iterative)
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(path);
    if (!dir.exists())
        dir.mkpath(".");

    this->fullname = path + "/" + "test" + ".settings";

    QVariantMap g;
    g["currency"] = "AED";
    g["period"] = "weekly";
    this->updateMap("general",g);

    this->exchRates["USD"] = 3.67;
    this->exchRates["RUB"] = 0.042;
    this->exchRates["CAD"] = 2.69;
    QVariantMap r;
    r["UAH"] = 0.090;
    this->updateMap("rates", r);

    this->nonRegCat.push_back("yacht");

    r["USD"] = 3.8;
    this->updateMap("rates", r);

    this->regCat = {
        "Grocery",
        "Fuel",
        "Cafes, restraurants",
        "Entertainment",
        "Public_transport",
        "Communications",
        "Utilities",
        "Kids education/development",
        "Alcohol",
        "Car maintenance",
        "House maintenance",
        "Insurances",
        "Medical",
        "Hygiene",
        "Detergents",
        "Clothes",
        "Presents"
    };
    this->settings.insert("Regual",QJsonValue::fromVariant(this->regCat));
    saveJson(QJsonDocument(this->settings), this->fullname);
}

void Settings::updateMap(QString section, QVariantMap const &m){
    for (auto i = m.begin(); i != m.end(); ++i){
        if (section == "general")
            this->general[i.key()] = i.value();
        else if(section == "rates")
            this->exchRates[i.key()] = i.value();
    }
    if (section == "general")
        this->settings.insert("General",QJsonObject::fromVariantMap(this->general));
    else if(section == "rates")
        this->settings.insert("ExchRates",QJsonObject::fromVariantMap(this->exchRates));

    saveJson(QJsonDocument(this->settings), this->fullname);
}
