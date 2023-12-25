#include "startmodule.h"
#include "ui_startmodule.h"

Startmodule::Startmodule(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Startmodule)
{
    ui->setupUi(this);
    Startmodule::getExistingProfiles();
}

Startmodule::~Startmodule()
{
    delete ui;
}

void Startmodule::getExistingProfiles(){
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QVector<QString> profiles;
    QDir dir(path);
    QStringList filters;
    filters << "*" + this->extension;
    dir.setNameFilters(filters);
    for (const QString &filename : dir.entryList(QDir::Files)){
        QString name = filename;
        name = name.left(name.lastIndexOf(this->extension));
        profiles.push_back(name);
        ui->profileListCombo->addItem(name);
    }
    for (auto i:profiles)
        qDebug() << i;
}

QDir Startmodule::selectProfile(){
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString name = ui->profileListCombo->currentText() + this->extension;
    path += "/" + name;
    QDir profile(path);
    qDebug() << path;
    return profile;
}

void Startmodule::on_okPB_clicked()
{
    Startmodule::selectProfile();
}

