#ifndef ALLEXPENSES_H
#define ALLEXPENSES_H

#include <QDialog>
#include <QVector>
#include "record.h"
#include "editrecord.h"`

namespace Ui {
class AllExpenses;
}

class AllExpenses : public QDialog
{
    Q_OBJECT

public:
    explicit AllExpenses(QWidget *parent = nullptr);
    ~AllExpenses();

    void populateRecords(QVector<Record> const & allExpenses);

private slots:
    void on_pb_EditRecord_clicked();

signals:
    void recordByID(int64_t rowid);

private:
    Ui::AllExpenses *ui;
};

#endif // ALLEXPENSES_H
