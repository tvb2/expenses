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
    //find existing profiles in current directory
    this->profile->searchProfiles();

    //no profiles found - create new profile
    if (this->profile->isEmpty()){
        qDebug("No profiles found - create new profile");

        //create new profile name and settings
        CreateProfile *d = new CreateProfile();

        QObject::connect(d, &CreateProfile::setProfileName, this->db, &Database::createNewDB);
        QObject::connect(d, &CreateProfile::setProfileName, this->profile, &Profile::setPath);
        QObject::connect(d, &CreateProfile::setSettings, this->settings, &Settings::createSettings);

        d->exec();

        //update profile object with newly created database
        this->profile->searchProfiles();
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
        QStringList existingNames = this->profile->getProfileNames();

        //temp
        CreateProfile *d = new CreateProfile(existingNames);
        QObject::connect(d, &CreateProfile::setProfileName, this->profile, &Profile::setPath);
        d->exec();
        qDebug("No profiles found");
        //
        qDebug("Multiple profiles found. Select one:");
    }
}

