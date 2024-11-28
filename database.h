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

    void getRecord(Record &record, int64_t id);

    /**
     * @brief get latest N records submitted or modified if N > 0
     * if N == -1 then get all available records
     * @return vector of Records
     */
    void getLatestN(int N);

    /**
     * @brief For transmitted category return total amount spent since sDate (start Date)
     * @param category
     */
    void getRegTotals(QString const & cat);

    /**
     * @brief return total amount spent since sDate (start Date) for non-Regular categories
     * @param category
     */
    void getNonRegTotals();

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
     * @brief Income total during current period
     * @param period
     * @return
     */
    double periodIncomeTotal(QString period);

    /**
     * @brief expense balance.
     * Positive when income > expenses
     * Negative when income < expenses
     * @param period
     * @return
     */
    double periodBalance(QString period);

    /**
     * @brief total (Reg + NonReg) amount spent during the specified period (month, week etc)
     * @param period
     * @return
     */
    double periodTotal(QString period);

    /**
     * @brief set start Date and row of new start date
     * @param sDate
     * @param row
     */
    void startDate(QDate const & sDate,int64_t const & row){
        this->sDate = sDate;
        this->startRow = row;
    }

    void updateRecord(Record const &record);

    void deleteRecord(int64_t rowid);

    /**
     * @brief get row id of the latest added/modified record
     * based on the field lastChangeDateTime
     * @return
     */
    int64_t getLatestRowID();

signals:

    void latestRecords(QVector<Record> & latestRecords);

    void allRecords(QVector<Record> & latestRecords);

    /**
     * @brief for category cat send total expense amount from start date sDate
     * @param cat
     * @param tot
     */
    void total(QString const & cat, double tot);

    void nonReg(double val);

    /**
     * @brief send total expense amount for all non-regular expenses
     * from start date sDate
     * @param tot
     */
    void totalNonReg(double tot);

    // void getStartDate(QDate const & startDate);

    /**
     * @brief provide start date and corresponding row index
     * @param d
     * @param id
     */
    void updateStartDate(QDate const & d, int64_t id);

private:
    QSqlDatabase db;
    QDir dir;
    QString path;
    QVector<Record> latest;
    QDate sDate;
    int64_t startRow;

    /**
     * @brief calculate start Date for the given period (month, week etc)
     * then use it to make SELECT query
     * @param period
     * @return
     */
    QString startDate(QString period);

    /**
     * @brief check if expense date is earlier than current sDate (start Date),
     * then update sDate with the expense date;
     * @param newStartDate
     */
    void startDateCheck(QDate newStartDate, int64_t row);

    /**
     * @brief parse DB and identify earliest date and row of the record
     *
     */
    void startDateUpdate();

    /**
     * @brief using supplied queryText establish connections to DB and execute query
     * @param queryText
     * @return
     */
    double executeQuery(QString queryText);
};

#endif // DATABASE_H
