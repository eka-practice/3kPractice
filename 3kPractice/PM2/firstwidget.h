#ifndef FIRSTWIDGET_H
#define FIRSTWIDGET_H
//Класс для создания диаграмм
#include <QWidget>

namespace Ui {
class FirstWidget;
}

class FirstWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FirstWidget(QWidget *parent = nullptr);
    ~FirstWidget();

private:
    Ui::FirstWidget *ui;
};

#endif // FIRSTWIDGET_H
