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
    this->profile->searchProfiles();
    QStringList names = this->profile->getProfilesNames();

    //no profiles found - create profile
    if (this->profile->isEmpty()){
        CreateProfile *d = new CreateProfile(names);
        QObject::connect(d, &CreateProfile::setProfileName, this->profile, &Profile::setPath);
        d->exec();
        qDebug("No profiles found");
    }
     //one profile found - select it
    else if(this->profile->size() == 1){
        qDebug("only one profile is found!");
        this->profile->setPath(this->profile->getProfiles()[0]);
        this->db->setDB(this->profile->getCurrentProfile());
        this->db->addExpense("test");
        this->db->printExpenses();
    }
    //multiple profiles found - select profile to be used in current session
    else{

        //temp
        CreateProfile *d = new CreateProfile(names);
        QObject::connect(d, &CreateProfile::setProfileName, this->profile, &Profile::setPath);
        d->exec();
        qDebug("No profiles found");
        //
        qDebug("Multiple profiles found. Select one:");
    }

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

