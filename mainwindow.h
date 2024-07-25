#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJSEngine>
#include <QDate>
#include <QVariant>
#include "validator.h"
#include "record.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    /**
     * populate drop-down lists
     */
    void populate(QVariant const &regCat, QVariant const &nonRegCat, QStringList const &curr);

private slots:
    void on_pbOK_clicked();

    /**
    * submit expense info to database
    */
    void on_pB_Submit_clicked();

    void on_chboxReg_stateChanged(int arg1);

    void on_leAmount_textChanged(const QString &arg1);

    void on_chBtoday_clicked();

    void on_pbAddCat_clicked();

signals:
    void newRecordAvailable(Record const &record);

private:
    Ui::MainWindow *ui;
    Record record;
};

#endif // MAINWINDOW_H
