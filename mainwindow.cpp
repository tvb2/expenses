#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, ConcreteDispatch *d)
    : QMainWindow(parent)
    , dsptch(d)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::getDispatch(ConcreteDispatch *d){
    this->dsptch = d;
}

void MainWindow::on_pushButton_clicked(){
    qDebug("OK pressed");
}

/**
 * @brief submit expense info to database
 */
void MainWindow::on_pB_Submit_clicked()
{
    this->dsptch->db->addExpense("boo");
}

