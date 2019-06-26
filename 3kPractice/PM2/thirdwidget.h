#ifndef THIRDWIDGET_H
#define THIRDWIDGET_H

#include <QWidget>

namespace Ui {
class thirdwidget;
}

class thirdwidget : public QWidget
{
    Q_OBJECT

public:
    explicit thirdwidget(QWidget *parent = nullptr);
    ~thirdwidget();

private:
    Ui::thirdwidget *ui;
};

#endif // THIRDWIDGET_H
