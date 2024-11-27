#include "editrecord.h"
#include "ui_editrecord.h"

EditRecord::EditRecord(Record &rec, SettingsBundle const &settings, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditRecord)
    , record (rec)
    , setBundle(settings)
{
    ui->setupUi(this);
    ui->leAmount->setValidator(new Validator);
    ui->date->setMaximumDate(QDate::currentDate());

}

EditRecord::~EditRecord()
{
    delete ui;
}

void EditRecord::on_pbOK_clicked()
{

    this->record.date = ui->date->date().toString("yyyy-MM-dd");
    this->record.cat= ui->cbCategory->currentText();
    this->record.currency = ui->cbCurrency->currentText();
    this->record.amount = ui->leAmount->text().toDouble();
    QString currency = ui->cbCurrency->currentText();
    QString rt = this->setBundle.exchRates.value(currency).toString();
    this->record.rate = this->setBundle.exchRates.value(ui->cbCurrency->currentText()).toDouble();
    this->record.finalAmnt = this->record.amount*this->record.rate;

    // qDebug("MainW: Submit button pressed");
    // ui->pB_Submit->setEnabled(false);
    // ui->leAmount->clear();
    // ui->cbNonRegCat->clear();
    this->close();
    // emit closeWindow();
}

void EditRecord::on_pbCancel_clicked()
{
    this->success = false;
    this->close();
}

void EditRecord::populate(){

    QStringList regC;
    foreach (auto i, this->setBundle.regCat) {
        regC.append(i.toStringList());
    }
    if (!regC.contains(this->record.cat)){
        regC.append(this->record.cat);
    }
    ui->cbCategory->addItems(regC);
    ui->cbCategory->setCurrentText(this->record.cat);
    qDebug() << "EditRecord::populate. category: " << ui->cbCategory->currentText();

    QStringList exchR;
    for (auto i = this->setBundle.exchRates.begin(); i != this->setBundle.exchRates.end(); ++i) {
        exchR.append(i.key());
    }
    ui->cbCurrency->addItems(exchR);
    qDebug() << "EditRecord::populate. currency: " << ui->cbCurrency->currentText();

    if (ui->cbCurrency->findText(this->record.currency))
        ui->cbCurrency->setCurrentText(this->record.currency);
    else
        qDebug() << "EditRecord::populate: no currency matched";
    QDate date = QDate::fromString(this->record.date,"yyyy-MM-dd");
    ui->date->setDate(date);

    if (ui->cbCategory->findText(this->record.cat))
        ui->cbCategory->setCurrentText(this->record.cat);
    else
        qDebug() << "EditRecord::populate: no category matched";

    ui->leAmount->setText(QString::number(this->record.amount));

    double finalAmount = this->record.amount*this->record.rate;
    ui->lbFinalAmount->setText(QString::number(finalAmount, 'f', 1));

    this->id = this->record.id;
}

bool EditRecord::updateRecord(){
    populate();
    return true;
}

void EditRecord::on_cbCurrency_currentTextChanged(const QString &arg1)
{
    double rt = this->setBundle.exchRates.value(arg1).toDouble();
    ui->lbFinalAmount->setText(QString::number(this->record.amount*rt, 'f', 1));
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
        double rt = this->setBundle.exchRates.value(ui->cbCurrency->currentText()).toDouble();
        ui->lbFinalAmount->setText(QString::number(this->record.amount*rt, 'f', 1));
    }
}

void EditRecord::on_cbCategory_currentTextChanged(const QString &arg1)
{
    if (!this->setBundle.regCat.contains(ui->cbCategory->currentText())){
        ui->cbCategory->setEditable(true);
        this->record.reg = false;
    }
    else{
        ui->cbCategory->setEditable(false);
        this->record.reg = true;
    }
}

