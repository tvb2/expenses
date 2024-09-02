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

    /**
     * @brief average expense for the default period
     * @return avg
     */
    double getAverage(QString period);

    void getTotals(QString const & cat);

    void setStartDate(QDate const & sDate){
        this->startDate = sDate;
    }

signals:

    void getLatest(QVector<Record> & latestRecords);

    void getTotal(QString const & cat, double tot);

    void getStartDate(QDate const & startDate);

    void updateStartDate(QDate const & sDate);

private:
    QSqlDatabase db;
    QDir dir;
    QString path;
    QVector<Record> latest;
    QDate startDate;
    long int index;
};

#endif // DATABASE_H
