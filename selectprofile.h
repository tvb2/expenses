#ifndef SELECTPROFILE_H
#define SELECTPROFILE_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class SelectProfile;
}

class SelectProfile : public QDialog
{
    Q_OBJECT

public:
    explicit SelectProfile(QStringList const & profiles, QWidget *parent = nullptr);
    ~SelectProfile();

signals:
    void selectProfile(QString const & profile);

private slots:
    void on_pbSelectOK_clicked();

private:
    Ui::SelectProfile *ui;
};

#endif // SELECTPROFILE_H
