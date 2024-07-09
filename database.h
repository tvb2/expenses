#ifndef DATABASE_H
#define DATABASE_H

#include "basecomponent.h"
#include <qsqldatabase.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDir>

class Database : public BaseComponent
{
private:
    QSqlDatabase db;
    QDir dir;
public:
    Database();

    /*
     * set database path
     */
    void setDB(QString const &path);

    /*
     * create new database with given path & name
     */
    void createNewDB(QString const &path);

    void printExpenses();
    bool addExpense(const QString &cat);
};

#endif // DATABASE_H
