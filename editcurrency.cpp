#include "editcurrency.h"
#include "ui_editcurrency.h"

EditCurrency::EditCurrency(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditCurrency)
{

    ui->setupUi(this);
}

EditCurrency::~EditCurrency()
{
    delete ui;
}

void EditCurrency::populate(SettingsBunlde const & bundle){
    this->bndl = bundle;
    // qDebug() << "EditCurrency:construct. Default currency: " << bundle.general["currency"].toString();
    ui->cbCurrency->addItems(this->bndl.exchRates.keys());
    ui->leRate->setText(this->bndl.exchRates.value( ui->cbCurrency->currentText()).toString());

    ui->lbFinalAmnt->setText(QString::number(ui->leRate->text().toDouble() * 10));

    ui->lbDefCurr->setText(bundle.general["currency"].toString());
}

void EditCurrency::on_cbCurrency_currentTextChanged(const QString &arg1)
{
    ui->leRate->setText(this->bndl.exchRates.value( ui->cbCurrency->currentText()).toString());
    ui->lbFinalAmnt->setText(QString::number(ui->leRate->text().toDouble() * 10));

}

void EditCurrency::on_leRate_textChanged(const QString &arg1)
{
    QJSEngine jsEngine;

    QJSValue eval = jsEngine.evaluate(ui->leRate->displayText());
    if (eval.isError()){
        // ui->pb->setEnabled(false);
        ui->lbFinalAmnt->setText(" ... ");
    }
    else{
        // ui->pB_Submit->setEnabled(true);
        ui->lbFinalAmnt->setText("resulting value: " + eval.toString());
        ui->lbFinalAmnt->setText(QString::number(ui->leRate->text().toDouble() * 10));
    }
}

