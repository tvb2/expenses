#ifndef ALLEXPENSES_H
#define ALLEXPENSES_H

#include <QDialog>
#include <QVector>
#include "record.h"

namespace Ui {
class AllExpenses;
}

class AllExpenses : public QDialog
{
    Q_OBJECT

public:
    explicit AllExpenses(QWidget *parent = nullptr);
    ~AllExpenses();

    void populateRecords(QVector<Record> const & allExpenses){

    }

private:
    Ui::AllExpenses *ui;
};

#endif // ALLEXPENSES_H
