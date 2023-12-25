#include "mainwindow.h"
#include "startmodule.h"

#include <QApplication>
#include <QObject>

#include <QtSql>
#include <QSqlRecord>
#include <QDebug>
#include <QStandardPaths>
#include <QListWidgetItem>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //launch start module and hand over selected DB to DB manager
    qDebug("start");
    a.setApplicationName("expensesApp");
    Startmodule start;
    start.show();



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



    MainWindow w;
    //w.show();
    return a.exec();
}
