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
        linii.clearline();
    }
    onWidthChanged: {
        linii.clearline();
    }
    TypeName{
    id:obh
    kol:0
    }
    Yeah{
    id: qwer
    }
    property real secHod : (aroundSh.width-4)/allTime
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
        if (rangeMax>=kolInRangeMax)
            return (window.height-200)/rangeMax;
        else
            return (window.height-200)/kolInRangeMax;
    }
    else{
        if (rangeMax>=kolInRangeMax)
            return (window.width-200)/rangeMax;
        else
            return (window.width-200)/kolInRangeMax;

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
        var sumall=obh.kolAll();
        var tFlag=true;
        for (var i=0;i<sumall;i++){
            for (var j=0;j<sumall;j++){
                if (obh.isSvaz(i,j)){
                    /**/
                    var s=obh.rasprRange();
                    var obshSum=0;
                    var kolu=0;
                    var h=0;
                    var flagN=false;
                    var str="";
                    while (obshSum-1<i){
                        if((s[h]!=' ')&&(flagN))
                        {
                            str+=s[h];
                        }

                        if (s[h]==' '){
                            if (flagN){
                                obshSum+=parseInt(str);
                                kolu=parseInt(str);
                                str="";
                            }
                            flagN=!flagN;
                        }
                        h++;
                    }
                    if ((j<obshSum)&&(j>(obshSum-kolu))){
                        ctx.beginPath();
                        ctx.strokeStyle=obh.sendColor(i,j);
                        ctx.setLineDash([5, 3]);//задача на отрисовку пунктирных линий
                        ctx.lineWidth = 2;
                        ctx.moveTo(allSquare.itemAt(i).x+standart/2,allSquare.itemAt(i).y+standart);
                        ctx.lineTo(allSquare.itemAt(j).x+standart/2,allSquare.itemAt(j).y);
                        ctx.stroke();
                    }
                    else if(obh.dalSvaz(i,j)){
                        ctx.beginPath();
                        ctx.strokeStyle=obh.sendColor(i,j);
                        ctx.setLineDash([5, 3]);//задача на отрисовку пунктирных линий
                        ctx.lineWidth = 2;
                        if (tFlag){
                        if (i<j){
                            ctx.moveTo(allSquare.itemAt(i).x+standart/2,allSquare.itemAt(i).y);
                            ctx.bezierCurveTo(allSquare.itemAt(i).x+standart,allSquare.itemAt(i).y-standart*3,allSquare.itemAt(j).x,allSquare.itemAt(j).y-standart*3,allSquare.itemAt(j).x+standart/2,allSquare.itemAt(j).y);
                        }else{
                            ctx.moveTo(allSquare.itemAt(j).x+standart/2,allSquare.itemAt(j).y);
                            ctx.bezierCurveTo(allSquare.itemAt(j).x+standart/2,allSquare.itemAt(j).y-standart*3,allSquare.itemAt(i).x+standart/2,allSquare.itemAt(i).y-standart*3,allSquare.itemAt(i).x+standart/2,allSquare.itemAt(i).y);
                        }
                        tFlag=!tFlag;
                        }else{
                            if (i<j){
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
                    ctx.moveTo(allSquare.itemAt(i).x+standart,allSquare.itemAt(i).y+standart/2);
                    ctx.lineTo(allSquare.itemAt(j).x,allSquare.itemAt(j).y+standart/2);
                    ctx.stroke();
                    }
                }
            }
        }
//        for (var i=0;i<secondreg.model;i++){
//        ctx.moveTo(firstreg.itemAt(0).x+standart,firstreg.itemAt(0).y+standart/2);
//        ctx.lineTo(secondreg.itemAt(i).x,secondreg.itemAt(i).y+standart/2);
//        }
//        ctx.moveTo(firstreg.itemAt(0).x+standart/2,firstreg.itemAt(0).y);
//        ctx.bezierCurveTo(100,-110,window.width,0,fourthreg.itemAt(0).x+standart/2,fourthreg.itemAt(0).y);
    }

    Canvas {
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
    Repeater{
    id: allSquare
    model:allKol
    Rectangle{
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

        Image {
            source: "qrc:/img/antena.png"
            anchors.fill: parent
        }
    }
    }
    Repeater{
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
        text: (index+1).toString()+'| '+'| '
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
    Repeater{
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
            kolTime++;
            var sumall=obh.kolAll();
            for (var i=0;i<sumall;i++){
                for (var j=0;j<sumall;j++){
                    if (obh.isSvaz(i,j)){
                        if (obh.sendColor(i,j)=="red"){
                           obh.getColor(i,j,"");
                        }

                    }
                }
            }
            linii.clearline();
            var arr=dannie.split(' ');
            while(kolTime==parseInt(arr[3])){
                console.log("gttt");
                var tablico=upTablo.itemAt(parseInt(arr[1])-1).text.split('|');
                upTablo.itemAt(parseInt(arr[1])-1).text=tablico[0]+'|'+arr[2]+'|'+tablico[2];
                obh.kol++;
                obh.getColor(parseInt(arr[2])-1,parseInt(arr[1])-1,arr[0]);
                dannie=obh.readFile(obh.kol);
                arr=dannie.split(' ');
            }

    }
}
Rectangle{
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
    Dial{
    x:0
    y:parent.height-standart
    width: standart
    height: standart
    value: 0.75
    stepSize: 0.1
    onValueChanged: {time=value*1000;}
    }
    Rectangle{
    id:aroundSh
    x:schet.x+schet.width+10
    y:schet.y
    width: window.width/2
    height:schet.height
    border.color: "black"
    border.width: 2
    }
    property variant mass: [10,17,10]//промежутки сколько длиться область неполадок
    property int allTime:37//заменить на общее время из базы
    Repeater{
    id:shkala
    model:3
        Rectangle{//разделяющие области
            x:{
                if (index==0)
                    return aroundSh.x+2;
                else
                    return shkala.itemAt(index-1).x+shkala.itemAt(index-1).width;
            }
            y:aroundSh.y+2;
            width: { return mass[index]*secHod}
            height: aroundSh.height-4
            border.color: "blue"
            Rectangle{
                x:1
                y:0
                width: {
                    var sum=0;
                    var need=-1;
                    for (var i=0;i<=index;i++){
                        sum+=mass[i];
                        need++;
                    }

                    if ((kolTime>=sum-mass[index])&&(kolTime<=sum)){
                        return secHod*(kolTime+mass[index]-sum);
                    } else if(sum<=kolTime)
                        return secHod*mass[index];
                }
                height: parent.height
                color: "red"
                Text {
                    text: qsTr("Условие"+index.toString())
                }
            }
        }
    }

}
