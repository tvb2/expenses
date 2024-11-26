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
#include "Periods.h"
#include "editrecord.h"
#include "allexpenses.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void catAVG(double avg);

    void periodRegTotal(double tot);

    /**
     * @brief average expenses for the default period
     * @param avg
     */
    void periodRegAVG(double avg);

    void periodNonRegTotal(double tot);

    void periodNonRegAVG(double avg);

    void periodTotal(double tot);

    void overallTotal(double tot);

    void periodIncomeTotal(double tot);

    void incomeOverallTotal(double tot);

    void periodBalance(double tot);

    void balanceOverall(double tot);

    void editRecord(Record &rec);

    QString getCurrentCat();

public slots:
    /**
     * populate drop-down lists
     */
    void populateLists(SettingsBundle const &settings);

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

    void on_cbCategory_currentTextChanged(const QString &arg1);

    void on_pbEditRecord_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_pb_ShowMoreExpenses_clicked();

signals:
    void newRecordAvailable(Record const &record);

    void editCurrencyPBclicked(SettingsBundle const &bundle);

    void requestAVG();

    void recordByID(int64_t rowid);

    void getAllExpenses();

private:
    Ui::MainWindow *ui;
    Record record;
    SettingsBundle setBundle;
};

#endif // MAINWINDOW_H
