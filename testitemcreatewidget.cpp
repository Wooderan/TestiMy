#include "testitemcreatewidget.h"
#include "ui_testitemcreatewidget.h"

#include <QLineEdit>
#include <QDebug>
#include <QRadioButton>

TestItemCreateWidget::TestItemCreateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestItemCreateWidget)
{
    ui->setupUi(this);
}

TestItemCreateWidget::~TestItemCreateWidget()
{
    delete ui;
}

TestItem TestItemCreateWidget::getItem() const
{
    TestItem item;
    QObjectList list = this->children();

    for (int i = 0; i < list.count(); i++) {
        QTextEdit *question = dynamic_cast<QTextEdit*>(list.at(i));
        if (question != nullptr && question->objectName() == "text_question") {
            item.setQuestion(question->toPlainText());
        }
        MyRadioButton *rb = dynamic_cast<MyRadioButton*>(list.at(i));
        if (rb != nullptr) {
            item.addVar(rb->isChecked(), rb->respond_line()->text());
        }
    }

    return item;
}


void TestItemCreateWidget::on_addBtn_clicked()
{
    MyRadioButton *rb = new MyRadioButton(this);
    rb->setChecked(true);
    QLineEdit *le = new QLineEdit(this);
    MyPushButton *pb = new MyPushButton(this);
    QObject::connect(pb, &MyPushButton::clicked, this, &TestItemCreateWidget::deleteLine);
    pb->setText("X");
    rb->setRespond_line(le);
    pb->setRespond_line(le);
    pb->setRespond_btn(rb);
    QSizePolicy policy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    policy.setHorizontalStretch(1);
    le->setSizePolicy(policy);
    int row = ui->formVariants->rowCount();
    ui->formVariants->addWidget(rb, row, 0);
    ui->formVariants->addWidget(le, row, 1);
    ui->formVariants->addWidget(pb, row, 2);
}

void TestItemCreateWidget::deleteLine()
{
    MyPushButton* pb = dynamic_cast<MyPushButton*>(sender());
    MyRadioButton *rb = pb->respond_btn();
    QLineEdit *le = pb->respond_line();
    delete pb;
    delete rb;
    delete le;
}



MyRadioButton::MyRadioButton(QWidget *parent)
    :QRadioButton(parent)
{

}

QLineEdit *MyRadioButton::respond_line() const
{
    return m_respond_line;
}

void MyRadioButton::setRespond_line(QLineEdit *respond_line)
{
    m_respond_line = respond_line;
}

MyPushButton::MyPushButton(QWidget *parent)
    :QPushButton (parent)
{

}
