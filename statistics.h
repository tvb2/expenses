#ifndef STATISTICS_H
#define STATISTICS_H

#include <QObject>
#include <map>
#include <QString>
#include <QVariantList>

#include "settings.h"
#include "database.h"
#include "settingsbundle.h"

class Statistics : public QObject
{
    Q_OBJECT
public:
    explicit Statistics(QObject *parent = nullptr);

    double getCatAv(QString const &category){
        return this->cat[category];
    }

signals:
public slots:
    void addTot(QString const & category, double val);

private:
    std::map<QString, double> cat;

    void setTotals(QVariantList const &cats, QVariantList const &tots);
};

#endif // STATISTICS_H
