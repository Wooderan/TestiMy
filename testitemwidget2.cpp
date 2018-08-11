#include "testitemwidget2.h"
#include "ui_testitemwidget2.h"

#include <QRadioButton>

TestItemWidget2::TestItemWidget2(const TestItem &_item, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestItemWidget2)
{
    ui->setupUi(this);
    ui->label->setText(_item.getQuestion());
    fill_subLayout(ui->gridLayout, _item);

    QFile file(":/qss/stylesheets/testitemwidget.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet(file.readAll());
    setStyleSheet(styleSheet);
    ensurePolished();
    file.close();
}

TestItemWidget2::~TestItemWidget2()
{
    delete ui;
}

QString TestItemWidget2::getCorrect_variant() const
{
    return correct_variant;
}

void TestItemWidget2::fill_subLayout(QGridLayout *_layout, const TestItem &_item)
{
    int col = 0,
        row = 0;
    size_t n = _item.getN();

    for (size_t i = 0; i < n; i++) {
        QString variant = _item.at(i).answer;
        if (_item.at(i).correct)
            this->correct_variant = variant;
        QRadioButton *btn = new QRadioButton(dynamic_cast<QWidget*>(_layout));

        btn->setText(variant);
        _layout->addWidget(btn,row,col++);
        if (col >= 2) {
            col = 0;
            row++;
        }
    }
}
