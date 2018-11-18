#include "wasdframe.h"


//---------- CONSTRUCTOR   WasdFrame ----------

WasdFrame :: WasdFrame(QWidget *mom, Qt::WindowFlags f) : QFrame(mom, f)
{
    qDebug()<<"CONSTRUCTOR   WasdFrame";

    parent = mom;
    keyPanTime.start();
    setFocusPolicy(Qt::StrongFocus);
    SignalWasdDoInitialize();
}


//---------- DESTRUCTOR   ~WasdFrame ----------

WasdFrame :: ~WasdFrame()
{
    qDebug()<<"DESTRUCTOR   ~WasdFrame";

    delete pixmap;
}

//---------- setImage ----------

void WasdFrame :: setImage(QImage* image){
    pixmap = new QPixmap( QPixmap::fromImage(*image));
}

//---------- SlotZoomSrcRect ----------

void WasdFrame :: SlotZoomSrcRect(QRect zSrc){

    double scaleFactor = (double)this->rect().width() / (double)pixmap->rect().width();

    int locX = (int)(scaleFactor * zSrc.x());
    int locY = (int)(scaleFactor * zSrc.y());

    redSrcRect.setX(locX);
    redSrcRect.setY(locY);
    redSrcRect.setWidth((int)(scaleFactor * zSrc.width()));
    redSrcRect.setHeight((int)(scaleFactor * zSrc.height()));
}//SlotZoomSrcRect

//---------- SlotWasdDoInitialize ----------

void WasdFrame :: SlotWasdDoInitialize(){

    gKeyState    = G_KEY_IDLE;
    gButtonState = G_BUTTON_IDLE;
}

//---------- paintEvent ----------

void WasdFrame :: paintEvent(QPaintEvent* e){

    QPainter* painter = new QPainter(this);


    QRect borderR = this->rect();
    borderR.adjust(1,1,-2,-2);
    painter->drawPixmap(borderR, *pixmap, pixmap->rect());

    //----------

    QPen  pen;
    pen.setWidth(3);
    painter->drawRect(borderR);

    //----------

    //paintEvent hit indicator
    int x = 10 + (int)(50 + (rand() % 10));
    int y = (this->height() - 40);
    QRect myRect(x,y,8,8);
    painter->fillRect(myRect, Qt::green);

    //----------

    QPen redPen;
    redPen.setColor(Qt::red);
    redPen.setWidth(3);
    painter->setPen(redPen);
    painter->drawRect(redSrcRect);

    delete painter;

    //----------

    if (gKeyState == G_KEY_DOWN){
        HandleKeyImagePan();
    }//if

    this->update();
}//paintEvent

//---------- keyPressEvent ----------

void WasdFrame :: keyPressEvent(QKeyEvent *event){

    if (gButtonState == G_MID_BUTTON_DOWN){
        return;
    }//if

    theKey = event->key();
    gKeyState = G_KEY_DOWN;
}//keyPressEvent

//---------- keyReleaseEvent ----------

void WasdFrame :: keyReleaseEvent(QKeyEvent *event){

    if (event->isAutoRepeat() == false){
        gKeyState = G_KEY_UP;
    }//if

    theKey = 0;
}//keyReleaseEvent

//---------- mouseMoveEvent ----------

void WasdFrame :: mouseMoveEvent(QMouseEvent* event){

    bool oops = false;

    QPoint mouseLoc = event->pos();
    mouseLocInWasdX = mouseLoc.x();
    mouseLocInWasdY = mouseLoc.y();

    int deltaX, deltaY;

    int origX;
    int origY;
    int origW;
    int origH;

    switch (gButtonState){

    case G_MID_BUTTON_DOWN:

        xAndOffset = mouseLocInWasdX + mouseMoveOffsetX;
        yAndOffset = mouseLocInWasdY + mouseMoveOffsetY;

        redSrcRect.moveCenter(QPoint(xAndOffset, yAndOffset));

        origX = redSrcRect.x();
        origY = redSrcRect.y();
        origW = redSrcRect.width();
        origH = redSrcRect.height();

        if (redSrcRect.left() < 0){
            redSrcRect.setX(0);
            redSrcRect.setWidth(origW);
            redSrcRect.setHeight(origH);
            oops = true;
        }//if

        if (redSrcRect.top() < 0){
            redSrcRect.setY(0);
            redSrcRect.setWidth(origW);
            redSrcRect.setHeight(origH);
            oops = true;
        }//if

        if (redSrcRect.right() > this->rect().right()){
            redSrcRect.setX(this->rect().right() - origW);
            redSrcRect.setWidth(origW);
            redSrcRect.setHeight(origH);
            oops = true;
        }//if

        if (redSrcRect.bottom() > this->rect().bottom()){
            redSrcRect.setY(this->rect().bottom() - origH);
            redSrcRect.setWidth(origW);
            redSrcRect.setHeight(origH);
            oops = true;
        }//if

        emit SignalWasdRect(redSrcRect);

        if (oops){
            QPoint rectCtr = redSrcRect.center();

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

void WasdFrame :: mousePressEvent(QMouseEvent *event){

    switch(event->button()){

    case Qt::MiddleButton:

        if (redSrcRect.contains(event->pos())){
            gKeyState    = G_KEY_IDLE;
            gButtonState = G_MID_BUTTON_DOWN;

            mouseLocInWasdX = event->pos().x();
            mouseLocInWasdY = event->pos().y();

            QPoint rectCtr = redSrcRect.center();

            mouseMoveOffsetX = rectCtr.x() - mouseLocInWasdX;
            mouseMoveOffsetY = rectCtr.y() - mouseLocInWasdY;
        }//if
        break;

    case Qt::LeftButton:

        break;

    case Qt::RightButton:

        break;
    }//switch
}//mousePressEvent

//---------- mouseReleaseEvent ----------

void WasdFrame :: mouseReleaseEvent(QMouseEvent *event){

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

//---------- HandleKeyImagePan ----------

void WasdFrame :: HandleKeyImagePan(){

    if (keyPanTime.elapsed() < WA_KEY_PAN_DELTA_TIME){
        return;
    }//if

    int deltaX = 0;
    int deltaY = 0;

    switch (theKey){

        case Qt::Key_A:
        case Qt::Key_Left:
            deltaX = -WA_KEY_PAN_DELTA_DISTANCE;
        break;

        case Qt::Key_D:
        case Qt::Key_Right:

            deltaX = WA_KEY_PAN_DELTA_DISTANCE;
        break;

        case Qt::Key_W:
        case Qt::Key_Up:
            deltaY = -WA_KEY_PAN_DELTA_DISTANCE;
        break;

        case Qt::Key_S:
        case Qt::Key_Down:
            deltaY = WA_KEY_PAN_DELTA_DISTANCE;
        break;
    }//switch

    //-----

    redSrcRect.adjust(deltaX, deltaY, deltaX, deltaY);

    if (redSrcRect.left() < 0){
        redSrcRect.moveLeft(0);
    }//if

    if (redSrcRect.right() > this->rect().right()){
        redSrcRect.moveRight(this->rect().right());
    }//if

    if (redSrcRect.top() < 0){
        redSrcRect.moveTop(0);
    }//if

    if (redSrcRect.bottom() > this->rect().bottom()){
        redSrcRect.moveBottom(this->rect().bottom());
    }//if

    emit SignalWasdRect(redSrcRect);

    keyPanTime.restart();
}//HandleKeyImagePan


