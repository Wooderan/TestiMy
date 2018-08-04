#ifndef CREATEACCOUNTFORM_H
#define CREATEACCOUNTFORM_H

#include <QWidget>

namespace Ui {
class CreateAccountForm;
}

class CreateAccountForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateAccountForm(QWidget *parent = nullptr);
    ~CreateAccountForm();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::CreateAccountForm *ui;
};

#endif // CREATEACCOUNTFORM_H
