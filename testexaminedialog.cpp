#include "testexaminedialog.h"
#include "ui_testexaminedialog.h"
#include "testitem.h"
#include "testitemwidget.h"

TestExamineDialog::TestExamineDialog(const Test &_test, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestExamineDialog)
{
    ui->setupUi(this);

    size_t n = _test.getN();
    QWidget* scrollWidget = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout();
    scrollWidget->setLayout(scrollLayout);

    for (size_t i = 0; i < n; i++) {
        TestItemWidget *itemWidget = new TestItemWidget(_test.at(i), scrollWidget);
        scrollLayout->addWidget(itemWidget);
    }

    ui->scrollArea->setWidget(scrollWidget);
}

TestExamineDialog::~TestExamineDialog()
{
    delete ui;
}
