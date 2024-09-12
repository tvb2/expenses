#ifndef STATISTICS_H
#define STATISTICS_H

#include <QObject>
#include <map>
#include <QString>
#include <QVariantList>

#include "settings.h"
#include "database.h"
#include "settingsbundle.h"
#include "Periods.h"

class Statistics : public QObject
{
    Q_OBJECT
public:
    explicit Statistics(QObject *parent = nullptr);

    double catAVG(QString const &category, QString period);

    double avg(QString period);

    double catOverall(QString const &category);

    double overallBalance();

    void startDate(QDate const & sDate){
        this->sDate = sDate;
    }

signals:
public slots:
    void addTot(QString const & category, double val);

    void setTotalNonReg(double val){
        this->nonRegCat = val;
    }

    void addNonReg(double val){
        this->nonRegCat += val;
    }
private:
    std::map<QString, double> regCat;
    double nonRegCat;
    QDate sDate;

    void setTotals(QVariantList const &cats, QVariantList const &tots);
};

#endif // STATISTICS_H
