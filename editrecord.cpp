#include "editrecord.h"
#include "ui_editrecord.h"

EditRecord::EditRecord(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditRecord)
{
    ui->setupUi(this);
}

EditRecord::~EditRecord()
{
    delete ui;
}

void EditRecord::on_pbOK_clicked()
{

    this->record.date = ui->deDate->date().toString("yyyy-MM-dd");
    this->record.currency = ui->cbCurrency->currentText();
    this->record.amount = ui->leAmount->text().toDouble();
    this->record.finalAmnt = this->record.amount*this->record.rate;

    // emit newRecordAvailable(this->record);
    // emit requestAVG(this->record.cat);

    // qDebug("MainW: Submit button pressed");
    // ui->pB_Submit->setEnabled(false);
    // ui->leAmount->clear();
    // ui->cbNonRegCat->clear();
}


void EditRecord::on_pbCancel_clicked()
{
    this->close();
}

void EditRecord::populateLists(SettingsBundle const &settings){

    this->setBundle = settings;
    QStringList regC;
    foreach (auto i, settings.regCat) {
        regC.append(i.toStringList());
    }
    ui->cbCategory->addItems(regC);

    QStringList exchR;
    for (auto i = settings.exchRates.begin(); i != settings.exchRates.end(); ++i) {
        exchR.append(i.key());
    }
    ui->cbCurrency->addItems(exchR);
    // ui->cbCurrency->addItems(settings.exchRates.keys());
    QStringList nonR;
    foreach (auto i, settings.nonRegCat) {
        nonR.append(i.toStringList());
    }
    // ui->cbNonRegCat->addItems(nonR);
}

void EditRecord::populateValues(Record const &record){
    this->record = record;
    QDate date = QDate::fromString(record.date,"yyyy-MM-dd");
    ui->deDate->setDate(date);

    if (ui->cbCategory->findText(record.cat))
        ui->cbCategory->setCurrentText(record.cat);
    else
        qDebug() << "EditRecord::populateValues: no category matched";

    ui->leAmount->setText(QString::number(record.amount));

    if (ui->cbCurrency->findText(record.currency))
        ui->cbCurrency->setCurrentText(record.currency);
    else
        qDebug() << "EditRecord::populateValues: no currency matched";
    double finalAmount = record.amount*record.rate;
    ui->lbFinalAmount->setText(QString::number(finalAmount));

    this->id = record.id;
}

void EditRecord::on_cbCurrency_currentTextChanged(const QString &arg1)
{
    this->record.rate = this->setBundle.exchRates.value( ui->cbCurrency->currentText()).toString().toDouble();
    ui->lbFinalAmount->setText(QString::number(this->record.amount*this->record.rate));

}

void EditRecord::on_leAmount_textChanged(const QString &arg1)
{
    QJSEngine jsEngine;
    QJSValue eval = jsEngine.evaluate(ui->leAmount->displayText());
    if (eval.isError() || ui->leAmount->text().isEmpty()){
        ui->pbOK->setEnabled(false);
    }
    else{
        ui->pbOK->setEnabled(true);
        this->record.amount = eval.toNumber();
        this->record.finalAmnt = this->record.amount*this->record.rate;
        ui->lbFinalAmount->setText(QString::number(record.finalAmnt));
    }
}

