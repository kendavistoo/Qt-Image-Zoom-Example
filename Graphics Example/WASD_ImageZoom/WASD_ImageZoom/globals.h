


#ifndef GLOBALS_H
#define GLOBALS_H


#include <iostream>
#include <cstdio>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <stdio.h>

#include <QApplication>
//#include <QBasicTimer>
#include <QBuffer>
#include <QByteArray>
//#include <QCheckBox>
#include <QCloseEvent>
#include <QColor>
#include <QCoreApplication>
#include <QtCore/qmath.h>
#include <QCursor>
#include <QDataStream>
#include <QDebug>
#include <QDesktopWidget>
#include <QErrorMessage>
#include <QEvent>
#include <QEventLoop>
#include <QFile>
#include <QFileInfo>
//#include <QFont>
//#include <QFontInfo>
//#include <QFontMetrics>
#include <QFrame>
#include <QGuiApplication>
#include <QInputEvent>
//#include <QIcon>
#include <QImage>
#include <QIODevice>
#include <QKeyEvent>
#include <QLabel>
//#include <QLayout>
//#include <QLayoutItem>
#include <QLine>
#include <QMainWindow>
//#include <QMargins>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QMouseEvent>
#include <QObject>
#include <QPaintDevice>
#include <QPainter>
#include <QPixelFormat>
#include <QPixmap>
//#include <QtPlugin>
//#include <QPluginLoader>
#include <QPoint>
#include <QPointer>
#include <QRect>
//#include <QRectF>
#include <QRegion>
#include <QResource>
#include <QRgb>
#include <QSize>
#include <QSizePolicy>
#include <QString>
#include <QStyle>
//#include <QTextStream>
#include <QTime>
#include <QTimer>
#include <QTimerEvent>
//#include <QTransform>
//#include <QVector>
#include <QWheelEvent>
#include <QWidget>
#include <QWindow>

//#include <QtEndian>

#include <QtCore>
#include <QtGlobal>
#include <QtDebug>
#include <QtGui>


using std::cout;
using std::cin;
using std::vector;


//==================== constants ====================

static const double G_PI = 3.1415926535897932384626433832795028841971693993751;
static const double G_PIBY2 = G_PI / 2.0;

static const double G_E = 2.7182818284590452353602874713527;

static const int G_FWD         = 1;
static const int G_REV         = -1;

static const bool G_YES = true;
static const bool G_NO  = false;

static const bool G_ON  = true;
static const bool G_OFF = false;

static const bool G_FAST = true;
static const bool G_SLOW = false;

static const int G_WIDTH    = 600;
static const int G_HEIGHT   = 300;

static const QColor G_DARKEST       = QColor(1,1,1,255);        // Almost QColor(0,0,0,255);
static const QColor G_WHITE         = QColor(255,255,255,255);

static const QColor G_RED           = QColor(255,0,0,255);
static const QColor G_GREEN         = QColor(0,255,0,255);
static const QColor G_BLUE          = QColor(0,0,255,255);

static const int A_NONE  = 0;
static const int A_LEFT  = 1;
static const int A_RIGHT = 2;

static const int    US_MINIMUM          = 101;
static const int    US_MAXIMUM          = 100001;
const static int    US_DEFAULT_SIZE_OF_UNIVERSE = 1001;

static const int G_BUTTON_IDLE      =0;

static const int G_MID_BUTTON_UP    = -1;
static const int G_MID_BUTTON_IDLE  = 0;
static const int G_MID_BUTTON_DOWN  = 1;

static const int G_LEFT_BUTTON_UP    = -2;
static const int G_LEFT_BUTTON_IDLE  = 0;
static const int G_LEFT_BUTTON_DOWN  = 2;

static const int G_RIGHT_BUTTON_UP    = -3;
static const int G_RIGHT_BUTTON_IDLE  = 0;
static const int G_RIGHT_BUTTON_DOWN  = 3;

static const int G_KEY_UP   = -1;
static const int G_KEY_IDLE = 0;
static const int G_KEY_DOWN = 1;

static const int G_ZOOM_FRAME_WIDTH = 500;
static const int G_WASD_FRAME_WIDTH = 250;

static const int G_COMPLETELY   = true;
static const int G_PARTIALLY    = false;

//==================== variables ====================

static int  gKeyState;
static int  gButtonState;

static bool gFlipFlop;
static bool gGate;

//==================== functions ====================

void gSizeAndCenterWidget (QWidget* widget, int width, int height);

void gSizeAndCenterWidgetInWidget (QWidget* widget, QWidget* inWidget,
                                                            int sideMargin, int topBotMargin);
bool gDecDigitTest(QChar ch);

bool gHexDigitTest(QChar ch);

QString  gLastNameOfPath(QString myPath);

QString gReverseString(QString strA);

QString gLeadingZerosForStringSuffixNumber(QString strA, uint numSuffixDigits);

//----------

//Used in diagnostics

void DoDebug ( quint32 t1);

void DoDebug ( quint32 t1, quint32 t2);

void DoDebug ( quint32 t1, quint32 t2, quint32 t3);

void DoDebug ( quint32 t1, quint32 t2, quint32 t3, quint32 t4);

//----------



#endif // GLOBALS_H
