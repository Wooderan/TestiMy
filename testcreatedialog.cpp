#include "testcreatedialog.h"
#include "ui_testcreatedialog.h"

TestCreateDialog::TestCreateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestCreateDialog)
{
    ui->setupUi(this);
}

TestCreateDialog::~TestCreateDialog()
{
    delete ui;
}
