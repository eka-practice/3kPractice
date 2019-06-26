import QtQuick.Window 2.2
import QtQuick 2.10
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import ModuleName 1.0
import BasaGet 1.0


ApplicationWindow {
    id:window
    visible: true
    width: 840
    height: 480
    onHeightChanged: {
        linii.clearline();//при каждом изменение экрана перерисовываем линии связи
    }
    onWidthChanged: {
        linii.clearline();//при каждом изменение экрана перерисовываем линии связи
    }
    TypeName{//с помощью этого объекта переносим функции из textout.cpp
    id:obh
    kol:0
    }
    Yeah{//с помощью этого объекта переносим функции из baseout.cpp
    id: qwer
    }
    property real secHod : (aroundSh.width-4)/allTime//ход шкалы в секунду
    property int nowKol: 0
    property int rangeMax: obh.maxR//максимальное колличество рангов
    property int kolInRangeMax: obh.maxKolRange();//максимальное колличество в ранге
    property int allKol: obh.kolAll()//колличество всех РТР приёмников и источников
    property string dannie: obh.readFile(obh.kol)
    property int time: 1000 //время  цикла таймера
    property int kolTime: 0//время пройденное с начала отсчёта
    property bool flag: true //флаг для смены цвета линий
    property color lineColor: "slategray"; //цвет по умолчанию
    property int standart: {//стандарт высоты и ширины изображений приёмников
    if (window.height<window.width){
        if (rangeMax>=kolInRangeMax){
            return (window.height-200)/rangeMax;}
        else{
            return (window.height-200)/kolInRangeMax;}
    }
    else{
        if (rangeMax>=kolInRangeMax){
            return (window.width-200)/rangeMax;}
        else{
            return (window.width-200)/kolInRangeMax;}

    }
    }
    property int stanX: {//расстояние по х между приёмниками
    return (window.width-20-rangeMax*standart)/rangeMax-1;
    }
    signal changeNowKol();
    onChangeNowKol: {
        nowKol++;
    }


    function drawLines(ctx){//функция отрисовки линий связи
        var sumall=obh.kolAll();//получаем кол-во всех Источников, РТР и Получателей
        var tFlag=true;
        for (var i=0;i<sumall;i++){
            for (var j=0;j<sumall;j++){//проходимся по всем возможным связям
                if (obh.isSvaz(i,j)){
                    /**/
                    var s=obh.rasprRange();//считываем как распределились ранги
                    var obshSum=0;
                    var kolu=0;
                    var h=0;
                    var flagN=false;
                    var str="";
                    while (obshSum-1<i){
                        if((s[h]!=' ')&&(flagN))
                        {
                            str+=s[h];//считываем по одному символу количества объектов на ранге
                        }

                        if (s[h]==' '){//если пробел не считываем данные
                            if (flagN){
                                obshSum+=parseInt(str);//сколько всего объектов до этого ранга
                                kolu=parseInt(str);//объекты на ранге
                                str="";
                            }
                            flagN=!flagN;
                        }
                        h++;
                    }
                    if ((j<obshSum)&&(j>=(obshSum-kolu))){//если объекты попадают в один ранг
                        ctx.beginPath();
                        ctx.strokeStyle=obh.sendColor(i,j);
                        ctx.setLineDash([5, 3]);//задача на отрисовку пунктирных линий
                        ctx.lineWidth = 2;
                        ctx.moveTo(allSquare.itemAt(i).x+standart/2,allSquare.itemAt(i).y+standart);
                        ctx.lineTo(allSquare.itemAt(j).x+standart/2,allSquare.itemAt(j).y);
                        ctx.stroke();
                    }
                    else if(obh.dalSvaz(i,j)){//если между объектами есть 1 или более рангов
                        ctx.beginPath();
                        ctx.strokeStyle=obh.sendColor(i,j);
                        ctx.setLineDash([5, 3]);//задача на отрисовку пунктирных линий
                        ctx.lineWidth = 2;
                        if (tFlag){
                        if (i<j){//если объект i ближе
                            ctx.moveTo(allSquare.itemAt(i).x+standart/2,allSquare.itemAt(i).y);
                            ctx.bezierCurveTo(allSquare.itemAt(i).x+standart,allSquare.itemAt(i).y-standart*3,allSquare.itemAt(j).x,allSquare.itemAt(j).y-standart*3,allSquare.itemAt(j).x+standart/2,allSquare.itemAt(j).y);
                        }else{
                            ctx.moveTo(allSquare.itemAt(j).x+standart/2,allSquare.itemAt(j).y);
                            ctx.bezierCurveTo(allSquare.itemAt(j).x+standart/2,allSquare.itemAt(j).y-standart*3,allSquare.itemAt(i).x+standart/2,allSquare.itemAt(i).y-standart*3,allSquare.itemAt(i).x+standart/2,allSquare.itemAt(i).y);
                        }
                        tFlag=!tFlag;
                        }else{
                            if (i<j){//если объект i ближе
                                ctx.moveTo(allSquare.itemAt(i).x+standart/2,allSquare.itemAt(i).y+standart);
                                ctx.bezierCurveTo(allSquare.itemAt(i).x+standart,allSquare.itemAt(i).y+standart*4,allSquare.itemAt(j).x,allSquare.itemAt(j).y+standart*4,allSquare.itemAt(j).x+standart/2,allSquare.itemAt(j).y+standart);
                            }else{
                                ctx.moveTo(allSquare.itemAt(j).x+standart/2,allSquare.itemAt(j).y);
                                ctx.bezierCurveTo(allSquare.itemAt(j).x+standart/2,allSquare.itemAt(j).y+standart*4,allSquare.itemAt(i).x+standart/2,allSquare.itemAt(i).y+standart*4,allSquare.itemAt(i).x+standart/2,allSquare.itemAt(i).y+standart);
                            }
                            tFlag=!tFlag;
                        }
                        ctx.stroke();
                }
                    else{

                    ctx.beginPath();
                    ctx.strokeStyle=obh.sendColor(i,j);
                    ctx.setLineDash([5, 3]);//задача на отрисовку пунктирных линий
                    ctx.lineWidth = 2;
                        if(i>j){//если объект i дальше
                    ctx.moveTo(allSquare.itemAt(i).x,allSquare.itemAt(i).y+standart/2);
                    ctx.lineTo(allSquare.itemAt(j).x+standart,allSquare.itemAt(j).y+standart/2);}
                        if(i<j){
                    ctx.moveTo(allSquare.itemAt(i).x+standart,allSquare.itemAt(i).y+standart/2);
                    ctx.lineTo(allSquare.itemAt(j).x,allSquare.itemAt(j).y+standart/2);}
                    ctx.stroke();
                    }
                }
            }
        }
    }
    Canvas {//площадь отрисовки
        x:0
        y:0
        id: linii
        width: window.width; height: window.height
        function clearline() {//функция перерисовки пунктирных линий
                    var ctx = getContext("2d");
                    ctx.reset();
                    linii.requestPaint();
                }
        onPaint:{
            var ctx = getContext("2d");
            drawLines(ctx) ;
        }
    }
    Repeater{//Все объекты на карте
    id: allSquare
    model:allKol
    Image{
        x:{
            var s=obh.rasprRange();//считываем как распределились ранги
            var obshSum=0;
            var kolRange=0;
            var i=0;
            var flagN=false;
            var str="";
            while (s[i]!='.'){//пока не достигнут конец строки
                if((s[i]!=' ')&&(flagN))//если данный символ не пробел и он является количеством рангов
                {
                    str+=s[i];
                }

                if (s[i]==' '){
                    if (flagN){
                        obshSum+=parseInt(str);
                        str="";
                        if (index<obshSum){
                            return 10+stanX*(kolRange)+standart*(kolRange);
                        } else{
                            kolRange++;

                        }
                    }
                    flagN=!flagN;
                }
                i++;
            }

            return 10+stanX*(kolRange)+standart*(kolRange);

        }
        y:{
            var s=obh.rasprRange();
            var obshSum=0;
            var kolRange=0;
            var i=0;
            var flagN=false;
            var str="";
            while (s[i]!='.'){
                if((s[i]!=' ')&&(flagN))
                {
                    str+=s[i];
                }

                if (s[i]==' '){
                    if (flagN){
                        obshSum+=parseInt(str);
                        if (index<obshSum){
                            return (window.height-(standart+10)*(parseInt(str)))/2+(obshSum-parseInt(str)-index)*(standart+10)*-1-(obshSum-parseInt(str)-index)*20;
                        } else{
                            kolRange++;

                        }

                        str="";
                    }
                    flagN=!flagN;
                }
                i++;
            }

            return 10+stanX*(kolRange)+standart*(kolRange);


        }
        width: standart
        height: standart
        source: "qrc:/img/"+obh.vidVariant(index);//выставляем нужное изображение которое стоит в БД
    }
    }
    Repeater{//Отображение верхних табло
        id:upTablo
        model:allKol
    Text{
        x:{
            var s=obh.rasprRange();
            var obshSum=0;
            var kolRange=0;
            var i=0;
            var flagN=false;
            var str="";
            while (s[i]!='.'){
                if((s[i]!=' ')&&(flagN))
                {
                    str+=s[i];
                }

                if (s[i]==' '){
                    if (flagN){
                        obshSum+=parseInt(str);
                        str="";
                        if (index<obshSum){
                            return 10+stanX*(kolRange)+standart*(kolRange);
                        } else{
                            kolRange++;

                        }
                    }
                    flagN=!flagN;
                }
                i++;
            }

            return 10+stanX*(kolRange)+standart*(kolRange);

        }
        y:{
            var s=obh.rasprRange();
            var obshSum=0;
            var kolRange=0;
            var i=0;
            var flagN=false;
            var str="";
            while (s[i]!='.'){
                if((s[i]!=' ')&&(flagN))
                {
                    str+=s[i];
                }

                if (s[i]==' '){
                    if (flagN){
                        obshSum+=parseInt(str);
                        if (index<obshSum){
                            return (window.height-(standart+10)*(parseInt(str)))/2+(obshSum-parseInt(str)-index)*(standart+10)*-1-(obshSum-parseInt(str)-index)*20-10;
                        } else{
                            kolRange++;

                        }

                        str="";
                    }
                    flagN=!flagN;
                }
                i++;
            }

            return stanX*(kolRange)+standart*(kolRange)+320;


        }
        text: (index+1).toString()+'| '+'|'+qwer.timeBroken(index);//текст формируется из индекса объекта, тоесть его номера, пустое место под радиоданные и время до конца работы
        Rectangle{
            x:-2
            y:-2
            width: standart
            height:parent.height+4
            color:"transparent"
            border.color: "black"
            border.width: 2

        }
    }

    }
    Repeater{//отображение рангов сверху
    model:obh.maxR
    Text {
        x:10+stanX*index+standart*index+standart/4
        y:5
        text: qsTr((index).toString()+" ранг")
    }
    }
    Timer {
        interval: time
        repeat: true
        running: true
        onTriggered: {
            for (var i=0;i<upTablo.model;i++){
                var tablo=upTablo.itemAt(i).text.split('|');//смотрим элементы в табло
                tablo[2]-=1;//уменьшаем время работы на 1
                if (tablo[2]>=0){//если не достигнут 0 просто отрисовываем табло по новой
                upTablo.itemAt(i).text=tablo[0]+'|'+tablo[1]+'|'+tablo[2];
                }
                else if(tablo[2]<0)//если 0 достигнут заменяем объект на крест
                {
                    allSquare.itemAt(i).source="qrc:/img/5.png";
                }
            }
            kolTime++;//общее время
            var sumall=obh.kolAll();
            for (var i=0;i<sumall;i++){
                for (var j=0;j<sumall;j++){
                    if (obh.isSvaz(i,j)){
                        if ((obh.sendColor(i,j)=="red")||(obh.sendColor(i,j)=="blue")){//если получены неудачная синхронизация или просто поиск
                           obh.getColor(i,j,"");//перекращиваем линию в цвет по умолчанию
                        }
                        obh.perehodPoisk(i,kolTime);//осуществляем переход поиска

                    }
                }
            }
            var arr=dannie.split(' ');//получаем данные из журнала данных
            while(kolTime==parseInt(arr[3])){//пока время в данных соответствует текущему делаем операции
                var tablico=upTablo.itemAt(parseInt(arr[2])).text.split('|');//считываем данные из табло
                upTablo.itemAt(parseInt(arr[2])).text=tablico[0]+'|'+arr[1]+'|'+tablico[2];//записываем обновлённые данные в табло
                obh.kol++;//ставим счётчик на следующие данные
                obh.getColor(parseInt(arr[1]),parseInt(arr[2]),arr[0]);//меняем цвет в соответствие с полученными данными
                dannie=obh.readFile(obh.kol);//считываем следующие данные
                arr=dannie.split(' ');
            }

            linii.clearline();
    }
}
Rectangle{//отображение счётчика времени
    id:schet
    x:standart
    y:parent.height-standart/2-10
    height: 20
    width: {
    return (17)*10}
    Text {
        anchors.centerIn: parent
        id: timeText
        text: qsTr("Прошло времени: "+kolTime.toString())
    }
    border.color: "black"
    border.width: 3
}
    Dial{//Изменение скоротечности времени
    id:dial
    x:0
    y:parent.height-standart
    width: standart
    height: standart
    value: 0.75
    stepSize: 0.1
    onValueChanged: {time=value*1000;}
    }
    Rectangle{//большая шкала в которую помещаются промежутки с условиями
    id:aroundSh
    x:schet.x+schet.width+10
    y:schet.y
    width: window.width/2
    height:schet.height
    border.color: "black"
    border.width: 2
    }
    property int allTime:obh.maxConTime()
    Repeater{
    id:shkala
    model:obh.kolCon();//сколько условий столько и делений
        Rectangle{//разделяющие области
            x:{
                console.log(obh.kolCon())
                if (index==0)
                    return aroundSh.x+2;
                else
                    return shkala.itemAt(index-1).x+shkala.itemAt(index-1).width;
            }
            y:aroundSh.y+2;
            width: {
                return (obh.timeCondition(index+1)-obh.timeCondition(index))*secHod;}
            height: aroundSh.height-4
            border.color: "blue"
            Rectangle{
                x:1
                y:0
                width: {
                    var sum=0;

                    for (var i=0;i<=index;i++){
                        sum+=(obh.timeCondition(i+1)-obh.timeCondition(i));

                    }
                    if ((kolTime>=(sum-(obh.timeCondition(index+1)-obh.timeCondition(index))))&&(kolTime<=sum)){
                        return secHod*(kolTime+(obh.timeCondition(index+1)-obh.timeCondition(index))-sum);
                    } else if(sum<=kolTime)
                        return secHod*(obh.timeCondition(index+1)-obh.timeCondition(index));
                }
                height: parent.height
                color: {
                    if (parseInt(qwer.numCondition(index))==10){
                    return "tomato";}
                    else if (parseInt(qwer.numCondition(index))==20){
                    return "orangered";}
                    else if (parseInt(qwer.numCondition(index))==30){
                    return "red";}
                    else {
                    return "darkred";}

                }
                Text {
                    text: qsTr(qwer.numCondition(index))
                }
            }
        }
    }


}
