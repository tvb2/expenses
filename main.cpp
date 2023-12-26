#include "profilecreate.h"
#include "profileselect.h"

#include <QApplication>
#include <QObject>
#include <QLineEdit>
#include <QPushButton>

#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //launch start module and hand over selected DB to DB manager
    qDebug("start");
    a.setOrganizationDomain("github.com/tvb2/expenses");
    a.setApplicationName("expensesApp");

    // ProfileCreate createProfile;
    // createProfile.show();

    ProfileSelect selectedProfile;
    selectedProfile.show();
    if (true)
    {
        //launch profile creator
    }
    else if (true)
    {
        //launch profile selector
    }
    else
    {
        //handover to DBManager
    }

    // creating sqlite database
/*
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (path.isEmpty()) qFatal("Cannot determine settings storage location");
    QDir d{path};
    QString thePath;
    if (d.mkpath(d.absolutePath()) && QDir::setCurrent(d.absolutePath())) {
        thePath = QDir::currentPath();
        qDebug() << "settings in" << thePath;// QDir::currentPath();
    }
    thePath = thePath + "/" + "d.sqlite";
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(thePath);
    if (!db.open())
        qDebug("problem opening db");
    else
        qDebug("DB successfully open!");
    qDebug("end");
*/
    return a.exec();
}
