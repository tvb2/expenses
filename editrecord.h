#ifndef EDITRECORD_H
#define EDITRECORD_H

#include <QDialog>
#include <QJSEngine>
#include "record.h"
#include "settingsbundle.h"

namespace Ui {
class EditRecord;
}

class EditRecord : public QDialog
{
    Q_OBJECT

public:
    explicit EditRecord(QWidget *parent = nullptr);
    ~EditRecord();

    void populateLists(SettingsBundle const &settings);

    void populateValues(Record const &record);

private slots:
    void on_pbOK_clicked();

    void on_pbCancel_clicked();

    void on_cbCurrency_currentTextChanged(const QString &arg1);

    void on_leAmount_textChanged(const QString &arg1);

private:
    Ui::EditRecord *ui;
        int64_t id;
    Record record;
        SettingsBundle setBundle;
};

#endif // EDITRECORD_H
