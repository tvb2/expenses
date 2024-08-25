#ifndef RECORD_H
#define RECORD_H

#include <QDAte>

struct Record{
    QString date;
    QString cat;
    double amount;
    QString currency;
    double rate;
    double finalAmnt;
    bool reg;
    QString chngDate;
};

#endif // RECORD_H
