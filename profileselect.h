#ifndef PROFILESELECT_H
#define PROFILESELECT_H

#include <QWidget>
#include <QStandardPaths>
#include <QDir>


namespace Ui {
class ProfileSelect;
}

class ProfileSelect : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileSelect(QWidget *parent = nullptr);
    ~ProfileSelect();

    void getExistingProfiles();

private slots:
    void on_selectPushButton_clicked();

private:
    Ui::ProfileSelect *ui;
    QString extension = ".sqlite";
};

#endif // PROFILESELECT_H
