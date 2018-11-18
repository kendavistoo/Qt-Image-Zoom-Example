#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#ifndef GLOBALS_H
#include "globals.h"
#endif

#ifndef ZOOMFRAME_H
#include "zoomframe.h"
#endif

#ifndef WASDFRAME_H
#include "wasdframe.h"
#endif

static const int MW_WIDTH   = 800;
static const int MW_HEIGHT  = 700;

static const int MW_FRAMES_GAP  = 30;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QImage*     image;
    ZoomFrame*  zoomFrame;
    WasdFrame*  wasdFrame;

    QRegion     region;

    QLabel*     zoomLabel;
    QLabel*     wasdLabel;

protected:
    void paintEvent(QPaintEvent*);

signals:
    void SignalDoInitialize();

public slots:
    void SlotDoInitialize();


};

#endif // MAINWINDOW_H
