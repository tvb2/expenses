#include "allexpenses.h"
#include "ui_allexpenses.h"

AllExpenses::AllExpenses(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AllExpenses)
{
    ui->setupUi(this);
}

AllExpenses::~AllExpenses()
{
    delete ui;
}
void AllExpenses::populateRecords(QVector<Record> const & allExpenses){

if (!allExpenses.isEmpty()){
    ui->tableWidget->setRowCount(allExpenses.size());
    auto rec = allExpenses.begin();
    for( int row = 0; row < allExpenses.size(); row++ ){
        QStringList itemList;
        itemList.append(rec->date);
        itemList.append(rec->cat);
        itemList.append(QString::number(rec->amount));
        itemList.append(rec->currency);
        itemList.append(QString::number(rec->finalAmnt));
        itemList.append(QString::number(rec->id));
        auto itemListIt = itemList.begin();
        for( int column = 0; column < itemList.size(); column++ ){
            QString item = QString(itemListIt->data());
            QVariant oVariant(item);
            ++itemListIt;
            // allocate the widget item
            QTableWidgetItem * poItem = new QTableWidgetItem();
            poItem->setData( Qt::DisplayRole, oVariant );
            ui->tableWidget->setItem( row, column, poItem );
        }
        ++rec;
    }
    //hide column containing rowid. It will be used to access record for edit/delete
    ui->tableWidget->hideColumn(ui->tableWidget->columnCount() - 1);
    }
}

void AllExpenses::on_pb_EditRecord_clicked()
{

}

