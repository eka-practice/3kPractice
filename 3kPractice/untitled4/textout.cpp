#include "textout.h"



TextOut::TextOut(QObject *parent) : QObject(parent)
{
    QString er;
    maxRange(&maxR);
    er=rasprRange();
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\Qt\\BasaSQ.db");
    db.open();
    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT * FROM RTR");
    while (query.next()){
        QString radio = query.value(2).toString(),str="",num=query.value(0).toString();
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
    query.exec("SELECT Vid FROM Object");
    while (query.next()){
    QString vid = query.value(0).toString();
    qDebug()<<vid;
    }
    db.close();
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

void TextOut::perehodPoisk(int a, int nowTime)
{
    for (int i = 0; i < nomerVarianta.size(); ++i) {
        if ((nomerVarianta[i].toInt()-1)==a){
            if ((nowKanalTime[i]+intervalSvyazi[i])<=nowTime){
                nowKanalVariant[i]++;
                int qw=0;
                for (int j = 0; j < radioData[i].length(); ++j) {

                    if(radioData[i][j]==','){
                        qw++;
                    }
                }
                qw++;
                if (qw< nowKanalVariant[i]){
                    nowKanalVariant[i]=1;
                }

            nowKanalTime[i]+=intervalSvyazi[i];
            }

            QString str=nomerVarianta[i]+'|';
            int tmp=1;
                for (int j = 0; j < radioData[i].length(); ++j) {

                    if ((tmp==nowKanalVariant[i])&&(radioData[i][j]!=',')){
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
                if((nowKanalTime[i]+intervalSvyazi[i])>nowTime){
                if((boolSvaz[tmp]=="slategray")||(boolSvaz[tmp]=="red")){
                    changeString(&boolSvaz[tmp],"С");
                }else if((boolSvaz[tmp]=="green")||(boolSvaz[tmp]=="yellow")){
                    nowKanalTime[i]++;
                }
                }
            }

    }
}

bool TextOut::dalSvaz(int a, int b)
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
    db.setDatabaseName("D:\\Qt\\BasaSQ.db");
    db.open();
    //Осуществляем запрос
    QSqlQuery query;
    int i=0;
    query.exec("SELECT Vid FROM Object");
    while (query.next()){
    QString vid = query.value(0).toString();
    if(i==a){
        return vid+".png";
    }
    i++;
    }
    db.close();
    return "1.png";
}




