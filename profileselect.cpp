#include "profileselect.h"
#include "ui_profileselect.h"

ProfileSelect::ProfileSelect(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProfileSelect)
{
    ui->setupUi(this);
    this->getExistingProfiles();
}

ProfileSelect::~ProfileSelect()
{
    delete ui;
}

void ProfileSelect::getExistingProfiles(){
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
        ui->profileListComboBox->addItem(name);
    }
    for (auto i:profiles)
        qDebug() << i;
}

void ProfileSelect::on_selectPushButton_clicked()
{
    qDebug() << ui->profileListComboBox->currentText();
}

