#include "loginform.h"
#include "ui_loginform.h"
#include "authorizationstackedwidget.h"

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_buttonBox_accepted()
{

}

void LoginForm::on_buttonBox_rejected()
{
}



void LoginForm::on_pushButton_create_clicked()
{
    AuthorizationStackedWidget *widget = dynamic_cast<AuthorizationStackedWidget*>(this->parent());
    if (widget != nullptr) {
        emit widget->changeIndex(1);
    }
}
