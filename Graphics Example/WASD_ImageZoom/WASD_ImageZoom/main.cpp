#include "mainwindow.h"

//========== main ==========

int main(int argc, char *argv[])
{
    int result;

    QApplication a(argc, argv);
    MainWindow* w = new MainWindow();
    gSizeAndCenterWidget (w, MW_WIDTH, MW_HEIGHT);
    w->setMinimumWidth(MW_WIDTH - 200);
    w->setMinimumHeight(MW_HEIGHT - 200);

    w->setWindowTitle("WASD_Image_Zoom");
    w->setVisible(true);

    //---------- Loop

    QRegion rzoom(w->zoomFrame->rect());
    QRegion rwasd(w->wasdFrame->rect());

    w->region = QRegion(w->rect());
    w->region.subtracted(rzoom);
    w->region.subtracted(rwasd);

    while (w->isVisible()){
        w->update();
        result = a.exec();
    }//while

    delete w;
    return result;
}
