#include "testitemwidget2.h"
#include "ui_testitemwidget2.h"

#include <QPainter>
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

void TestItemWidget2::paintEvent(QPaintEvent *pe) {
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
};

TestItemWidget2::~TestItemWidget2()
{
    delete ui;
}

QString TestItemWidget2::getCorrect_variant() const
{
    return correct_variant;
}

char TestItemWidget2::state() const
{
    return m_state;
}

void TestItemWidget2::disableRadio()
{
    QObjectList list = this->children();
    foreach (QObject* obj, list) {
        QRadioButton* btn = dynamic_cast<QRadioButton*>(obj);
        if (btn)
            btn->setEnabled(false);
    }
}

void TestItemWidget2::setState(char state)
{
    if (m_state == state)
        return;

    m_state = state;
    emit stateChanged(m_state);
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
        QRadioButton *btn = new QRadioButton(this);

        btn->setText(variant);
        _layout->addWidget(btn,row,col++);
        if (col >= 2) {
            col = 0;
            row++;
        }
    }
}
