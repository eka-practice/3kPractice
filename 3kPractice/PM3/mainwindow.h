#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include <QDebug>
#include <QString>
#include <QFile>
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    struct ptp{
        QString name; // Название
        int time; // Время отключения
        int n0; // Начальные р/д
        int range; // Ранг
        int kolvo_n; // Количество р/д
        int posledovatelnost[10]; // Все р/д
        int t_zadershka; // Задержка начала ретранляции
        int tis; //Время переключения р/д
        float pyc_veroyatn; // Вероятность синхронизации
        //дополнительные программные, не из входных данных:
        QString typ; // Тип (источник/получатель)
        int tekn0; // Время готовности к отправке
        bool posmotr; //Посмотрели ли мы этот ртр (временная)
    };
    struct ptp ptps[10];
    int kolvo, i, j, k, tektime;
    int puti[10][10]; // Связи
    int tekrd; //Текущие р/д (временная)
    int istkolvo; //Количество источников
    int ists[10]; //Номера источников

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
