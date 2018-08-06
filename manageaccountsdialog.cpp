#include "manageaccountsdialog.h"
#include "ui_manageaccountsdialog.h"

ManageAccountsDialog::ManageAccountsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageAccountsDialog)
{
    ui->setupUi(this);
    list = new AccountsList;
    list->Load();
    model = new AccountsListModel(list, this);
    ui->listView->setModel(model);
    ui->listView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QItemSelectionModel *selection = ui->listView->selectionModel();
    QObject::connect(selection, &QItemSelectionModel::selectionChanged, this, &ManageAccountsDialog::selection_handler);
}

ManageAccountsDialog::~ManageAccountsDialog()
{
    delete ui;
}

void ManageAccountsDialog::on_pushButton_create_clicked()
{
    model->createAccount();
}

void ManageAccountsDialog::selection_handler(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(selected)
    Q_UNUSED(deselected)
    lookup_account_results stats = model->getStatistic(ui->listView->selectionModel()->currentIndex());
    ui->label->setText(stats.formLabale());
}

void ManageAccountsDialog::on_pushButton_delete_clicked()
{
    QItemSelectionModel *selection = ui->listView->selectionModel();
    if (!selection->hasSelection()) return;
    QString login = qvariant_cast<QString>(model->data(selection->currentIndex(), Qt::DisplayRole));
    model->deleteAccount(login);
}

void ManageAccountsDialog::on_pushButton_change_clicked()
{
    QItemSelectionModel *selection = ui->listView->selectionModel();
    if (!selection->hasSelection()) return;
    QString login = qvariant_cast<QString>(model->data(selection->currentIndex(), Qt::DisplayRole));
    model->changeAccount(login);
}
