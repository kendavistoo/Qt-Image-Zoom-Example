#include "zoomframe.h"




//---------- CONSTRUCTOR   ZoomFrame ----------

ZoomFrame :: ZoomFrame(QWidget *parent, Qt::WindowFlags f) : QFrame(parent, f)
{
    qDebug()<<"CONSTRUCTOR   ZoomFrame";

    zoomFactor = 1.0;
    wheelConst = 8.0 / 120.0;

    setMouseTracking(true);
    show();
}

//---------- DESTRUCTOR   ~ZoomFrame ----------

ZoomFrame :: ~ZoomFrame()
{
    qDebug()<<"DESTRUCTOR   ~ZoomFrame";

    delete pixmap;
}

//---------- paintEvent ----------

void ZoomFrame :: paintEvent(QPaintEvent*){

    QPainter* painter = new QPainter(this);

    painter->drawPixmap(this->rect(), *pixmap, viewPort);

    //drawPixmap(const QRect &target, const QPixmap &pixmap, const QRect &source)
    //Draws the rectangular portion source of the given pixmap into the given target in the paint device.

    //----------

    QRect borderR = this->rect();
    borderR.adjust(1,1,-2,-2);
    QPen  pen;
    pen.setWidth(3);
    painter->drawRect(borderR);

    //----------

    //paintEvent hit indicator
    int x = 10 + (int)(50 + (rand() % 10));
    int y = (this->height() - 40);
    QRect myRect(x,y,8,8);
    painter->fillRect(myRect, G_BLUE);

    delete painter;

    mouseLocInZoomFrame = QCursor::pos();
    mouseLocInZoomFrame = this->mapFromGlobal(mouseLocInZoomFrame);

    //----------

    if (initial == true){
        pixFrameRatio = (double)pixmap->width() / (double)G_ZOOM_FRAME_WIDTH;

        pixmapW2ThisW = (double)pixmap->rect().width() / (double)this->rect().width();

        gKeyState    = G_KEY_UP;
        gButtonState = G_BUTTON_IDLE;

        emit SignalZoomSrcRect(viewPort);
        initial = false;
    }//if

    update();
}//paintEvent

//---------- wheelEvent ----------

void ZoomFrame :: wheelEvent(QWheelEvent* event){

    if (gButtonState == G_MID_BUTTON_DOWN){
        return;
    }//if

    theCenter = viewPort.center();

    if (event->delta() > 0)
        zoomFactor = 0.9;
    else
        zoomFactor = 1.1;

    doMouseLocation();

    QRect tempRect = viewPort;      // Has pixmap coordinates

    int www = round(zoomFactor * (double)tempRect.width());
    int hhh = round(zoomFactor * (double)tempRect.height());

    if ((www < (this->width() / 8)) || (hhh < (this->height() / 8))){  // If too small
        qDebug()<<"viewPort is too small";
        www = this->width() / 8;    // This is glitchy !!
        hhh = this->height() / 8;
    }//if

    if ((www > (pixmap->width())) || (hhh > (pixmap->height()))){
        www = pixmap->width();
        hhh = pixmap->height();
    }//if

    tempRect.setX(viewPort.x());
    tempRect.setY(viewPort.y());
    tempRect.setWidth(www);         // Has zoomed width and height
    tempRect.setHeight(hhh);

    //----------

    tempRect.moveCenter(theCenter);

    viewPort = tempRect;

    //----------

    origX = viewPort.x();
    origY = viewPort.y();
    origW = viewPort.width();
    origH = viewPort.height();

    if ( pixmap->rect().contains(viewPort, G_COMPLETELY) == false){

        if (viewPort.left() < 0){
            viewPort.setX(0);
            viewPort.setWidth(origW);
            viewPort.setHeight(origH);
        }//if

        if (viewPort.top() < 0){
            viewPort.setY(0);
            viewPort.setWidth(origW);
            viewPort.setHeight(origH);
        }//if

        if (viewPort.right() > pixmap->rect().right()){
            viewPort.setX(pixmap->rect().right() - origW);
            viewPort.setWidth(origW);
            viewPort.setHeight(origH);
        }//if

        if (viewPort.bottom() > pixmap->rect().bottom()){
            viewPort.setY(pixmap->rect().bottom() - origH);
            viewPort.setWidth(origW);
            viewPort.setHeight(origH);
        }//if
    }//if

    emit SignalZoomSrcRect(viewPort);
}//wheelEvent

//---------- mouseMoveEvent ----------

void ZoomFrame :: mouseMoveEvent(QMouseEvent* event){

    bool oops = false;

    QPoint mouseLoc = event->pos();
    mouseLocInViewportX = mouseLoc.x();
    mouseLocInViewportY = mouseLoc.y();

    switch (gButtonState){

    case G_MID_BUTTON_DOWN:

        deltaX = (int)(Z_MID_BUTT_SPEED * (oldX - mouseLocInViewportX));
        deltaY = (int)(Z_MID_BUTT_SPEED * (oldY - mouseLocInViewportY));

        viewPort.adjust(deltaX, deltaY, deltaX, deltaY);

        if (viewPort.left() < 0){
            viewPort.setX(0);
            viewPort.setWidth(origW);
            viewPort.setHeight(origH);
            oops = true;
        }//if

        if (viewPort.top() < 0){
            viewPort.setY(0);
            viewPort.setWidth(origW);
            viewPort.setHeight(origH);
            oops = true;
        }//if

        if (viewPort.right() > pixmap->rect().right()){
            viewPort.setX(pixmap->rect().right() - origW);
            viewPort.setWidth(origW);
            viewPort.setHeight(origH);
            oops = true;
        }//if

        if (viewPort.bottom() > pixmap->rect().bottom()){
            viewPort.setY(pixmap->rect().bottom() - origH);
            viewPort.setWidth(origW);
            viewPort.setHeight(origH);
            oops = true;
        }//if

        emit SignalZoomSrcRect(viewPort);

        if (oops){
            oldX = mouseLocInViewportX;
            oldY = mouseLocInViewportY;
        }//if
        break;

    case G_LEFT_BUTTON_DOWN:

        // TODO

        break;

    case G_RIGHT_BUTTON_DOWN:

        //TODO

        break;
    }//switch
}//mouseMoveEvent

//---------- mousePressEvent ----------

void ZoomFrame :: mousePressEvent(QMouseEvent *event){

    switch(event->button()){

    case Qt::MiddleButton:

        gKeyState    = G_KEY_IDLE;
        gButtonState = G_MID_BUTTON_DOWN;

        mouseLocInViewportX = event->pos().x();
        mouseLocInViewportY = event->pos().y();

        oldX = mouseLocInViewportX;
        oldY = mouseLocInViewportY;
        break;

    case Qt::LeftButton:

        break;

    case Qt::RightButton:

        break;
    }
}//mousePressEvent

//---------- mouseReleaseEvent ----------

void ZoomFrame :: mouseReleaseEvent(QMouseEvent *event){

    switch(event->button()){

    case Qt::LeftButton:

        break;

    case Qt::RightButton:

        break;

    case Qt::MiddleButton:
        gKeyState    = G_KEY_IDLE;
        gButtonState = G_MID_BUTTON_UP;
        break;
    }//switch
}//mouseReleaseEvent

//---------- SlotHandleWASDrect ----------

void ZoomFrame :: SlotHandleWASDrect(QRect r){

    double scaleFactor = pixmapW2ThisW * ((double)G_ZOOM_FRAME_WIDTH / (double)G_WASD_FRAME_WIDTH);

    int locX = (int)(scaleFactor * r.x());
    int locY = (int)(scaleFactor * r.y());

    viewPort.setX(locX);
    viewPort.setY(locY);
    viewPort.setWidth((int)(scaleFactor * r.width()));
    viewPort.setHeight((int)(scaleFactor * r.height()));

    this->update();
}//SlotHandleWASDrect

//---------- setImage ----------

void ZoomFrame :: setImage(QImage* image){
    pixmap = new QPixmap( QPixmap::fromImage(*image));
    viewPort = pixmap->rect();
}//setImage

//---------- doMouseLocation ----------

void ZoomFrame :: doMouseLocation(){

    fractionOfWidthX  = (double)mouseLocInZoomFrame.x() / (double)this->width();      // Fractional width..
    fractionOfHeightY = (double)mouseLocInZoomFrame.y() / (double)this->height();     // ..of the mouse

    mouseLocInViewportX = (int)(fractionOfWidthX * (double)viewPort.width());    // Fractional pixmap width..
    mouseLocInViewportY = (int)(fractionOfHeightY * (double)viewPort.height()); // ..of the mouse

    mouseLocInPixmapX = viewPort.x() + mouseLocInViewportX;  // Location of mouse in the viewport
    mouseLocInPixmapY = viewPort.y() + mouseLocInViewportY; // Remember, viewport coords are in pixmap coords
}//doMouseLocation

