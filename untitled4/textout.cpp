#include "textout.h"



TextOut::TextOut(QObject *parent) : QObject(parent)
{
    QString er;
    maxRange(&maxR);
    er=rasprRange();
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("BasaSQ.db");
    db.open();
    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT * FROM RTR");
    while (query.next()){
        QString radio = query.value(2).toString(),str="",num=query.value(0).toString();
        nowKanalsVariants.append(query.value(3).toString());
        nowKanalsTimes.append("");
        for (int i = 0; i < nowKanalsVariants[nowKanalsVariants.size()-1].length(); ++i) {
            if(nowKanalsVariants[nowKanalsVariants.size()-1][i]==','){
                nowKanalsTimes[nowKanalsVariants.size()-1]+="0,";
            }
        }
        nowKanalsTimes[nowKanalsVariants.size()-1]+="0";
        radioData.append(radio);
        intervalSvyazi.append(10);
        nomerVarianta.append(num);
        nowKanalTime.append(0);
        nowKanalVariant.append(1);
        for (int i = 0; i < radio.length(); ++i) {
            if (radio[i]!=','){
                str+=radio[i];
            } else if(radio[i]==','){
                svaz.append(num+'|'+str);
                str="";
            }
        }
        svaz.append(num+'|'+str);

    }
    for (int i = 0; i < svaz.size(); ++i) {
        boolSvaz.append("slategray");
    }


}
int TextOut::getSomeProperty()const
{
    return kol;
}

int TextOut::getMaxRProperty() const
{
    return maxR;
}

void TextOut::changeBool(bool *t)//смена булевых значений
{
    *t=!(*t);
}
void TextOut::setSomeProperty(const int &i)
{
    kol = i;
}

void TextOut::setMaxRProperty(const int &i)
{
    maxR = i;
}

void TextOut::changeString(QString *s, QString er)//функция меняющая цвет в векторе
{
    if (er=="НС"){
        *s="yellow";
    } else if (er=="НУС") {
        *s="red";
    } else if (er=="УС") {
        *s="green";
    } else if(er=="С"){
        *s="blue";
    } else {
        *s="slategray";
    }
}

void TextOut::sortMax(int *a, int *b)
{
    if (*a<*b){
        int tmp=*b;
        *b=*a;
        *a=tmp;
    }
}

void TextOut::perehodPoisk(int a, int nowTime)//осуществление перехода поиска у передатчиков
{
    for (int i = 0; i < nomerVarianta.size(); ++i) {//делаем проход по всем доступным вариантам
        if ((nomerVarianta[i].toInt()-1)==a){//если мы считали нужный нам вариант продолжаем действия
            int schetSinh=0;//счётчик кол-ва элементов для вектора nowSinh
            QVector<int> nowSinh;//вектор в который поместим куда смотрит канал в данный момент
            nowSinh.append(0);//добавляем сразу элемент туда
            for (int j = 0; j < nowKanalsVariants[i].length(); ++j) {//цикл в котором помещаем данные из nowKanalsVariants в nowSinh
                if (nowKanalsVariants[i][j]!=','){
                    nowSinh[schetSinh]*=10;
                    QString strTmp=""+nowKanalsVariants[i][j];
                    nowSinh[schetSinh]+=strTmp.toInt();
                } else if (nowKanalsVariants[i][j]==',') {
                    nowSinh.append(0);
                    schetSinh++;
                }

            }
            /**/
            int schetKolTimer=0;//счётчик кол-ва элементов для вектора nowSinh
            QVector<int> nowTimer;//вектор в который поместим куда смотрит канал в данный момент
            nowTimer.append(0);//добавляем сразу элемент туда
            for (int j = 0; j < nowKanalsTimes[i].length(); ++j) {//цикл в котором помещаем данные из nowKanalsVariants в nowSinh
                if (nowKanalsTimes[i][j]!=','){
                    nowTimer[schetKolTimer]*=10;
                    QString strTmp=""+nowKanalsTimes[i][j];
                    nowTimer[schetKolTimer]+=strTmp.toInt();
                } else if (nowKanalsTimes[i][j]==',') {
                    nowTimer.append(0);
                    schetKolTimer++;
                }

            }
            /**/

            for (int y = 0; y < nowSinh.size(); ++y) {//проходим по всем каналам которые есть
                if ((nowTimer[y]+intervalSvyazi[i])<=nowTime){//проверяем стоит ли сейчас переместить поиск на другой вариант
                    nowSinh[y]++;//если это произошло прибавляем в текущем канале смещение куда стоит смотреть
                    int qw=0;//счётчик кол-ва радиоданных
                    for (int j = 0; j < radioData[i].length(); ++j) {//проходимся по радиоданным текущего варианта
                        if(radioData[i][j]==','){
                            qw++;
                        }
                    }
                    qw++;//прибавляем к кол-ву 1 из-за того что запятых всегда на 1 меньше чем радиоданных
                        if (qw< nowSinh[y]){//если мы зашли за большее кол-во радиоданных чем есть
                            nowSinh[y]=1;//возвращаем в 1
                        }

                nowTimer[y]+=intervalSvyazi[i];
                }
                QString str=nomerVarianta[i]+'|';
                int tmp=1;
                    for (int j = 0; j < radioData[i].length(); ++j) {
                        if ((tmp==nowSinh[y])&&(radioData[i][j]!=',')){
                            str+=radioData[i][j];
                        }
                        if(radioData[i][j]==','){
                            tmp++;
                        }

                    }
                    for (int j = 0; j <svaz.size() ; ++j) {
                        if (str==svaz[j]){

                            tmp=j;
                        }
                    }
                    if((nowTimer[y]+intervalSvyazi[i])>nowTime){
                        if((boolSvaz[tmp]=="slategray")||(boolSvaz[tmp]=="red")){
                            changeString(&boolSvaz[tmp],"С");
                        }else if((boolSvaz[tmp]=="green")||(boolSvaz[tmp]=="yellow")){
                            nowTimer[y]++;
                        }
                    }

                }
            nowKanalsTimes[i]="";
            nowKanalsVariants[i]="";
            for (int k = 0; k < nowTimer.size(); ++k) {
                if ((nowTimer.size()-1)!=k){
                nowKanalsTimes[i]+=QString::number(nowTimer[k])+',';
                nowKanalsVariants[i]+=QString::number(nowSinh[k])+',';}
                else {
                    nowKanalsTimes[i]+=QString::number(nowTimer[k]);
                    nowKanalsVariants[i]+=QString::number(nowSinh[k]);
                }
            }
            qDebug()<<nowKanalsTimes[i]<<nowKanalsVariants[i];
            }

    }

}

bool TextOut::dalSvaz(int a, int b)//функция определяющая находится ли введённые РТР в дальности рангов более чем на один
{
    QString s=rasprRange();
    sortMax(&a,&b);
    int obshSum=0;
    int kolu=0;
    int i=0;
    bool flagN=false;
    QString str="";
    while ((obshSum)<=a+1){
        if ((obshSum)==a+1){
            obshSum++;
        }
        if((s[i]!=' ')&&(flagN))
        {
            str+=s[i];
        }

        if (s[i]==' '){
            if (flagN){
                obshSum+=str.toInt();
                if ((obshSum>b) &&(obshSum<=a)){
                    kolu++;
                }
                str="";
            }
            flagN=!flagN;
        }
        i++;
    }
    if (kolu>1){
        return true;}
    else {
        return false;
    }
}

QString TextOut::sendColor(int a, int b)//получение из вектора нужного цвета
{
    QString str1=QString::number(a+1)+'|'+QString::number(b+1);
    for (int i=0;i<svaz.size();i++){
        if (str1==svaz[i]){
            return boolSvaz[i];
        }
    }
    return "-1";
}



void TextOut::getColor(int a, int b,QString s)//изменение цвета нужной связи
{
    QString str1=QString::number(a+1)+'|'+QString::number(b+1);
    for (int i=0;i<svaz.size();i++){
        if (str1==svaz[i]){
            changeString(&boolSvaz[i],s);
        }
    }
}



QString TextOut::readFile(int t)//считывание нужной строки файла
{
    int i=0;
    QFile file(":/txt/input.txt");
        if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
        {

            while(!file.atEnd()){
                    QString s=file.readLine();
                if (t==i){
                    return s;
                }
                i++;
            }
        }
        return "-1";
}



bool TextOut::isSvaz(int a, int b)//проверка имеется ли связь между запрошенными объектами
{
    QString str1=QString::number(a+1)+'|'+QString::number(b+1);
    for (int i=0;i<svaz.size();i++){
        if (str1==svaz[i]){
            return true;
        }
    }
    return false;
}



void TextOut::maxRange(int *t)//функция определения максимального ранга
{
    int maxi=0;
    QFile file(":/txt/range.txt");
        if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
        {

            while(!file.atEnd()){
                    QString s=file.readLine(),str="";
                    int i=0;
                    bool flag=false;
                    while (s[i]!='\0'){
                        if (flag){
                            str+=s[i];
                        }
                        if (s[i]==' '){
                            flag=true;
                        }
                        i++;
                    }
                    if (str.toInt()>maxi){
                        maxi=str.toInt();
                    }
            }
        }
        *t=maxi+1;
}

QString TextOut::rasprRange()//Функция просматривающая как распределяются ранги
{
    int ar[maxR];
    for (int i = 0; i < maxR; ++i) {
        ar[i]=0;
    }
    QFile file(":/txt/range.txt");
        if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
        {
            while(!file.atEnd()){
                QString s=file.readLine(),str="";
                int i=0;
                bool flag=false;
                while (s[i]!='\0'){
                    if (flag){
                        str+=s[i];
                    }
                    if (s[i]==' '){
                        flag=true;
                    }
                    i++;
                }
                ar[str.toInt()]++;

        }
}
        QString itog="";
        for (int i = 0; i < maxR; ++i) {
            itog+=QString::number(i)+' '+QString::number(ar[i])+' ';
        }
        itog+='.';

        return itog;
}

int TextOut::maxKolRange()
{
    int ar[maxR];
    int maxt=0;
    for (int i = 0; i < maxR; ++i) {
        ar[i]=0;
    }
    QFile file(":/txt/range.txt");
        if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
        {
            while(!file.atEnd()){
                QString s=file.readLine(),str="";
                int i=0;
                bool flag=false;
                while (s[i]!='\0'){
                    if (flag){
                        str+=s[i];
                    }
                    if (s[i]==' '){
                        flag=true;
                    }
                    i++;
                }
                ar[str.toInt()]++;

        }
}
        QString itog="";
        for (int i = 0; i < maxR; ++i) {
            if (ar[i]>maxt){
                maxt=ar[i];
            }
        }
        return maxt;
}

int TextOut::kolAll()//количество всех РТР приёмников и источников
{
    int sumAll=0;
    int ar[maxR];
    for (int i = 0; i < maxR; ++i) {
        ar[i]=0;
    }
    QFile file(":/txt/range.txt");
        if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
        {
            while(!file.atEnd()){
                QString s=file.readLine(),str="";
                int i=0;
                bool flag=false;
                while (s[i]!='\0'){
                    if (flag){
                        str+=s[i];
                    }
                    if (s[i]==' '){
                        flag=true;
                    }
                    i++;
                }
                ar[str.toInt()]++;

        }
}
        QString itog="";
        for (int i = 0; i < maxR; ++i) {
            sumAll+=ar[i];
        }
        return sumAll;
}

QString TextOut::vidVariant(int a)
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("BasaSQ.db");
    db.open();
    //Осуществляем запрос
    QSqlQuery query;
    int i=0;
    query.exec("SELECT Vid FROM Object");
    while (query.next()){
    QString vid = query.value(0).toString();
    if(i==a){
        db.close();
        return vid+".png";
    }
    i++;
    }
    db.close();
    return "1.png";
}

int TextOut::timeCondition(int a)
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("BasaSQ.db");
    db.open();
    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT * FROM conditions");
    int i=0,tmp=0;
    while (query.next()){
    QString numCon = query.value(0).toString();
    QString timeCon = query.value(1).toString();
    if(i==a){
        db.close();
        return timeCon.toInt();
    }
    i++;
    tmp=timeCon.toInt();
    }
    db.close();
    return tmp+20;
}

int TextOut::kolCon()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("BasaSQ.db");
    db.open();
    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT * FROM conditions");
    int i=0;
    while (query.next()){
    QString numCon = query.value(0).toString();
    QString timeCon = query.value(1).toString();
    i++;
    }
    db.close();
    return i;
}

int TextOut::maxConTime()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("BasaSQ.db");
    db.open();
    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT * FROM conditions");
    int i=0;
    while (query.next()){
    QString numCon = query.value(0).toString();
    QString timeCon = query.value(1).toString();
    i=timeCon.toInt();
    }
    db.close();
    return i+20;
}




