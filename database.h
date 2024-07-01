#ifndef DATABASE_H
#define DATABASE_H

#include "basecomponent.h"
#include <qsqldatabase.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

class Database : public BaseComponent
{
private:
    QSqlDatabase db;
public:
    Database();
    void addExpense();

    //set path for database
    void setDB(QString const &path);
    void printExpenses();
    bool addExpense(const QString &cat);
};

#endif // DATABASE_H
