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
        createNew();
    }
//one profile found - select it
    else if(this->profile->size() == 1){

        qDebug("only one profile is found!");
        QString p = this->profile->getProfileNames()[0];
        selectProfile(p);
        this->settings->readSettings(p);
    }
//multiple profiles found - select profile to be used in current session
    else{
        selectProfile();
    }
}

void ConcreteDispatch::createNew(){
    CreateProfile *d = new CreateProfile();

    QObject::connect(d, &CreateProfile::setProfileName, this->db, &Database::createNewDB);
    QObject::connect(d, &CreateProfile::setProfileName, this->profile, &Profile::setPath);
    QObject::connect(d, &CreateProfile::setSettings, this->settings, &Settings::createSettings);

    d->exec();

    //update profile object with newly created database
    this->profile->searchProfiles();
}

void ConcreteDispatch::selectProfile(QString const &p){
    QStringList existingNames = this->profile->getProfileNames();
    int index = 0;
    for (; index < existingNames.size(); ++index){
        if (p == existingNames[index])
            break;
    }
    this->profile->setPath(this->profile->getProfiles()[index]);
    this->db->setDB(this->profile->getCurrentProfile());
    this->settings->readSettings(p);
}

void ConcreteDispatch::selectProfile()  {
    QStringList existingNames = this->profile->getProfileNames();

    SelectProfile *s = new SelectProfile(existingNames);
    QObject::connect(s, &SelectProfile::selectProfile, this->profile, &Profile::setPath);
    QObject::connect(s, &SelectProfile::selectProfile, this->db, &Database::setDB);
    QObject::connect(s, &SelectProfile::selectProfile, this->settings, &Settings::readSettings);
    s->exec();
    qDebug("Multiple profiles found");
}
