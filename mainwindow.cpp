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
    ui->pbEditRecord->setEnabled(false);
    ui->pb_DeleteRecord->setEnabled(false);

    ui->date->setDate(QDate::currentDate());
    ui->date->setEnabled(false);
    ui->date->setMaximumDate(QDate::currentDate());
    emit requestAVG();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::catAVG(double avg){

    QString catAVG =
        ui->cbCategory->currentText() + " " +
        QString::number(avg, 'f', 1) + " " +
        setBundle.general.value("currency").toString() + " avg/" +
        setBundle.general.value("period").toString();
    ui->lbCatAvg->setText(catAVG);
}

void MainWindow::periodRegTotal(double tot){
    QString periodTot =
        QString::number(tot, 'f', 1) + " " +
        setBundle.general.value("currency").toString();

    ui->lbperiodTotal->setText(periodTot);
}

void MainWindow::periodRegAVG(double avg){
    QString periodAVG =
        QString::number(avg, 'f', 1) + " " +
        setBundle.general.value("currency").toString() + " avg";
    ui->lbPeriodRegAVG->setText(periodAVG);
}

void MainWindow::periodNonRegTotal(double tot){
    QString periodTot =
        QString::number(tot, 'f', 1) + " " +
        setBundle.general.value("currency").toString();

    ui->lbperiodNonRegTot->setText(periodTot);
}

void MainWindow::periodNonRegAVG(double avg){
    QString periodAVG =
        QString::number(avg, 'f', 1) + " " +
        setBundle.general.value("currency").toString() + " avg";
    ui->lbperiodNonRegAVG->setText(periodAVG);
}

void MainWindow::periodTotal(double tot){
    QString periodTot =
        QString::number(tot, 'f', 1) + " " +
        setBundle.general.value("currency").toString();

    ui->lbPeriodTotal->setText(periodTot);
}

void MainWindow::overallTotal(double tot){
    QString periodTot =
        QString::number(tot, 'f', 1) + " " +
        setBundle.general.value("currency").toString() + " tot";
    ui->lbOverallTotal->setText(periodTot);
}

void MainWindow::periodIncomeTotal(double tot){
    QString periodTot =
        QString::number(tot, 'f', 1) + " " +
        setBundle.general.value("currency").toString();

    ui->lbPeriodIncomeTotal->setText(periodTot);
}

void MainWindow::incomeOverallTotal(double tot){
    QString periodTot =
        QString::number(tot, 'f', 1) + " " +
        setBundle.general.value("currency").toString() + " tot";
    ui->lbIncomeOverallTotal->setText(periodTot);
}

void MainWindow::periodBalance(double tot){
    QString periodTot =
        QString::number(tot, 'f', 1) + " " +
        setBundle.general.value("currency").toString();

    ui->lbPeriodBalance->setText(periodTot);
}

void MainWindow::balanceOverall(double tot){
    QString periodTot =
        QString::number(tot, 'f', 1) + " " +
        setBundle.general.value("currency").toString() + " tot";
    ui->lbBalanceOverall->setText(periodTot);
}

QString MainWindow::getCurrentCat(){
    return ui->cbCategory->currentText();
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
    this->record.date = ui->date->date().toString("yyyy-MM-dd");
    this->record.currency = ui->cbCurrency->currentText();
    this->record.reg = !ui->chboxReg->isChecked();
    this->record.rate = ui->lbRate->text().toDouble();
    this->record.finalAmnt = this->record.amount*ui->lbRate->text().toDouble();

    emit newRecordAvailable(this->record);
    emit requestAVG();

    qDebug("MainW: Submit button pressed");
    ui->pB_Submit->setEnabled(false);
    ui->leAmount->clear();
    ui->cbNonRegCat->clear();
}

void MainWindow::populateLists(SettingsBundle const &settings){
    this->setBundle = settings;
    QStringList regC;
    foreach (auto i, this->setBundle.regCat) {
        regC.append(i.toStringList());
    }
    ui->cbCategory->addItems(regC);

    ui->cbCurrency->addItems(this->setBundle.exchRates.keys());
    ui->cbCurrency->setCurrentText(this->setBundle.general["currency"].toString());
    QStringList nonR;
    foreach (auto i, this->setBundle.nonRegCat) {
        nonR.append(i.toStringList());
    }
    ui->cbNonRegCat->addItems(nonR);
    ui->lbRate->setText(this->setBundle.exchRates.value( ui->cbCurrency->currentText()).toString());
    ui->lbThisPeriodName->setText("This " + this->setBundle.general["period"].toString());
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
    ui->lbFinalAmount->setText("final amount");
    ++rec;
    }
    //hide column containing rowid. It will be used to access record for edit/delete
    ui->tableWidget->hideColumn(ui->tableWidget->columnCount() - 1);
    }
}

void MainWindow::on_chboxReg_stateChanged(int arg1)
{
    if (ui->chboxReg->checkState()){
        ui->cbNonRegCat->setEnabled(true);
        ui->cbNonRegCat->setEditable(true);
        ui->cbCategory->setVisible(false);
        ui->lbCategory->setVisible(false);
        ui->lbCatAvg->setVisible(false);
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
        double rt = this->setBundle.exchRates[ui->cbCurrency->currentText()].toDouble();
        ui->lbFinalAmount->setText(QString::number(this->record.amount*rt));
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
    double rt = this->setBundle.exchRates[ui->cbCurrency->currentText()].toDouble();
    ui->lbFinalAmount->setText(QString::number(this->record.amount*rt));

}

void MainWindow::on_pbEditCurrency_clicked()
{
    emit editCurrencyPBclicked(this->setBundle);
}

void MainWindow::on_cbCategory_currentTextChanged(const QString &arg1)
{
    emit requestAVG();
}

void MainWindow::on_pbEditRecord_clicked()
{
    int64_t rowid = ui->tableWidget->item(ui->tableWidget->currentRow(),ui->tableWidget->columnCount() - 1)->text().toInt();
    qDebug() << "Edit record rowid is: " << rowid;

    emit recordByID(rowid, "Main");
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    ui->pbEditRecord->setEnabled(true);
    ui->pb_DeleteRecord->setEnabled(true);
}

void MainWindow::on_pb_ShowMoreExpenses_clicked()
{
    emit getAllExpenses();
}

void MainWindow::on_pb_DeleteRecord_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete record?", "Delete record? This cannot be undone!",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        int64_t rowid = ui->tableWidget->item(ui->tableWidget->currentRow(),ui->tableWidget->columnCount() - 1)->text().toInt();
        qDebug() << "Edit record rowid is: " << rowid;
        emit deleteRecord(rowid, "Main");
    } else {
        qDebug() << "Delete Record canceled by user";
    }
}

