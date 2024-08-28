#include "statistics.h"

Statistics::Statistics(QObject *parent)
    : QObject{parent}
{}

void Statistics::setTotals(QVariantList const &cats, QVariantList const &tots){

}

void Statistics::addTot(QString const &category, double val){
    this->cat.emplace(category, val);
}
