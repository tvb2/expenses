#ifndef DATABASE_H
#define DATABASE_H

#include "basecomponent.h"

class Database : public BaseComponent
{
private:
    QString dbPath;
public:
    Database();
    void DoD();
    void addExpense();

    //set path for database
    void setPath(QString &path);
};

#endif // DATABASE_H
