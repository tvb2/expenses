#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QtSql>

class DbManager
{
public:
    DbManager();
    DbManager(QSqlDatabase & db);

    void addRecord(QSqlDatabase & db);
    void deleteRecord(QSqlDatabase & db);
    void editRecord(QSqlDatabase & db);
};

#endif // DBMANAGER_H
