#include "accountsstatsdialog.h"
#include "ui_accountsstatsdialog.h"
#include "treemodel.h"

AccountsStatsDialog::AccountsStatsDialog(const Account &_acc, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountsStatsDialog)
{
    ui->setupUi(this);
    TreeModel *model = new TreeModel(this, &_acc);
    ui->treeView->setModel(model);
    ui->treeView->setIconSize(QSize(50,50));
    ui->treeView->setAlternatingRowColors(true);
    ui->treeView->header()->setSectionResizeMode(QHeaderView::Stretch);

    ui->label->setText(QString("%1\n"
                               "Name:%2\n"
                               "Adress:%3\n"
                               "Phone:%4")
                                .arg(Account::RoleStr[_acc.getPermission()])
                                .arg(_acc.getName())
                                .arg(_acc.getAdress())
                                .arg(_acc.getPhone_number()));
}

AccountsStatsDialog::~AccountsStatsDialog()
{
    delete ui;
}
