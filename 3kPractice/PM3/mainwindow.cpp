#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase db; //Подключение базы данных
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("DB.db");
    db.open();
    for (i=0; i<10; i++){
        ists[i]=-1;
        ptps[i].typ="Получатель";
        ptps[i].tekn0=0;
         ptps[i].posmotr=false;
        for (j=0; j<10; j++){
            puti[i][j]=0;
        }
    }
    ptps[0].typ="Источник";
    ists[0]=1;
    tektime=0;
    istkolvo=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() //Очистка
{
    ui->textEdit->clear();
}

void MainWindow::on_pushButton_2_clicked()
{
    QSqlQuery query; //Создане запроса
    query.exec("SELECT * FROM Objects");
    ui->textEdit->clear();
    QString str="";
    while (query.next()){
        str=query.value(0).toString()+" ";
        str+=query.value(1).toString()+" ";
        str+=query.value(2).toString()+" ";
        str+=query.value(3).toString()+" ";
        str+=query.value(4).toString()+" ";
        str+=query.value(5).toString()+" ";
        str+=query.value(6).toString()+" ";
        str+=query.value(7).toString()+" ";
        str+=query.value(8).toString()+" ";
        str+=query.value(9).toString()+" ";
        str+=query.value(10).toString();
        ui->textEdit->insertPlainText(str+"\n");
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QSqlQuery query; //Создане запроса
    query.exec("SELECT * FROM Svaz");
    ui->textEdit->clear();
    QString str="";
    while (query.next()){
        str=query.value(0).toString()+" ";
        str+=query.value(1).toString()+" ";
        str+=query.value(2).toString()+" ";
        str+=query.value(3).toString();
        ui->textEdit->insertPlainText(str+"\n");
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    QSqlQuery query; //Создане запроса
    query.exec("SELECT * FROM Other");
    ui->textEdit->clear();
    QString str="";
    while (query.next()){
        str=query.value(0).toString();
        ui->textEdit->insertPlainText(str+"\n");
    }
}

void MainWindow::on_pushButton_5_clicked() //Считывание с базы
{
    QSqlQuery query; //Создане запроса
    query.exec("SELECT * FROM Other");
    while (query.next()){
         kolvo=(query.value(0).toString()).toInt();
    }

    QSqlQuery query2; //Создане запроса
    query2.exec("SELECT * FROM Objects");
    i=0;
    while (query2.next()){
        ptps[i].name=query2.value(1).toString();
        ptps[i].time=(query2.value(4).toString()).toInt();
        ptps[i].n0=(query2.value(5).toString()).toInt();
        ptps[i].range=(query2.value(6).toString()).toInt();
        ptps[i].t_zadershka=(query2.value(8).toString()).toInt();
        ptps[i].pyc_veroyatn=(query2.value(9).toString()).toFloat();
        ptps[i].tis=(query2.value(10).toString()).toInt();
        i++;
    }

    QSqlQuery query3; //Создане запроса
    query3.exec("SELECT * FROM Svaz");
    ptps[0].kolvo_n=-1;
    i=1;
    QString str="";
    while (query3.next()){
        k=0;
        j=0;
        ptps[i].kolvo_n=(query3.value(3).toString()).toInt();
        str=query3.value(2).toString()+" ";
        while (k<ptps[i].kolvo_n){
            QString chislo="";
            while (str[j]!=" "){
                chislo+=str[j];
                j++;
            }
            j++;
            ptps[i].posledovatelnost[k]=chislo.toInt();
            puti[i][chislo.toInt()]=1;
            puti[chislo.toInt()][i]=1;
            k++;
        };
        i++;
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->textEdit->clear();
    QString str="";
    for (i=0; i<kolvo+2; i++){ //Источник и получатель не входят в РТР, поэтому +2 для вывода
         ui->textEdit->insertPlainText("Название объекта: "+ptps[i].name+"\n");
         ui->textEdit->insertPlainText("Тип: "+ptps[i].typ+"\n");
         //ui->textEdit->insertPlainText("Время отключения: "+QString::number(ptps[i].time)+"\n");
         ui->textEdit->insertPlainText("Начальные р/д: "+QString::number(ptps[i].n0)+"\n");
         ui->textEdit->insertPlainText("Ранг: "+QString::number(ptps[i].range)+"\n");
         ui->textEdit->insertPlainText("Количество связей: "+QString::number(ptps[i].kolvo_n)+"\n");
         str="";
         for (j=0; j<ptps[i].kolvo_n; j++){
             str+=QString::number(ptps[i].posledovatelnost[j])+" ";
         }
         ui->textEdit->insertPlainText("Связи: "+str+"\n");
         ui->textEdit->insertPlainText("Задержка начала ретрансляции: "+QString::number(ptps[i].t_zadershka)+"\n");
         ui->textEdit->insertPlainText("Время переключения р/д: "+QString::number(ptps[i].tis)+"\n");
         //ui->textEdit->insertPlainText("Вероятность синхронизации: "+QString::number(ptps[i].pyc_veroyatn)+"\n");
         ui->textEdit->insertPlainText("Время готовности к отправке: "+QString::number(ptps[i].tekn0)+"\n");
         ui->textEdit->insertPlainText("-----------------------------------------------\n");
    }
}

void MainWindow::on_pushButton_7_clicked() //Основной алгоритм
{
    tektime=0;
    ui->textEdit->clear();
    QFile file("info.txt");
    QFile file2("output.txt");
    QFile file3("Log2.txt");
    QString filestr = "";
    QString filestr2 = "";
    QString filestr3 = ""; // Для лога
    //Для 1 ранга
    //Отправка данных ПМ1
    int ptpid=-1;
    int polkolvo=0; //Кол-во получателей
    istkolvo=1; // В начале всегда 1 источник
    for (i=0; i<kolvo+2; i++){
        if ((puti[0][i]==1)&&(ptps[i].range==1)){
            polkolvo++;
        }
    }
    int polkolvo2=polkolvo;
    ui->textEdit->insertPlainText("Количество связанных РТР 1 ранга с Ист(№0): "+QString::number(polkolvo)+"\n"); //Общее
    int onerangepol = true;
    while (onerangepol==true){ //while ещё есть получатели 1 ранга
        polkolvo2=polkolvo;
        onerangepol = false;
        for (i=0; i<kolvo+2; i++){ //Проверка, есть ли получатели
            if ((ptps[i].range==1)&&(ptps[i].typ=="Получатель")){
                onerangepol = true;
                break;
            }
        }
        for (i=0; i<kolvo+2; i++){
            ptps[i].posmotr=false;
        }
        while (polkolvo>0){ //Просмотр получателей для 1 раза
            qDebug()<<polkolvo;
            ui->textEdit->insertPlainText("-----------------------------------------------\n");
            for (i=0; i<kolvo+2; i++){
                if (file.open(QIODevice::WriteOnly))
                {
                    file.close();
                }
                if ((ptps[i].typ=="Получатель")&&(ptps[i].range==1)&&(ptps[i].posmotr==false)){ //Выбираем получателя
                    ui->textEdit->insertPlainText("Получатель: "+QString::number(i)+"\n");
                    filestr = QString::number(i);
                    if (file.open(QIODevice::Append | QIODevice::Text))
                    {
                        QTextStream out(&file);
                        out << filestr << "\n";
                        file.close();
                    }
                    filestr = "";
                    ui->textEdit->insertPlainText("Источники: ");
                    for (k=0; k<kolvo+2; k++){ //Выводим все текущие источники
                        if ((ists[k]==1)&&(puti[i][k]==1)){
                            ui->textEdit->insertPlainText(QString::number(k)+" ");
                            filestr += QString::number(k)+"|";
                        }
                    }
                    ui->textEdit->insertPlainText("\n");
                    filestr.remove(filestr.length()-1, 1);
                    if (file.open(QIODevice::Append | QIODevice::Text))
                    {
                        QTextStream out(&file);
                        out << filestr << "\n";
                        file.close();
                    }
                    //Определение min времени источника
                    int minttime=999;
                    qDebug()<<"Кол-во источников: "<<istkolvo;
                    //if (istkolvo>1){
                        for (k=0; k<kolvo+2; k++){
                            //if ((ists[k]==1)&&(ptps[k].tekn0<=minttime)&&(puti[i][k]==1)){
                            if ((ptps[k].typ=="Источник")&&(ptps[k].tekn0<=minttime)&&(puti[i][k]==1)){
                                minttime=ptps[k].tekn0;
                            }
                        }
                    //}
                    qDebug()<<"min время источника: "<<minttime;
                    ui->textEdit->insertPlainText("Текущее время: "+QString::number(minttime)+"\n");
                    tektime=minttime;
                    filestr = QString::number(minttime);
                    if (file.open(QIODevice::Append | QIODevice::Text))
                    {
                        QTextStream out(&file);
                        out << filestr << "\n";
                        file.close();
                    }
                    //Определение текущих р/д
                    int nachid=0;
                    for (j=0; j<ptps[i].kolvo_n; j++){
                        if (ptps[i].posledovatelnost[j]==ptps[i].n0){
                            nachid=j;
                            break;
                        }
                    }
                    int testtime=0;
                    while (testtime+ptps[i].tis<tektime){
                        testtime+=ptps[i].tis;
                        nachid++;
                        if (nachid>ptps[i].kolvo_n){
                            nachid=0;
                        }
                    }
                    tekrd=ptps[i].posledovatelnost[nachid];
                    filestr = QString::number(tekrd);
                    if (file.open(QIODevice::Append | QIODevice::Text))
                    {
                        QTextStream out(&file);
                        out << filestr << "\n";
                        file.close();
                    }
                    ui->textEdit->insertPlainText("Текущие р/д: "+QString::number(tekrd)+"\n");
                    ui->textEdit->insertPlainText("Время готовности к отправке Источника - Ист(№0): "+QString::number(ptps[0].tekn0)+"\n");
                    ui->textEdit->insertPlainText("-----------------------------------------------\n");
                    ptpid=i;
                    ptps[i].posmotr=true;
                    polkolvo--;
                    break;
                }
            }
            //Получение данных ПМ1
            //ptps[ptpid].tekn0=(qrand() % ((30 + 10) - 10) + 10); //((20 + 5) - 5) + 5);
            if ((file2.exists())&&(file2.open(QIODevice::ReadOnly)))
            {
                filestr2 = file2.readLine();
                file2.close();
            }
            ptps[ptpid].tekn0=filestr2.toInt();
            ui->textEdit->insertPlainText("-----------------------------------------------\n");
            ui->textEdit->insertPlainText("Время готовности к отправке Получателя - "+ptps[ptpid].name+": "+QString::number(ptps[ptpid].tekn0)+"\n");
            ui->textEdit->insertPlainText("-----------------------------------------------\n");
            bool isalone=true;
            for (i=0; i<kolvo+2; i++){ //Проверка на одиночество
                if (puti[ptpid][i]==1){
                    isalone=false;
                    break;
                }
            }
            if (isalone==true){ //Переход в источник из-за одиночества
                ptps[ptpid].typ="Источник";
                ists[ptpid]=1;
                istkolvo++;
                ptps[ptpid].tekn0+=ptps[ptpid].t_zadershka;
                qDebug()<<"Переход в источник из-за одиночества"<<ptpid;
            }
        }
        polkolvo=polkolvo2;
        int mintime=999999;
        int minid=-1;
        for (i=0; i<kolvo+2; i++){ //Вычисление, у кого min время
            if ((ptps[i].range==1)&&(ptps[i].typ=="Получатель")&&(ptps[ptpid].tekn0<mintime)){
                mintime=ptps[ptpid].tekn0;
                minid=i;
            }
        }
        if (minid!=-1){ //Переход в источник по min времени
            ptps[minid].tekn0+=ptps[minid].t_zadershka;
            ptps[minid].typ="Источник";
            polkolvo--;
            ists[minid]=1;
            istkolvo++;
            qDebug()<<"Переход в источник по min времени"<<minid;
            qDebug()<<"Время готовности: "<<ptps[minid].tekn0;
        }
    }
    //Для всех рангов !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //Получатели 2 ранга
    int h = 0; //Считаем кол-во рангов
    for (i=0; i<kolvo+2; i++){
        if (ptps[i].range>=h){
            h = ptps[i].range;
        }
    }
    qDebug()<<"Кол-во рангов: "<<h;
    //
    h+=1;
    int z=2;
    for (z=2; z<h; z++){
        polkolvo=0;
        for (i=0; i<kolvo+2; i++){
            if (ptps[i].range==z){ // !ранг
                polkolvo++;
            }
        }
        istkolvo=0; // Базовое
        //
        onerangepol = true;
        while (onerangepol==true){ //while ещё есть получатели 1 ранга
            polkolvo2=polkolvo;
            onerangepol = false;
            for (i=0; i<kolvo+2; i++){ //Проверка, есть ли получатели
                if ((ptps[i].range==z)&&(ptps[i].typ=="Получатель")){ // !ранг
                    onerangepol = true;
                    break;
                }
            }
            for (i=0; i<kolvo+2; i++){
                ptps[i].posmotr=false;
            }
            while (polkolvo>0){ //Просмотр получателей для 1 раза
                qDebug()<<polkolvo;
                ui->textEdit->insertPlainText("-----------------------------------------------\n");
                for (i=0; i<kolvo+2; i++){
                    if (file.open(QIODevice::WriteOnly))
                    {
                        file.close();
                    }
                    if ((ptps[i].typ=="Получатель")&&(ptps[i].range==z)&&(ptps[i].posmotr==false)){ //Выбираем получателя !ранг
                        ui->textEdit->insertPlainText("Получатель: "+QString::number(i)+"\n");
                        filestr = QString::number(i);
                        if (file.open(QIODevice::Append | QIODevice::Text))
                        {
                            QTextStream out(&file);
                            out << filestr << "\n";
                            file.close();
                        }
                        filestr = "";
                        ui->textEdit->insertPlainText("Источники: ");
                        istkolvo=0;
                        for (k=0; k<kolvo+2; k++){ //Выводим все текущие источники
                            if ((ists[k]==1)&&(puti[i][k]==1)){
                                ui->textEdit->insertPlainText(QString::number(k)+" ");
                                filestr += QString::number(k)+"|";
                                istkolvo++;
                            }
                        }
                        ui->textEdit->insertPlainText("\n");
                        filestr.remove(filestr.length()-1, 1);
                        if (file.open(QIODevice::Append | QIODevice::Text))
                        {
                            QTextStream out(&file);
                            out << filestr << "\n";
                            file.close();
                        }
                        //Определение min времени источника
                        int minttime=999;
                        int dopp=0;
                        qDebug()<<"Кол-во источников: "<<istkolvo;
                        //if (istkolvo>1){
                            for (k=0; k<kolvo+2; k++){
                                //if ((ists[k]==1)&&(ptps[k].tekn0<=minttime)&&(puti[i][k]==1)){
                                if ((ptps[k].typ=="Источник")&&(ptps[k].tekn0<=minttime)&&(puti[i][k]==1)){
                                    minttime=ptps[k].tekn0;
                                    dopp=k;
                                }
                            }
                        //}
                        qDebug()<<"min время источника: "<<minttime;
                        ui->textEdit->insertPlainText("Текущее время: "+QString::number(minttime)+"\n");
                        tektime=minttime;
                        filestr = QString::number(minttime);
                        if (file.open(QIODevice::Append | QIODevice::Text))
                        {
                            QTextStream out(&file);
                            out << filestr << "\n";
                            file.close();
                        }
                        //Определение текущих р/д
                        int nachid=0;
                        for (j=0; j<ptps[i].kolvo_n; j++){
                            if (ptps[i].posledovatelnost[j]==ptps[i].n0){
                                nachid=j;
                                break;
                            }
                        }
                        int testtime=0;
                        qDebug()<<"Времена: "<<testtime+ptps[i].tis<<tektime<<"\n";
                        while (testtime+ptps[i].tis<tektime){
                            testtime+=ptps[i].tis;
                            nachid++;
                            if (nachid>ptps[i].kolvo_n){
                                nachid=0;
                            }
                        }
                        tekrd=ptps[i].posledovatelnost[nachid];
                        filestr = QString::number(tekrd);
                        if (file.open(QIODevice::Append | QIODevice::Text))
                        {
                            QTextStream out(&file);
                            out << filestr << "\n";
                            file.close();
                        }
                        ui->textEdit->insertPlainText("Текущие р/д: "+QString::number(tekrd)+"\n");
                        ui->textEdit->insertPlainText("Время готовности к отправке Источника - "+ptps[dopp].name+": "+QString::number(ptps[dopp].tekn0)+"\n");
                        ui->textEdit->insertPlainText("-----------------------------------------------\n");
                        ptpid=i;
                        ptps[i].posmotr=true;
                        polkolvo--;
                        break;
                    }
                }
                //Получение данных ПМ1
                //ptps[ptpid].tekn0=(qrand() % ((30 + 10) - 10) + 10);
                if ((file2.exists())&&(file2.open(QIODevice::ReadOnly)))
                {
                    filestr2 = file2.readLine();
                    file2.close();
                }
                ptps[ptpid].tekn0=filestr2.toInt();
                ui->textEdit->insertPlainText("-----------------------------------------------\n");
                ui->textEdit->insertPlainText("Время готовности к отправке Получателя - "+ptps[ptpid].name+": "+QString::number(ptps[ptpid].tekn0)+"\n");
                ui->textEdit->insertPlainText("-----------------------------------------------\n");
                bool isalone=true;
                for (i=0; i<kolvo+2; i++){ //Проверка на одиночество
                    if (puti[ptpid][i]==1){
                        isalone=false;
                        break;
                    }
                }
                if (isalone==true){ //Переход в источник из-за одиночества
                    ptps[ptpid].typ="Источник";
                    ists[ptpid]=1;
                    istkolvo++;
                    ptps[ptpid].tekn0+=ptps[ptpid].t_zadershka;
                    qDebug()<<"Переход в источник из-за одиночества"<<ptpid;
                }
            }
            polkolvo=polkolvo2;
            int mintime=999999;
            int minid=-1;
            for (i=0; i<kolvo+2; i++){ //Вычисление, у кого min время
                if ((ptps[i].range==z)&&(ptps[i].typ=="Получатель")&&(ptps[ptpid].tekn0<mintime)){ // !ранг
                    mintime=ptps[ptpid].tekn0;
                    minid=i;
                }
            }
            if (minid!=-1){ //Переход в источник по min времени
                ptps[minid].tekn0+=ptps[minid].t_zadershka;
                ptps[minid].typ="Источник";
                polkolvo--;
                ists[minid]=1;
                istkolvo++;
                qDebug()<<"Переход в источник по min времени"<<minid;
            }
        }
    }
    //Для последнего получателя
    i=kolvo+1;
    if (file.open(QIODevice::WriteOnly))
    {
        file.close();
    }
    ui->textEdit->insertPlainText("Получатель: "+QString::number(i)+"\n");
    ui->textEdit->insertPlainText("Источники: ");
    filestr = QString::number(i);
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out << filestr << "\n";
        file.close();
    }
    filestr = "";
    for (k=0; k<kolvo+2; k++){ //Выводим все текущие источники
        if ((ists[k]==1)&&(puti[i][k]==1)){
            ui->textEdit->insertPlainText(QString::number(k)+" ");
            filestr += QString::number(k)+"|";
            istkolvo++;
        }
    }
    ui->textEdit->insertPlainText("\n");
    filestr.remove(filestr.length()-1, 1);
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out << filestr << "\n";
        file.close();
    }
    //Определение min времени источника
    int minttime=999;
    int dopp=0;
    qDebug()<<"Кол-во источников: "<<istkolvo;
    //if (istkolvo>1){
        for (k=0; k<kolvo+2; k++){
            //if ((ists[k]==1)&&(ptps[k].tekn0<=minttime)&&(puti[i][k]==1)){
            if ((ptps[k].typ=="Источник")&&(ptps[k].tekn0<=minttime)&&(puti[i][k]==1)){
                minttime=ptps[k].tekn0;
                dopp=k;
            }
        }
    //}
    qDebug()<<"min время источника: "<<minttime;
    ui->textEdit->insertPlainText("Текущее время: "+QString::number(minttime)+"\n");
    tektime=minttime;
    filestr = QString::number(minttime);
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out << filestr << "\n";
        file.close();
    }
    //Определение текущих р/д
    int nachid=0;
    for (j=0; j<ptps[i].kolvo_n; j++){
        if (ptps[i].posledovatelnost[j]==ptps[i].n0){
            nachid=j;
            break;
        }
    }
    int testtime=0;
    while (testtime+ptps[i].tis<tektime){
        testtime+=ptps[i].tis;
        nachid++;
        if (nachid>ptps[i].kolvo_n){
            nachid=0;
        }
    }
    tekrd=ptps[i].posledovatelnost[nachid];
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out << filestr << "\n";
        file.close();
    }
    ui->textEdit->insertPlainText("Текущие р/д: "+QString::number(tekrd)+"\n");
    ui->textEdit->insertPlainText("Время готовности к отправке Источника - "+ptps[dopp].name+": "+QString::number(ptps[dopp].tekn0)+"\n");
    ui->textEdit->insertPlainText("-----------------------------------------------\n");
    ptpid=i;
    //Получение данных ПМ1
    //ptps[ptpid].tekn0=(qrand() % ((30 + 10) - 10) + 10);
    if ((file2.exists())&&(file2.open(QIODevice::ReadOnly)))
    {
        filestr2 = file2.readLine();
        file2.close();
    }
    ptps[ptpid].tekn0=filestr2.toInt();
    ui->textEdit->insertPlainText("-----------------------------------------------\n");
    ui->textEdit->insertPlainText("Время готовности к отправке Получателя - "+ptps[ptpid].name+": "+QString::number(ptps[ptpid].tekn0)+"\n");
    ui->textEdit->insertPlainText("-----------------------------------------------\n");
}

void MainWindow::on_pushButton_8_clicked() //Таблица связности
{
    ui->textEdit->clear();
    QString str="";
    for (i=0; i<kolvo+2; i++){
        str="";
        for (j=0; j<kolvo+2; j++){
            str+=QString::number(puti[i][j])+" ";
        }
        ui->textEdit->insertPlainText(QString::number(i)+": "+str+"\n");
    }
}
