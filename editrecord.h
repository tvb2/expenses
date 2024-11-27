#ifndef EDITRECORD_H
#define EDITRECORD_H

#include <QDialog>
#include <QJSEngine>
#include "record.h"
#include "settingsbundle.h"
#include "validator.h"

namespace Ui {
class EditRecord;
}

class EditRecord : public QDialog
{
    Q_OBJECT

public:
    explicit EditRecord(Record &rec, SettingsBundle const &settings, QWidget *parent = nullptr);
    ~EditRecord();

    void populate();

    bool updateRecord();

    //let know if update was successful (true) or if it was cancelled (false)
    bool isSuccess(){
        return this->success;
    }

private slots:
    void on_pbOK_clicked();

    void on_pbCancel_clicked();

    void on_cbCurrency_currentTextChanged(const QString &arg1);

    void on_leAmount_textChanged(const QString &arg1);

signals:
    void closeWindow();
private:
    Ui::EditRecord *ui;
    int64_t id;
    Record &record;
    SettingsBundle setBundle;
    bool success = true;

};


#endif // EDITRECORD_H
