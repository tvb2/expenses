#ifndef TESTDATABASE_H
#define TESTDATABASE_H

#include <QObject>
#include <QTest>

class Testdatabase: public QObject
{
    Q_OBJECT
    private slots:
    void printData();
};

#endif // TESTDATABASE_H
