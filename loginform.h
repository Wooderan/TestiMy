#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include "authorizationdialog.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(AuthorizationDialog *dialog, QWidget *parent = nullptr);
    ~LoginForm();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();


    void on_pushButton_create_clicked();

private:
    Ui::LoginForm *ui;
    AuthorizationDialog *dialog;
};

#endif // LOGINFORM_H
