#include "BaiduFaceMainDialog.h"
#include "ui_BaiduFaceMainDialog.h"

#include "QDebug"

#include "baidu_face_api.h"
#include "FaceDrawDlg.h"
#include "CapThread.h"
#include "FaceIdentifyThread.h"

//报中文常量错误
#pragma execution_character_set("utf-8")

BaiduFaceMainDialog::BaiduFaceMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BaiduFaceMainDialog)
{
    ui->setupUi(this);

    //BaiduFaceApi *baiduapi = new BaiduFaceApi();

//    BaiduFaceApi*baiduapi = new BaiduFaceApi;
//    int ret = baiduapi->sdk_init();
//    qDebug() << "ret: " << ret;
//    qDebug() << "返回值：" << ret;
    //创建子窗口
    m_FaceDrawDlg = new FaceDrawDlg(this);
    //
    //创建采图线程
    m_CapThread = new CapThread;
    m_CapThread->CapThreadInit();
    //基础人像画面
    connect(m_CapThread, SIGNAL(SendRGBData(const QImage&)),m_FaceDrawDlg, SLOT(RecvRGBData(const QImage&)));
    connect(m_CapThread, SIGNAL(SendIRData(const QImage&)), this, SLOT(RecvIRData(const QImage&)));

    m_FaceIdentifyThread = new FaceIdentifyThread;
    //连接采图线程的发图信号到验证流程(RGB)
    connect(m_CapThread, SIGNAL(SendRGBData(const QImage&)),m_FaceIdentifyThread, SLOT(RecvRGBimg(const QImage&)));


    //m_FaceDrawDlg->move(30,10);
    //m_FaceDrawDlg->show();
    //做完所有操作开启采图线程
    m_CapThread->start();
}

BaiduFaceMainDialog::~BaiduFaceMainDialog()
{
    delete ui;
    //delete  m_FaceDrawDlg;
}
