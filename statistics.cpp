#include "statistics.h"

Statistics::Statistics(QObject *parent)
    : QObject{parent}
{}

void Statistics::setTotals(QVariantList const &cats, QVariantList const &tots){

}

void Statistics::addTot(QString const &category, double val){
    this->regCat[category] += val;
}

double Statistics::catAVG(QString const &category, QString period){
    QDate today = QDate::currentDate();
    double factor{0.0};
    if (period == Periods::weekly){
        factor = 1.0/7.0;
    }
    else if (period == Periods::monthly){
        factor = 12.0/365.0;
    }
    else
        qDebug() << "Statistics::catAVG. Something wrong with default period!";
    double periods = this->sDate.daysTo(today)*factor;
    if (regCat.find(category) != regCat.end())
        return this->regCat[category]/periods;
    else
        return this->nonRegCat/periods;
}

double Statistics::avg(QString period){
    double total{0};
    foreach (auto c, this->regCat) {
        if (c.first != "Income")
            total += c.second;
    }
    qDebug() << "Total: " << total;
    QDate today = QDate::currentDate();
    double factor{0.0};
    if (period == Periods::weekly){
        factor = 1.0/7.0;
    }
    else if (period == Periods::monthly){
        factor = 12.0/365.0;
    }
    else
        qDebug() << "Statistics::avg. Something wrong with default period!";
    double periods = this->sDate.daysTo(today)*factor;
    qDebug() << "Total/periods: " << total/periods;
    return total/periods;
}

double Statistics::catOverall(QString const &category){
    return this->regCat[category];
}

double Statistics::overallBalance(){
    double total{0};
    foreach (auto c, this->regCat) {
        if (c.first == "Income")
            total += c.second;
        else
            total -= c.second;
    }
        total -= this->nonRegCat;
    return total;
}
