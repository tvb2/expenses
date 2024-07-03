#include "createprofile.h"
#include "ui_createprofile.h"
#include <QDebug>

CreateProfile::CreateProfile(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateProfile)
{
    ui->setupUi(this);
}

CreateProfile::~CreateProfile()
{
    delete ui;
}

void CreateProfile::on_pbCreateProfile_clicked()
{
    QString name = "NewProfile";
    name = ui->leProfileName->text();
    name = name.length()>=8?name.mid(0,8):name;
    emit setProfileName(name);
    qDebug("New profile created!");
}

