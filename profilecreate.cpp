#include "profilecreate.h"
#include "ui_profilecreate.h"

#include <QDebug>

ProfileCreate::ProfileCreate(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProfileCreate)
{
    ui->setupUi(this);
}

ProfileCreate::~ProfileCreate()
{
    delete ui;
}

void ProfileCreate::on_createPB_clicked()
{
    QString name;
    if (ui->profileNewNameLineEdit->text() == ""){
        name = "user1";
    }
    else{
        name = ui->profileNewNameLineEdit->text().remove(QChar(' '));
        // qDebug() << name;
    }

    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (path.isEmpty()) qFatal("Cannot determine settings storage location");
    QDir d{path};
    QString thePath;
    if (d.mkpath(d.absolutePath()) && QDir::setCurrent(d.absolutePath())) {
        thePath = QDir::currentPath();
        // qDebug() << "settings in" << thePath;// QDir::currentPath();
    }

    QSqlDatabase db;
    QString dbname = thePath + "/" + name + this->extension;
    qDebug() << dbname;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbname);
    if (!db.open())
        qDebug() << "problem opening db " << dbname;
    else
        // qDebug("DB successfully open!");
    qDebug("end");
    this->close();
}
