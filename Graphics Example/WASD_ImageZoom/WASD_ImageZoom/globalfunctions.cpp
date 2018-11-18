



#ifndef GLOBALS_H
#include "globals.h"
#endif





static const QChar gHexDigits[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8',
                                           '9', 'A', 'B', 'C', 'D', 'E', 'F'};

static const QChar gDecDigits[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};


QStringList strList;




//---------- gSizeAndCenterWidget ---------

void gSizeAndCenterWidget (QWidget* widget, int width, int height) {
    int x,y;
    int screenWidth;
    int screenHeight;

    QDesktopWidget* desktop = QApplication::desktop();

    screenWidth = desktop->width();
    screenHeight = desktop->height();

    x = (screenWidth - width)/2;
    y = (screenHeight - height)/2;

    widget->setGeometry (x, y, width, height);
}//gSizeAndCenterWidget


//---------- gSizeAndCenterWidgetInWidget ---------

void gSizeAndCenterWidgetInWidget (QWidget* widget, QWidget* inWidget,
                                                            int sideMargin, int topBotMargin) {
    int x,y;
    int widWidth;
    int widHeight;
    int widX, widY;
    int width, height;

    widWidth  = inWidget->width();
    widHeight = inWidget->height();

    width  = inWidget->width() - 2*sideMargin;
    height = inWidget->height() - 2*topBotMargin;

    widX = inWidget->x();
    widY = inWidget->y();

    x = widX + (widWidth - width)/2;
    y = widY + (widHeight - height)/2;

    widget->setGeometry (x, y, width, height);
    widget->setFixedSize(width, height);
}//gSizeAndCenterWidgetInWidget



//---------- gDecDigitTest ---------

bool gDecDigitTest(QChar ch) {

    bool test = false;                                      //Assume ch is not dec digit

    for (int i=0; i<10; i++){                               //Go thru list of dec digits
        if(gDecDigits[i] == ch){                             //If ch matches one of them...
            test = true;                                    //..then test is good
            break;                                          //Look no further
        }//if
    }//for

    return test;
}//gDecDigitTest


//---------- gHexDigitTest ---------

bool gHexDigitTest(QChar ch) {

    bool test = false;                                      //Assume ch is not hex digit

    for (int i=0; i<16; i++){                               //Go thru list of hex digits
        if(gHexDigits[i] == ch){                             //If ch matches one of them...
            test = true;                                    //..then test is good
            break;                                          //Look no further
        }//if
    }//for

    return test;
}//gHexDigitTest


//---------- gLastNameOfPath ---------

QString gLastNameOfPath(QString myPath) {

    if ((myPath.isEmpty()) or (myPath.isNull())){           //Bad string
        return QString();
    }//if

    int index = myPath.lastIndexOf('/');

    if (index == -1){                                       //'/' not found...
        return myPath;                                      //..must be first name
    }//if

    int numRtChars = myPath.size() - index;
    QString rightStr = myPath.right(numRtChars);            //Fetch the rightmost name..

    if (rightStr[0] == '/'){                                //..along with leading '/'
       rightStr.remove(0,1);                                //Strip the '/'
    }//if

    return rightStr;
}//gLastNameOfPath


//---------- gReverseString ---------

QString gReverseString(QString strA) {

    if ((strA.isEmpty()) or (strA.isNull())){
        return QString();
    }//if

    QString strB(strA);                                     //For correct size

    int j=0;
    for (int i=(strA.size() - 1); i>=0; i--){
        strB[j] = strA[i];
        j++;
    }//for i

    return strB;
}//gReverseString


//---------- gLeadingZerosForStringSuffixNumber -----------

QString gLeadingZerosForStringSuffixNumber(QString strA, uint numSuffixDigits){

    if ((strA.isEmpty()) or (strA.isNull())){
        return QString();
    }//if

    QString strB( gReverseString(strA) );                   //Create reverse of strA

    //-----

    QString     digitsStr;
    uint        nDigits = 0;
    bool        digitBool = true;

    while(digitBool){
        digitBool = false;
        QChar dch = strB.at(nDigits);
        if(gDecDigitTest(dch)){
            digitBool = true;
            digitsStr.append(dch);
            nDigits++;
        }//if
    }//while

    if (nDigits > numSuffixDigits){
        return strA;
    }//if

    //-----

    uint numZeros = numSuffixDigits - nDigits;

    for (int i=1; i<=numZeros; i++){
        digitsStr.append("0");
    }//for

    digitsStr = gReverseString(digitsStr);

    strA.truncate(strA.size() - nDigits);

    return strA.append(digitsStr);

}//gLeadingZerosForStringSuffixNumber

//--------------- DoDebug ---------------

void DoDebug ( quint32 t1){

    qDebug() << "";
    QString str1 = QString("%1").arg(t1, 8, 16, QLatin1Char('0') );
    QString outStr1 = QString("num1  %1   %2   %3").
                                arg(str1.toUpper(), 10, ' ').
                                    arg(QString::number(t1), 10, ' ').
                                        arg(t1, 32, 2, QLatin1Char('0'));
    qDebug()<<outStr1;

}//DoDebug

//--------------- DoDebug ---------------

void DoDebug ( quint32 t1, quint32 t2){

    qDebug() << "";
    QString str1 = QString("%1").arg(t1, 8, 16, QLatin1Char('0') );
    QString outStr1 = QString("num1  %1   %2   %3").
                                arg(str1.toUpper(), 10, ' ').
                                    arg(QString::number(t1), 10, ' ').
                                        arg(t1, 32, 2, QLatin1Char('0'));
    qDebug()<<outStr1;

    //----------

    QString str2 = QString("%1").arg(t2, 8, 16, QLatin1Char('0') );
    QString outStr2 = QString("num2  %1   %2   %3").
                                arg(str2.toUpper(), 10, ' ').
                                    arg(QString::number(t2), 10, ' ').
                                        arg(t2, 32, 2, QLatin1Char('0'));
    qDebug()<<outStr2;

}//DoDebug

//--------------- DoDebug ---------------

void DoDebug ( quint32 t1, quint32 t2, quint32 t3){

    qDebug() << "";
    QString str1 = QString("%1").arg(t1, 8, 16, QLatin1Char('0') );
    QString outStr1 = QString("num1  %1   %2   %3").
                                arg(str1.toUpper(), 10, ' ').
                                    arg(QString::number(t1), 10, ' ').
                                        arg(t1, 32, 2, QLatin1Char('0'));
    qDebug()<<outStr1;

    //----------

    QString str2 = QString("%1").arg(t2, 8, 16, QLatin1Char('0') );
    QString outStr2 = QString("num2  %1   %2   %3").
                                arg(str2.toUpper(), 10, ' ').
                                    arg(QString::number(t2), 10, ' ').
                                        arg(t2, 32, 2, QLatin1Char('0'));
    qDebug()<<outStr2;

    //----------

    QString str3 = QString("%1").arg(t3, 8, 16, QLatin1Char('0') );
    QString outStr3 = QString("num3  %1   %2   %3").
                                arg(str3.toUpper(), 10, ' ').
                                    arg(QString::number(t3), 10, ' ').
                                        arg(t3, 32, 2, QLatin1Char('0'));
    qDebug()<<outStr3;

}//DoDebug

//--------------- DoDebug ---------------

void DoDebug ( quint32 t1, quint32 t2, quint32 t3, quint32 t4){

    qDebug() << "";
    QString str1 = QString("%1").arg(t1, 8, 16, QLatin1Char('0') );
    QString outStr1 = QString("num1  %1   %2   %3").
                                arg(str1.toUpper(), 10, ' ').
                                    arg(QString::number(t1), 10, ' ').
                                        arg(t1, 32, 2, QLatin1Char('0'));
    qDebug()<<outStr1;

    //----------

    QString str2 = QString("%1").arg(t2, 8, 16, QLatin1Char('0') );
    QString outStr2 = QString("num2  %1   %2   %3").
                                arg(str2.toUpper(), 10, ' ').
                                    arg(QString::number(t2), 10, ' ').
                                        arg(t2, 32, 2, QLatin1Char('0'));
    qDebug()<<outStr2;

    //----------

    QString str3 = QString("%1").arg(t3, 8, 16, QLatin1Char('0') );
    QString outStr3 = QString("num3  %1   %2   %3").
                                arg(str3.toUpper(), 10, ' ').
                                    arg(QString::number(t3), 10, ' ').
                                        arg(t3, 32, 2, QLatin1Char('0'));
    qDebug()<<outStr3;


    //----------

    QString str4 = QString("%1").arg(t4, 8, 16, QLatin1Char('0') );
    QString outStr4 = QString("num4  %1   %2   %3").
                                arg(str4.toUpper(), 10, ' ').
                                    arg(QString::number(t4), 10, ' ').
                                        arg(t4, 32, 2, QLatin1Char('0'));
    qDebug()<<outStr4;

}//DoDebug
