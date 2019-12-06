#ifndef FACEDRAWDLG_H
#define FACEDRAWDLG_H

#include <QWidget>

class QPaintEvent;
class CapThread;
class FaceIdentifyThread;
namespace Ui {
class FaceDrawDlg;
}

class FaceDrawDlg : public QWidget
{
    Q_OBJECT

public:
    explicit FaceDrawDlg(QWidget *parent = nullptr);
    ~FaceDrawDlg();

    void paintEvent(QPaintEvent *e);
    //void closeEvent(QCloseEvent *event);

//public:
//    CapThread* m_CapThread;

public slots:
    //接收槽
    void RecvRGBData(const QImage& RGBimg);
    void RecvIRData(const QImage& IRimg);

public:
    //保存图像到paintevent中绘制
    QImage m_QimgEvent_tempImg;

private slots:
    void on_Btn_Setup_clicked();


private:
    Ui::FaceDrawDlg *ui;
};

#endif // FACEDRAWDLG_H
