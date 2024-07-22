#include "settings.h"

Settings::Settings() {}

void Settings::createSettings(QString const &newName, QVariantMap const & gen){
    //check the profile doesn't exist yet
    if (this->accounts.find(newName) != this->accounts.end()){
        qFatal("Settings::createSettings. Profile already exists!");
        return;
    }

    //current application path. If folder doesn't exist, create it (supposed to be iterative)
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(path);
    if (!dir.exists())
        dir.mkpath(".");

    //new profile becomes current one
    this->name = newName;
    this->fullpath = path + "/" + newName + ".settings";

    //populate default regular categories first time
    this->accounts[newName].regCat= {
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
    this->accounts[newName].settings.insert(
        "Regular",
        QJsonValue::fromVariant(this->accounts[newName].regCat));

    this->updateMap("general", gen);
}

void Settings::readSettings(QString const &newName){
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (newName == this->name){
        qDebug() << "Settings::readSettings. Selected profile is the same as current.";
    }
    else{
        this->fullpath = path + "/" + newName + ".settings";
        QJsonDocument config = loadJson(this->fullpath);
        this->accounts[newName].settings = config.object();

        QVariantMap t = this->accounts[newName].settings.toVariantMap();
        this->accounts[newName].exchRates= t["ExchRates"].toMap();
        this->accounts[newName].general  = t["General"].toMap();
        this->accounts[newName].regCat = t["Regular"].toList();
        this->accounts[newName].nonRegCat = t["NonRegular"].toList();
    }
        //populate currency list
        QStringList curr = this->accounts[newName].exchRates.keys();
        //add default currency to the list
        curr.append(this->accounts[newName].general.value("currency").toString());
        emit transmitSettings(this->accounts[newName].regCat, curr);
    qDebug() << "Settings::readSettings: file loaded: " << this->fullpath;
}

//used only for tests
void Settings::jsonTests(){
    //current path. If folder doesn't exist, create it (supposed to be iterative)
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(path);
    if (!dir.exists())
        dir.mkpath(".");

    this->fullpath = path + "/" + "test" + ".settings";

    QVariantMap g;
    g["currency"] = "AED";
    g["period"] = "weekly";
    this->updateMap("general",g);

    this->accounts[this->name].exchRates["USD"] = 3.67;
    this->accounts[this->name].exchRates["RUB"] = 0.042;
    this->accounts[this->name].exchRates["CAD"] = 2.69;
    QVariantMap r;
    r["UAH"] = 0.090;
    this->updateMap("rates", r);

    this->accounts[this->name].nonRegCat.push_back("yacht");

    r["USD"] = 3.8;
    this->updateMap("rates", r);

    this->accounts[this->name].regCat = {
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
    this->accounts[this->name].settings.insert("Regual",QJsonValue::fromVariant(this->accounts[this->name].regCat));
    saveJson(QJsonDocument(this->accounts[this->name].settings), this->fullpath);
}

void Settings::updateMap(QString section, QVariantMap const &m){

    for (auto i = m.begin(); i != m.end(); ++i){
        if (section == "general")
            this->accounts[this->name].general = m;
        else if(section == "rates")
            this->accounts[this->name].exchRates = m;
        else
            qDebug("Settings: wrong name of Section to update!");
    }

    if (section == "general")
        this->accounts[this->name].settings.insert(
            "General",
            QJsonObject::fromVariantMap(this->accounts[this->name].general));
    else if(section == "rates")
        this->accounts[this->name].settings.insert(
            "ExchRates",
            QJsonObject::fromVariantMap(this->accounts[name].exchRates));

    saveJson(QJsonDocument(this->accounts[this->name].settings), this->fullpath);
}
