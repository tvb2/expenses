#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cbCategory->setEditable(true);
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

void MainWindow::populate(QVariant const &cat, QStringList const &curr){
    ui->cbCategory->addItems(cat.toStringList());
    ui->cbCurrency->addItems(curr);
}
