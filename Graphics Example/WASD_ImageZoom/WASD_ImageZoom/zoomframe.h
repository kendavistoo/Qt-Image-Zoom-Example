#ifndef ZOOMFRAME_H
#define ZOOMFRAME_H

#ifndef GLOBALS_H
#include "globals.h"
#endif


static double Z_MID_BUTT_SPEED = 0.2;

class ZoomFrame : public QFrame
{
    Q_OBJECT

public:
    ZoomFrame(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::Widget);
    ~ZoomFrame();

    QPixmap*    pixmap;
    QRect       viewPort;
    double      zoomFactor;
    double      wheelConst;

    bool        initial = true;
    double      pixFrameRatio;

    double      fractionOfWidthX;
    double      fractionOfHeightY;

    QPoint      mouseLocInZoomFrame;

    int         mouseLocInViewportX;
    int         mouseLocInViewportY;

    int         mouseLocInPixmapX;
    int         mouseLocInPixmapY;

    QPoint      theCenter;

    int         oldX;
    int         oldY;

    int         deltaX;
    int         deltaY;

    int         origX;
    int         origY;
    int         origW;
    int         origH;

    double      pixmapW2ThisW;

    int         testCounter = 0;

    void    setImage(QImage* image);
    QPoint  localToPixmap(QPoint);
    void    doMouseLocation();

protected:
    void paintEvent(QPaintEvent*);
    void wheelEvent(QWheelEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void SignalZoomSrcRect(QRect);

public slots:
    void SlotHandleWASDrect(QRect);
};

#endif // ZOOMFRAME_H
