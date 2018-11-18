#ifndef WASDFRAME_H
#define WASDFRAME_H

#ifndef GLOBALS_H
#include "globals.h"
#endif


static const int    WA_KEY_PAN_DELTA_TIME = 10;
static const int    WA_KEY_PAN_DELTA_DISTANCE = 3;

static double       WA_MID_BUTT_SPEED = 0.2;

class WasdFrame : public QFrame
{
    Q_OBJECT

public:
    WasdFrame(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::Widget);
    ~WasdFrame();

    QWidget* parent;

    QPixmap* pixmap;

    QRect  redSrcRect;
    double imageFrameRatio;

    int     theKey   = 0;
    QTime   keyPanTime;
    int     keyState = G_KEY_IDLE;

    int     mouseLocInWasdX;
    int     mouseLocInWasdY;

    int     mouseMoveOffsetX;
    int     mouseMoveOffsetY;

    int     xAndOffset;
    int     yAndOffset;


    void setImage(QImage* image);
    void HandleKeyImagePan();

protected:
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public slots:
    void SlotZoomSrcRect(QRect);
    void SlotWasdDoInitialize();

signals:
    void SignalWasdRect(QRect);
    void SignalWasdDoInitialize();
};


#endif // WASDFRAME_H
