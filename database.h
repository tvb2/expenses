#ifndef DATABASE_H
#define DATABASE_H

#include "basecomponent.h"
#include <qsqldatabase.h>
#include <QSqlQuery>

class Database : public BaseComponent
{
private:
    QSqlDatabase db;
public:
    Database();
    void addExpense();

    //set path for database
    void setDB(QString const &path);
};

#endif // DATABASE_H
