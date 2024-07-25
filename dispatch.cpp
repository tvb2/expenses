#include "dispatch.h"

void    Dispatch::Launcher(){
//find existing profiles in current directory
    this->profile->searchProfiles();

//no profiles found - create new profile
    if (this->profile->isEmpty()){
        qDebug("ConcreteDispatch::Launcher. No profiles found - create new profile");
        createNew();
    }
//one profile found - select it
    else if(this->profile->size() == 1){
        qDebug() << "Launcher: only one profile is found!";
        QStringList list;
        this->profile->getProfileNames(list);
        if (list.size() != 0)
            setProfile(list[0]);
    }
//multiple profiles found - select profile to be used in current session
    else{
        selectProfile();
    }
    startMainW();
}

void Dispatch::createNew(){
    CreateProfile *d = new CreateProfile();
    QObject::connect(d, &CreateProfile::profileCreated, this, &Dispatch::newProfileCreated);

    d->exec();
}

void Dispatch::setProfile(QString const &name){
    this->profile->setCurrentProfile(name);
    this->db->setCurrentDB(name);
    this->settings->setCurrentSettings(name);
}

void Dispatch::selectProfile()  {
    QStringList existingNames;
    this->profile->getProfileNames(existingNames);

    SelectProfile *s = new SelectProfile(existingNames);
    QObject::connect(s, &SelectProfile::selectProfile, this, &Dispatch::setProfile);
    s->exec();
}

void Dispatch::startMainW(){
    MainWindow *w = new MainWindow;
    QObject::connect(this->settings, &Settings::transmitSettings, w, &MainWindow::populate);
    this->settings->readSettings(this->profile->getCurrentProfileName());

    w->show();
}

void Dispatch::newProfileCreated(QString const &name, QVariantMap const &settings){
    this->db->createDB(name);
    this->profile->createProfile(name);
    this->settings->createSettings(name, settings);

    setProfile(name);
}
