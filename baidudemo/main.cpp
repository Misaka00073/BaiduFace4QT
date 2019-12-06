#include "BaiduFaceMainDialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BaiduFaceMainDialog w;
    w.show();

    return a.exec();
}
