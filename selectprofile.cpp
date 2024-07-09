#include "selectprofile.h"
#include "ui_selectprofile.h"

SelectProfile::SelectProfile(QStringList const & profiles, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SelectProfile)
{
    ui->setupUi(this);
    ui->cbSelectProfile->addItems(profiles);
    //disable default close cross in the title bar
    this->setWindowFlags(Qt::Window |
                         Qt::CustomizeWindowHint |
                         Qt::WindowTitleHint|
                         Qt::WindowSystemMenuHint);
}

SelectProfile::~SelectProfile()
{
    delete ui;
}

void SelectProfile::on_pbSelectOK_clicked()
{
    if (ui->cbSelectProfile->currentIndex() == -1){
        QMessageBox warn;
        warn.setText("Please select profile from the list!");
        warn.setIcon(QMessageBox::Warning);
        warn.setWindowTitle("Error");
        warn.exec();
    }
    else{
        emit selectProfile(ui->cbSelectProfile->currentText());
        this->close();
    }
}

