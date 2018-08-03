#ifndef TEXTITEMCREATEWIDGET_H
#define TEXTITEMCREATEWIDGET_H

#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QWidget>
#include <testitem.h>

namespace Ui {
class TestItemCreateWidget;
}


class MyRadioButton : public QRadioButton
{
    Q_OBJECT
    Q_PROPERTY(QLineEdit* respond_line READ respond_line WRITE setRespond_line)

public:
    MyRadioButton(QWidget *parent = nullptr);
    QLineEdit* respond_line() const;

public slots:
    void setRespond_line(QLineEdit* respond_line);



private:
    QLineEdit* m_respond_line;
};

class MyPushButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(MyRadioButton* respond_btn READ respond_btn WRITE setRespond_btn)
    Q_PROPERTY(QLineEdit* respond_line READ respond_line WRITE setRespond_line)
    MyRadioButton* m_respond_btn;

    QLineEdit* m_respond_line;

public:
    MyPushButton(QWidget *parent = nullptr);

    MyRadioButton* respond_btn() const
    {
        return m_respond_btn;
    }
    QLineEdit* respond_line() const
    {
        return m_respond_line;
    }

public slots:
    void setRespond_btn(MyRadioButton* respond_btn)
    {
        m_respond_btn = respond_btn;
    }
    void setRespond_line(QLineEdit* respond_line)
    {
        m_respond_line = respond_line;
    }
};

class TestItemCreateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TestItemCreateWidget(QWidget *parent = nullptr);
    ~TestItemCreateWidget();

    TestItem getItem() const;

private slots:
    void on_addBtn_clicked();
    void deleteLine();

private:
    Ui::TestItemCreateWidget *ui;
};

#endif // TEXTITEMCREATEWIDGET_H
