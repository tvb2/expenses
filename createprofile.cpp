#include "createprofile.h"
#include "ui_createprofile.h"
#include <QDebug>

CreateProfile::CreateProfile( QStringList const &e, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::CreateProfile),
    existing(e)
{
    ui->setupUi(this);
    ui->cbPeriods->addItems(this->periods);

    //disable default close cross in the title bar
    this->setWindowFlags(Qt::Window |
                         Qt::CustomizeWindowHint |
                         Qt::WindowTitleHint|
                         Qt::WindowSystemMenuHint);
    // ui->pbCreateProfile->setEnabled(false);
}

CreateProfile::~CreateProfile()
{
    delete ui;

}

bool CreateProfile::isUniq(QString const &name){
    foreach (auto p, this->existing) {
        if (name == p){
            return false;
        }
    }
    return true;
}

void CreateProfile::on_pbCreateProfile_clicked()
{
    QString name = "NewProfile";
    //check if profile name is not empty
    if (ui->leProfileName->text().length() > 0){
        name = ui->leProfileName->text();
        name = name.length()>=8?name.mid(0,8):name;
        //check that this profile does not already exist
        if (isUniq(name)){
            emit setProfileName(name);
            this->close();
        }
        else{
            QMessageBox warn;
            warn.setText("Profile with this name already exists!");
            warn.setIcon(QMessageBox::Warning);
            warn.setWindowTitle("Error");
            warn.exec();
        }
    }
    //profile name is empty: show warning and return to Create Profile window
    else{
        QMessageBox warn;
        warn.setText("Profile name must be 1 to 8 characters long!");
        warn.setIcon(QMessageBox::Warning);
        warn.setWindowTitle("Error");
        warn.exec();
    }
    qDebug("New profile created!");
}

