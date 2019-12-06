#include "FaceIdentifyThread.h"
#include <CapThread.h>
#include <QDebug>

//百度sdk
#include <baidu_face_api.h>


FaceIdentifyThread::FaceIdentifyThread(/*CapThread* CapThread*/)
{

    //m_pCapThread = CapThread;
    //连接采图线程的发图信号
    //connect(m_pCapThread, &CapThread::SendRGBData,this, &FaceIdentifyThread::RecvRGBimg);

    //BaiduFaceApi *baiduapi = new BaiduFaceApi();

    //m_baiduapi = new BaiduFaceApi;
    //int ret = m_baiduapi->sdk_init();
    //提前加载人脸库到内存
    //m_baiduapi->load_db_face();

}

void FaceIdentifyThread::run()
{

}
//原始RGB数据入口
void FaceIdentifyThread::RecvRGBimg(const QImage &qRGBimg)
{
#ifdef _MYDEBUG_
    qDebug() << "FaceIdentifyThread::RecvRGBimg";
    qDebug() << qRGBimg.size();
#endif
    m_CurrentQRGBimg = qRGBimg;
}
//原始IR数据入口
void FaceIdentifyThread::RecvIRimg(const QImage &qIRimg)
{
#ifdef _MYDEBUG_
    qDebug() << "FaceIdentifyThread::RecvRGBimg";
    qDebug() << qIRimg.size();
#endif
    m_CurrentQIRimg = qIRimg;
}
