#include "profile.h"

Profile::Profile() {}
Profile::Profile(QSqlDatabase &db) {}

QSqlDatabase & Profile::selectProfile(){
    QSqlDatabase db;
    return db;
}
QString Profile::createProfile(QApplication &a) {

    a.setOrganizationDomain("github.com/tvb2/expenses");
    a.setApplicationName("expensesApp");
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (path.isEmpty()) qFatal("Cannot determine settings storage location");
    QDir d{path};
    QString thePath;
    if (d.mkpath(d.absolutePath()) && QDir::setCurrent(d.absolutePath())) {
        thePath = QDir::currentPath();
        qDebug() << "settings in" << thePath;// QDir::currentPath();
    }

    QSqlDatabase db;
    QString dbname = thePath + "d.sqlite";
    qDebug() << dbname;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbname);
    if (!db.open())
        qDebug("problem opening db");
    else
        qDebug("DB successfully open!");
    qDebug("end");
    return dbname;
}
