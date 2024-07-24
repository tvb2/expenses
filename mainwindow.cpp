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
    qDebug("MainW: Submit button pressed");
}

void MainWindow::populate(QVariant const &regCat, QVariant const &nonRegCat, QStringList const &curr){
    ui->cbCategory->addItems(regCat.toStringList());
    ui->cbCurrency->addItems(curr);
    ui->cbNonRegCat->addItems(nonRegCat.toStringList());
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
    if (eval.isError())
        ui->pB_Submit->setEnabled(false);
    else
        ui->pB_Submit->setEnabled(true);
    ui->lbAmountEntered->setText("resulting value: " + eval.toString());
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

