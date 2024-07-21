#include "dispatch.h"

void Dispatch::Launcher(){
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

//start Main Window
}

void Dispatch::createNew(){
    CreateProfile *d = new CreateProfile();
    QObject::connect(d, &CreateProfile::profileCreated, this, &Dispatch::newProfileCreated);

    d->exec();
    //update profile object with newly created database
    this->profile->searchProfiles();
}

void Dispatch::setProfile(QString const &name){
    MainWindow *w = new MainWindow;
    QObject::connect(this->settings, &Settings::transmitSettings, w, &MainWindow::populate);

    this->profile->setCurrentProfile(name);
    this->db->setCurrentDB(name);
    this->settings->readSettings(name);

    w->show();
}

void Dispatch::selectProfile()  {
    QStringList existingNames;// = this->profile->getProfileNames();

    SelectProfile *s = new SelectProfile(existingNames);
    s->exec();
}

void Dispatch::startMainW(QVariant const &cat, QStringList const &curr){
    MainWindow *w = new MainWindow;
    w->show();
}

void Dispatch::newProfileCreated(QString const &name, QVariantMap const &settings){
    this->db->createDB(name);
    this->profile->addProfile(name);
    this->settings->createSettings(name, settings);
}
