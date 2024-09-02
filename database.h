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
#include <QDate>

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
    void getLatestN(int N);

    void getTotals(QString const & cat);

    double periodTotal(QString period);

    void startDate(QDate const & sDate){
        this->sDate = sDate;
    }

signals:

    void getLatest(QVector<Record> & latestRecords);

    void total(QString const & cat, double tot);

    void getStartDate(QDate const & startDate);

    void updateStartDate(QDate const & sDate);

private:
    QSqlDatabase db;
    QDir dir;
    QString path;
    QVector<Record> latest;
    QDate sDate;
    long int index;
};

#endif // DATABASE_H
