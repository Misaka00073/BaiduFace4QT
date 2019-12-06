#include "FaceDrawDlg.h"
#include "ui_FaceDrawDlg.h"

#include "opencv2/opencv.hpp"
#include "QPaintEvent"
#include "QPainter"
#include "CapThread.h"
#include "QDebug"

#include "FaceIdentifyThread.h"


FaceDrawDlg::FaceDrawDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FaceDrawDlg)
{
    ui->setupUi(this);
    //m_CapThread = new CapThread;
    //m_CapThread->CapThreadInit();
    //设置槽函数接收RGB和IR;

    //m_FaceIdentifyThread = new FaceIdentifyThread(m_CapThread);
    //connect(m_CapThread, &CapThread::SendRGBData,this, &FaceDrawDlg::RecvRGBData);
    //connect(m_CapThread, &CapThread::SendIRData,this, &FaceDrawDlg::RecvIRData);
    //启动采集线程
    //m_CapThread->start();
    //setAutoFillBackground(1);

    //setStyleSheet("background: yellow");

    //connect(ui->Btn_Setup,&QPushButton::clicked, this, &FaceDrawDlg::on_Btn_Setup_clicked);

}

FaceDrawDlg::~FaceDrawDlg()
{
    //m_CapThread->StopCapThread();
    delete ui;

}
int i  = 30;
void FaceDrawDlg::paintEvent(QPaintEvent *e)
{//内部做过双缓冲
    QPainter painter(this);
    painter.setPen(    QPen(QColor(111,167,127),3));

    //painter.setBrush(QBrush(m_QimgEvent_tempImg));
    QRectF rect(40.0, 40.0, 100.0, 100.0);

    //paintet.drawImage
    painter.setRenderHint(QPainter:: Antialiasing, true);  //设置渲染,启动反锯齿
    QRectF imgTarget(0,0,640,480);
    QRectF imgSource(0,0,640,480);
    //paintet.drawImage(rect,m_QimgEvent_tempImg,rect);
    //绘制画面
    painter.drawImage(imgTarget,m_QimgEvent_tempImg,imgSource);
//    painter.drawArc(rect,30*16,(i++)*16); //绘画角度为30°~(30+150°)
//    if(i>360)
//    {
//        i = 0;

//    }
//    painter.drawPoint(40+50,40+50);     //绘制中心点

}

void FaceDrawDlg::RecvRGBData(const QImage &RGBimg)
{
    //ui->Btn_Setup->setText(tr("RecvRGBData"));
    //qDebug() << "RecvRGBData";
    QPixmap temppixmap = QPixmap::fromImage(RGBimg);
    //ui->Laber_showRGB->setPixmap(temppixmap);
    m_QimgEvent_tempImg = RGBimg;
    //qDebug() << temppixmap.rect();
    //qDebug() << temppixmap.size();
    update();
}

void FaceDrawDlg::RecvIRData(const QImage& IRimg)
{
    //return;

    //ui->Btn_Setup->setText(tr("RecvIRData"));
    //qDebug() << "RecvIRData";
    //QPixmap temppixmap = QPixmap::fromImage(IRimg);
    //m_QimgEvent_tempImg = IRimg;
    //update();




}

void FaceDrawDlg::on_Btn_Setup_clicked()
{
    i = 0;
    qDebug() << "FaceDrawDlg::on_Btn_Setup_clicked";
}
