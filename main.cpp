#include <QApplication>
#include <QObject>
#include <QLineEdit>
#include <QPushButton>

#include <QDebug>
#include <memory.h>

#include "concretedispatch.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //launch start module and hand over selected DB to DB manager
    qDebug("start");
    a.setOrganizationDomain("github.com/tvb2/expenses");
    a.setApplicationName("expensesApp");


    Profile *profile = new Profile;
    Database *db = new Database;
    Settings *settings = new Settings;
    ConcreteDispatch *dispatch = new ConcreteDispatch(profile, db, settings);
    MainWindow *w = new MainWindow;
    w->getDispatch(dispatch);
    w->show();



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
