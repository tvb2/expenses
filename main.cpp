#include "mainwindow.h"

#include <QApplication>
#include <QObject>

#include <QtSql>
#include <QDebug>
#include <QStandardPaths>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // creating sqlite database
    qDebug("start");


    a.setOrganizationDomain("github.com/tvb2/expenses");
    a.setApplicationName("expensesApp");
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (path.isEmpty()) qFatal("Cannot determine settings storage location");
    QDir d{path};
    if (d.mkpath(d.absolutePath()) && QDir::setCurrent(d.absolutePath())) {
        auto thePath = QDir::currentPath();
        qDebug() << "settings in" << thePath;// QDir::currentPath();
    }

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("d.sqlite");
    if (!db.open())
        qDebug("problem opening db");
    else
        qDebug("DB successfully open!");
    qDebug("end");

    MainWindow w;
    w.show();
    return a.exec();
}
