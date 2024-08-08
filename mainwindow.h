#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJSEngine>
#include <QDate>
#include <QVariant>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "validator.h"
#include "record.h"
#include "settingsbundle.h"

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
    void populateLists(SettingsBunlde const &settings);

    /**
     * @brief overload populate last records added
     * @param settings
     */
    void populateRecords(QVector<Record> const & lastRecords);

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

    void on_cbCurrency_currentTextChanged(const QString &arg1);

    void on_pbEditCurrency_clicked();

signals:
    void newRecordAvailable(Record const &record);

    void editCurrencyPBclicked(SettingsBunlde const &bundle);

private:
    Ui::MainWindow *ui;
    Record record;
    SettingsBunlde setBundle;
};

#endif // MAINWINDOW_H
