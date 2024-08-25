#ifndef CALC_H
#define CALC_H
/**
 * This class is used for statistical and other calculations with expense records
 */
#include <QObject>

class Calc : public QObject
{
    Q_OBJECT
public:
    explicit Calc(QObject *parent = nullptr);

signals:
};

#endif // CALC_H
