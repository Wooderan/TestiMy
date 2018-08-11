#ifndef TESTITEMWIDGET2_H
#define TESTITEMWIDGET2_H

#include "testitem.h"

#include <QVBoxLayout>
#include <QWidget>

namespace Ui {
class TestItemWidget2;
}

class TestItemWidget2 : public QWidget
{
    Q_OBJECT
private:
    QString correct_variant;
    void fill_subLayout(QGridLayout *_layout, const TestItem &_item);
public:
    explicit TestItemWidget2(const TestItem& _item, QWidget *parent = nullptr);
    ~TestItemWidget2();

    QString getCorrect_variant() const;

private:
    Ui::TestItemWidget2 *ui;
};

#endif // TESTITEMWIDGET2_H
