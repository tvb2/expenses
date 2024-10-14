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

    qDebug() << "Start date: " << this->settings->startDate();
    this->db->startDate(this->settings->startDate());
    this->stats->startDate(this->settings->startDate(), 0);

    updateTotals();
    qDebug() << "Dispatch::setProfile complete";
}

void Dispatch::selectProfile()  {
    QStringList existingNames;
    this->profile->getProfileNames(existingNames);

    SelectProfile *s = new SelectProfile(existingNames);
    QObject::connect(s, &SelectProfile::selectProfile, this, &Dispatch::setProfile);
    s->exec();
}

void Dispatch::updateTotals(){

    this->stats->clearAll();
    QVariantList cats = this->settings->getRegCats();
    foreach (auto cat, cats) {
        this->db->getRegTotals(cat.toString());
        this->db->getNonRegTotals();
    }
}

void Dispatch::startMainW(){
    this->mW = new MainWindow;
    QObject::connect(this->settings, &Settings::transmitSettings, this->mW, &MainWindow::populateLists);
    QObject::connect(this->mW, &MainWindow::newRecordAvailable,this, &Dispatch::newRecordRequest);
    QObject::connect(this->mW, &MainWindow::editCurrencyPBclicked,this, &Dispatch::editCurrency);
    QObject::connect(this->db, &Database::latestRecords, this->mW, &MainWindow::populateRecords);
    QObject::connect(this->mW, &MainWindow::requestAVG, this, &Dispatch::averages);
    QObject::connect(this->mW, &MainWindow::recordByID, this, &Dispatch::updateRecord);

    this->settings->readSettings(this->profile->getCurrentProfileName());
    this->db->getLatestN(5);

    this->mW->show();
}

void Dispatch::newProfileCreated(QString const &name, QVariantMap const &settings){

    this->db->createDB(name);
    this->profile->createProfile(name);
    this->settings->createSettings(name, settings);

    setProfile(name);
}

void Dispatch::newRecordRequest(Record const &record){
    qDebug("Dispatch::newRecordRequest recieved signal");


    this->db->addRecord(record);
    this->db->getLatestN(5);
}

void Dispatch::updateRecord(int64_t rowid){
    Record rec;
    this->db->getRecord(rec, rowid);
    qDebug() << "Record final amount before update: " << rec.finalAmnt;
    this->mW->editRecord(rec);
    qDebug() << "Record final amount after update: " << rec.finalAmnt;
    this->db->updateRecord(rec);
    updateTotals();
    averages();
    this->db->getLatestN(5);
}

void Dispatch::editCurrency(SettingsBundle const &bundle){
    EditCurrency *ec = new EditCurrency;
    ec->populate(bundle);
    ec->show();
}

void Dispatch::averages(){
    QString period = this->settings->getDefaultPeriod();

    this->mW->catAVG(this->stats->catAVG(this->mW->getCurrentCat(),period));

    this->mW->periodRegTotal(this->db->periodRegTotal(period));
    this->mW->periodRegAVG(this->stats->avg(period));

    this->mW->periodNonRegTotal(this->db->periodNonRegTotal(period));
    this->mW->periodNonRegAVG(this->stats->catAVG("non-regular", period));

    this->mW->periodTotal(this->db->periodTotal(period));
    this->mW->overallTotal(this->db->periodTotal(Periods::overall));

    this->mW->periodIncomeTotal(this->db->periodIncomeTotal(period));
    this->mW->incomeOverallTotal(this->stats->catOverall("Income"));

    this->mW->periodBalance(this->db->periodBalance(period));
    this->mW->balanceOverall(this->stats->overallBalance());
}
