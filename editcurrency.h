#ifndef EDITCURRENCY_H
#define EDITCURRENCY_H

#include <QDialog>
#include <QJSEngine>
#include "settingsbundle.h"
#include "validator.h"

namespace Ui {
class EditCurrency;
}

class EditCurrency : public QDialog
{
    Q_OBJECT

public:
    explicit EditCurrency(QWidget *parent = nullptr);
    ~EditCurrency();

    /**
     * populate drop-down lists
     */
    void populate(SettingsBundle const &settings);

private slots:
    void on_cbCurrency_currentTextChanged(const QString &arg1);

    void on_leRate_textChanged(const QString &arg1);

private:
    Ui::EditCurrency *ui;
    SettingsBundle bndl;
};

#endif // EDITCURRENCY_H
