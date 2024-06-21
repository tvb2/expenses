#include "concretedispatch.h"

void ConcreteDispatch::Notify(BaseComponent *sender, std::string event) const {
    if (event == "Pr") {
        qDebug ("Dispatch recieves PROFILE and triggers following operations: ");
    }
    if (event == "DB") {
        qDebug ("Dispatch recieves DATABASE and triggers following operations: ");
    }
}


void ConcreteDispatch::Launcher(){
    //find profiles in current directory
    ConcreteDispatch::searchProfiles();

    //no profiles found - create profile
    if (this->profiles.isEmpty()){
        qDebug("No profiles found");
    }
    else if(this->profiles.size() == 1){
        qDebug("only one profile is found!");
        this->db->setPath(this->profiles[0]);
    }
    else{
        qDebug("Multiple profiles found. Select one:");
    }
    //one profile found - select it

    //multiple profiles found - select profile to be used in current session

    // creating sqlite database

    // thePath = thePath + "/" + "d.sqlite";
    // QSqlDatabase db;
    // db = QSqlDatabase::addDatabase("QSQLITE");
    // db.setDatabaseName(thePath);
    // if (!db.open())
    //     qDebug("problem opening db");
    // else
    //     qDebug("DB successfully open!");
    // qDebug("end");

}


void ConcreteDispatch::searchProfiles(){
    QVector<QString> item;
    QVector<QVector<QString>> profiles;

    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (path.isEmpty()) qFatal("Cannot determine settings storage location");
    QDir d{path};
    QString thePath;
    if (d.mkpath(d.absolutePath()) && QDir::setCurrent(d.absolutePath())) {
        thePath = QDir::currentPath();
        qDebug() << "settings in" << thePath;// QDir::currentPath();
    }
    QStringList filter = {"*.sqlite"};
    QStringList items = d.entryList(filter);
    for (auto i:items){
        this->profiles.append(d.absoluteFilePath(i));
        qDebug() << i;
    }
    qDebug("QString list derived");
}
