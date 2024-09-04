#ifndef DATABASE_H
#define DATABASE_H

#include "basecomponent.h"
#include "record.h"
#include "Periods.h"

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
     * @brief get latest N records submitted or modified
     * @return vector of Records
     */
    void getLatestN(int N);

    /**
     * @brief For transmitted category return total amount spent since sDate (start Date)
     * @param category
     */
    void getTotals(QString const & cat);

    /**
     * @brief Regular expenses total amount spent for the given period (month, week etc)
     * @param period
     * @return
     */
    double periodRegTotal(QString period);

    /**
     * @brief Non-Regular expenses total amount spent for the given period (month, week etc)
     * @param period
     * @return
     */
    double periodNonRegTotal(QString period);

    /**
     * @brief total (Reg + NonReg) amount spent during the specified period (month, week etc)
     * @param period
     * @return
     */
    double periodTotal(QString period);

    void startDate(QDate const & sDate){
        this->sDate = sDate;
    }

signals:

    void latestRecords(QVector<Record> & latestRecords);

    /**
     * @brief for category cat send total expense amount from start date sDate
     * @param cat
     * @param tot
     */
    void total(QString const & cat, double tot);

    /**
     * @brief send total expense amount for all non-regular expenses
     * from start date sDate
     * @param tot
     */
    void totalNonReg(double tot);

    void getStartDate(QDate const & startDate);

    void updateStartDate(QDate const & sDate);

private:
    QSqlDatabase db;
    QDir dir;
    QString path;
    QVector<Record> latest;
    QDate sDate;
    long int index;

    /**
     * @brief calculate start Date for the given period (month, week etc)
     * then use it to make SELECT query
     * @param period
     * @return
     */
    QString startDate(QString period);

    /**
     * @brief using supplied queryText establish connections to DB and execute query
     * @param queryText
     * @return
     */
    double periodTot(QString queryText);
};

#endif // DATABASE_H
