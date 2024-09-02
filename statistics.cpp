#include "statistics.h"

Statistics::Statistics(QObject *parent)
    : QObject{parent}
{}

void Statistics::setTotals(QVariantList const &cats, QVariantList const &tots){

}

void Statistics::addTot(QString const &category, double val){
    // this->cat.emplace(category, val);
    this->cat[category] += val;
}

double Statistics::catAVG(QString const &category, QString period){
    QDate today = QDate::currentDate();
    double factor{0.0};
    if (period == "weekly"){
        factor = 1.0/7.0;
    }
    else if (period == "monthly"){
        factor = 12.0/365.0;
    }
    else
        qDebug() << "Statistics::catAVG. Something wrong with default period!";
    double periods = this->sDate.daysTo(today)*factor;
    return this->cat[category]/periods;
}

double Statistics::avg(QString period){
    double total{0};
    foreach (auto c, this->cat) {
        total += c.second;
    }
    QDate today = QDate::currentDate();
    double factor{0.0};
    if (period == "weekly"){
        factor = 1.0/7.0;
    }
    else if (period == "monthly"){
        factor = 12.0/365.0;
    }
    else
        qDebug() << "Statistics::avg. Something wrong with default period!";
    double periods = this->sDate.daysTo(today)*factor;
    return total/periods;
}

double Statistics::periodTotal(){
    return 0;
}
