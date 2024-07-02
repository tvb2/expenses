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
    qDebug("New profile created!");
}

