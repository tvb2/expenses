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

    /**
     * @brief average expenses for the default period
     * @param avg
     */
    void periodRegAVG(double avg);

    void periodRegTotal(double tot);

    void periodNonRegTotal(double tot);

    void periodNonRegAVG(double avg);

    void periodTotal(double tot);

    void overallTotal(double tot);

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

    void on_cbCategory_currentTextChanged(const QString &arg1);

signals:
    void newRecordAvailable(Record const &record);

    void editCurrencyPBclicked(SettingsBunlde const &bundle);

    void requestAVG(const QString cat);

private:
    Ui::MainWindow *ui;
    Record record;
    SettingsBunlde setBundle;
};

#endif // MAINWINDOW_H
