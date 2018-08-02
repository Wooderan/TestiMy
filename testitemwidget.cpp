#include "testitemwidget.h"

#include <QLabel>
#include <QRadioButton>

TestItemWidget::TestItemWidget(const TestItem &_item, QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QVBoxLayout(this);
    QLabel *question = new QLabel(_item.getQuestion(), dynamic_cast<QWidget*>(mainLayout));
    question->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    question->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    mainLayout->addWidget(question);

    QGridLayout *subLayout = new QGridLayout(dynamic_cast<QWidget*>(mainLayout));
    fill_subLayout(subLayout, _item);
    mainLayout->addLayout(subLayout);
}

QString TestItemWidget::getCorrect_variant() const
{
    return correct_variant;
}

void TestItemWidget::fill_subLayout(QGridLayout *_layout, const TestItem &_item)
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
