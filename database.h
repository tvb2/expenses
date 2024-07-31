#ifndef DATABASE_H
#define DATABASE_H

#include "basecomponent.h"
#include "record.h"

#include <qsqldatabase.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDir>
#include <QStandardPaths>

class Database : public BaseComponent
{
public:
    Database();
    //virtual to go around a bug that requires a vtable for this class
    virtual ~Database() {}
    /**
     * create database (name only)
     */
    void createDB(QString const &name);

    /**
     * set current profile
     * @param name
     */
    void setCurrentDB(QString const &name);

    void printExpenses();

    bool addRecord(Record const &record);
private:
    QSqlDatabase db;
    QDir dir;
    QString path;
};

#endif // DATABASE_H
