#include "mainwindow.h"




//---------- CONSTRUCTOR   MainWindow ----------

MainWindow :: MainWindow(QWidget *parent) : QMainWindow(parent)
{
    qDebug()<<"CONSTRUCTOR   MainWindow";

    image = new QImage(":/Images/Hollywood.jpg");

    qDebug()<<"image size:  "<<image->rect();

    connect(this, &MainWindow::SignalDoInitialize, this, &MainWindow::SlotDoInitialize);

    emit MainWindow::SignalDoInitialize();
}//CONSTRUCTOR

//---------- DESTRUCTOR   ~MainWindow ----------

MainWindow :: ~MainWindow()
{
    qDebug()<<"DESTRUCTOR   ~MainWindow";

    delete image;
}//DESTRUCTOR

//---------- paintEvent ----------

void MainWindow :: paintEvent(QPaintEvent* e){

    QPainter* painter = new QPainter(this);

    painter->setClipRegion(region);

    int x = 10 + (int)(50 + (rand() % 10));
    int y = (this->height() - 40);
    QRect myRect(x,y,8,8);
    painter->fillRect(myRect, G_RED);

    //__________

    delete painter;
}//paintEvent

//---------- SlotDoInitialize ----------

void MainWindow :: SlotDoInitialize(){

    zoomFrame = new ZoomFrame(this);
    double aspect = (double)image->width() / (double)image->height();
    int www = G_ZOOM_FRAME_WIDTH;
    int hhh = (int)((double)www / aspect);
    zoomFrame->setGeometry(0, 0, www, hhh);
    zoomFrame->setAutoFillBackground(false);
    zoomFrame->show();
    zoomFrame->setImage(image);
    zoomFrame->viewPort = image->rect();

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   TEST   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
int newW = round(0.7 * (double)zoomFrame->viewPort.width());
int newH = round(0.7 * (double)zoomFrame->viewPort.height());
zoomFrame->viewPort.setSize(QSize(newW, newH));
zoomFrame->viewPort.moveTo(300,200);


    emit zoomFrame->SignalZoomSrcRect(zoomFrame->viewPort);

    //----------

    wasdFrame = new WasdFrame(this);
    int wasdX = zoomFrame->x();
    int wasdY = zoomFrame->y() + zoomFrame->height() + MW_FRAMES_GAP;
    int wasdW = G_WASD_FRAME_WIDTH;
    int wasdH = (int)((double)wasdW / aspect);

    wasdFrame->setGeometry(wasdX, wasdY, wasdW, wasdH);
    wasdFrame->setAutoFillBackground(false);
    wasdFrame->show();
    wasdFrame->setImage(image);
    wasdFrame->imageFrameRatio = (double)image->width() / (double)wasdFrame->width();

    connect(zoomFrame, &ZoomFrame::SignalZoomSrcRect, wasdFrame, &WasdFrame::SlotZoomSrcRect);

    connect(wasdFrame, &WasdFrame::SignalWasdRect, zoomFrame, &ZoomFrame::SlotHandleWASDrect);

    //----------

    QString zoomStr("- Mouse wheel to zoom");
    zoomStr.append("\n- Wheel-button to move viewport");
    zoomLabel = new QLabel(zoomStr, this);
    zoomLabel->setText(zoomStr);

    QString wasdStr("- WASD or arrow keys to translat rectangle");
    wasdStr.append("\n- Wheel-button to move red rectangle");
    wasdLabel = new QLabel(wasdStr, this);
    wasdLabel->setText(wasdStr);

    int myX, myY;
    myX = G_ZOOM_FRAME_WIDTH + 40;
    myY = zoomFrame->rect().top() + 40;
    zoomLabel->move(myX, myY);
    zoomLabel->setMinimumWidth(300);
    zoomLabel->setVisible(true);

    int urX, urY;
    urX = G_WASD_FRAME_WIDTH + 40;
    urY = wasdY + 40;
    wasdLabel->move(urX, urY);
    wasdLabel->setMinimumWidth(300);
    wasdLabel->setVisible(true);

    this->update();
}//SlotDoInitialize
