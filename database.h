#ifndef DATABASE_H
#define DATABASE_H

#include "basecomponent.h"
#include "record.h"

#include <qsqldatabase.h>
#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDir>
#include <QStandardPaths>
#include <QDateTime>

class Database : public QObject, public BaseComponent
{
    Q_OBJECT
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

    /**
     * @brief get latest 5 records submitted
     * @return vector of Records
     */
    void getLatest5();

signals:

    void getLatest(QVector<Record> & latestRecords);

private:
    QSqlDatabase db;
    QDir dir;
    QString path;
    QVector<Record> latest;
    long int index;
};

#endif // DATABASE_H
