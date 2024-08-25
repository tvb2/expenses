#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cbCategory->setEditable(false);
    ui->cbNonRegCat->setEnabled(false);
    ui->leAmount->setValidator(new Validator);
    ui->pB_Submit->setEnabled(false);

    ui->date->setDate(QDate::currentDate());
    ui->date->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbOK_clicked(){
    qDebug("MainW: OK pressed");
}

void MainWindow::on_pB_Submit_clicked()
{
    if (!ui->chboxReg->isChecked())
        this->record.cat = ui->cbCategory->currentText();
    else
        this->record.cat = ui->cbNonRegCat->currentText();
    this->record.date = ui->date->date().toString("yyyy.MM.dd");
    this->record.currency = ui->cbCurrency->currentText();
    this->record.reg = !ui->chboxReg->isChecked();
    this->record.rate = ui->lbRate->text().toDouble();
    this->record.finalAmnt = this->record.amount*ui->lbRate->text().toDouble();
    emit newRecordAvailable(this->record);

    qDebug("MainW: Submit button pressed");
    ui->pB_Submit->setEnabled(false);
}

void MainWindow::populateLists(SettingsBunlde const &settings){
    this->setBundle = settings;
    QStringList regC;
    foreach (auto i, this->setBundle.regCat) {
        regC.append(i.toStringList());
    }
    ui->cbCategory->addItems(regC);

    ui->cbCurrency->addItems(this->setBundle.exchRates.keys());
    QStringList nonR;
    foreach (auto i, this->setBundle.nonRegCat) {
        nonR.append(i.toStringList());
    }
    ui->cbNonRegCat->addItems(nonR);
    ui->lbRate->setText(this->setBundle.exchRates.value( ui->cbCurrency->currentText()).toString());
}

void MainWindow::populateRecords(QVector<Record> const & lastRecords){
    if (!lastRecords.isEmpty()){
    auto rec = lastRecords.begin();
    for( int row = 0; row < lastRecords.size(); row++ ){
        QStringList itemList;
        itemList.append(rec->date);
        itemList.append(rec->cat);
        itemList.append(QString::number(rec->amount));
        itemList.append(rec->currency);
        itemList.append(QString::number(rec->finalAmnt));
        auto itemListIt = itemList.begin();
        for( int column = 0; column < 5; column++ ){
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
    foreach (auto item, lastRecords) {
        ui->lbLatest0Date->setText(item.date);
        ui->lbLatest0Cat->setText(item.cat);
        ui->lbLatest0Amount->setText(QString::number(item.amount));
        ui->lbLatest0Curr->setText(item.currency);
    }
    }
    }

void MainWindow::on_chboxReg_stateChanged(int arg1)
{
    if (ui->chboxReg->checkState()){
        ui->cbNonRegCat->setEnabled(true);
        ui->cbNonRegCat->setEditable(true);
        ui->cbCategory->setVisible(false);
        ui->lbCategory->setVisible(false);
        ui->pbAddCat->setVisible(false);
    }
    if (!ui->chboxReg->checkState()){
        ui->cbNonRegCat->clearEditText();
        ui->cbNonRegCat->setEnabled(false);
        ui->cbCategory->setVisible(true);
        ui->lbCategory->setVisible(true);
        ui->pbAddCat->setVisible(true);
    }
}

void MainWindow::on_leAmount_textChanged(const QString &arg1)
{
    QJSEngine jsEngine;
    QJSValue eval = jsEngine.evaluate(ui->leAmount->displayText());
    if (eval.isError() || ui->leAmount->text().isEmpty()){
        ui->pB_Submit->setEnabled(false);
        ui->lbAmountEntered->setText(" ... ");
    }
    else{
        ui->pB_Submit->setEnabled(true);
        ui->lbAmountEntered->setText("resulting value: " + eval.toString());
        this->record.amount = eval.toNumber();
    }
}

void MainWindow::on_chBtoday_clicked()
{
    if (!ui->chBtoday->checkState()){
        ui->date->setEnabled(true);
    }
    else{
        ui->date->setDate(QDate::currentDate());
        ui->date->setEnabled(false);
    }
}

void MainWindow::on_pbAddCat_clicked()
{

}

void MainWindow::on_cbCurrency_currentTextChanged(const QString &arg1)
{
    ui->lbRate->setText(this->setBundle.exchRates.value( ui->cbCurrency->currentText()).toString());

}

void MainWindow::on_pbEditCurrency_clicked()
{
    emit editCurrencyPBclicked(this->setBundle);
}

