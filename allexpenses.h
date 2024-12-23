#ifndef ALLEXPENSES_H
#define ALLEXPENSES_H

#include <QDialog>
#include <QVector>
#include <QMessageBox>
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

    void on_pb_Close_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_pb_DeleteRecord_clicked();

signals:
    void recordByID(int64_t rowid, QString flag);

    void deleteRecord(int64_t rowid, QString flag);

private:
    Ui::AllExpenses *ui;
};

#endif // ALLEXPENSES_H
