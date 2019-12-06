#include "CapThread.h"
#include "QImage"

#include "QDebug"

CapThread::CapThread()
{
    m_StopThreadFlag = false;


}

CapThread::~CapThread()
{
    StopCapThread();
    //如果异常退出析构时需要加判断，防止二次释放
    delete m_RGBQimg;
    delete m_IRQimg;
    delete [] m_ucharIR;
    delete [] m_ucharRGB;

}

int CapThread::CapThreadInit()
{
    //打开设备默认640,480
    m_CamIR =new cv::VideoCapture(1);
    m_CamRGB = new cv::VideoCapture(0);
    //设置摄像头分辨率
    //m_CamIR.set(CV_CAP_PROP_FRAME_WIDTH, 600);////可以显示 但8*6最小
    //m_CamIR.set(CV_CAP_PROP_FRAME_HEIGHT, 1023);
    //m_CamRGB.set(CV_CAP_PROP_FRAME_WIDTH, 600);////可以显示 但8*6最小
    //m_CamRGB.set(CV_CAP_PROP_FRAME_HEIGHT, 1023);

    printf("width = %.2f\n", m_CamIR->get(CV_CAP_PROP_FRAME_WIDTH));
    printf("height = %.2f\n", m_CamIR->get(CV_CAP_PROP_FRAME_HEIGHT));
    printf("width = %.2f\n", m_CamRGB->get(CV_CAP_PROP_FRAME_WIDTH));
    printf("height = %.2f\n", m_CamRGB->get(CV_CAP_PROP_FRAME_HEIGHT));


    m_ucharIR = new unsigned char[m_CapWidth * m_CapHeigth *3 ];
    m_ucharRGB = new unsigned char[m_CapWidth * m_CapHeigth *3 ];

    memset(m_ucharIR,0,m_CapWidth * m_CapHeigth *3);
    memset(m_ucharRGB,0,m_CapWidth * m_CapHeigth *3);

    m_IRQimg = new QImage(m_ucharIR, m_CapWidth,   m_CapHeigth, QImage::Format_RGB888);
    m_RGBQimg = new QImage(m_ucharIR, m_CapWidth,   m_CapHeigth, QImage::Format_RGB888);
    return 0;

}
void CapThread::run()
{
    //采集数据线程
    while (!m_StopThreadFlag) {

        *m_CamRGB >> m_RGBframe;
        *m_CamIR >> m_IRframe;

        //数据转换
        //Mat2QImage(m_IRframe,m_IRQimg);
        //Mat2QImage(m_RGBframe,m_RGBQimg);
        QImage qrgbimg = Mat2QImage(m_RGBframe);
        QImage qirimg = Mat2QImage(m_IRframe);
        //发射信号，带上一帧数据
        emit SendRGBData(qrgbimg);
        emit SendIRData(qirimg);
        //发送mat原始数据
        emit SendRGBData(m_RGBframe);
        emit SendIRData(m_IRframe);

    }

}

//void CapThread::Mat2QImage(const cv::Mat& cvmat, QImage* Qimg)
//{
////    cv::Mat des;

////    cv::resize(cvmat, des, cv::Size(Qimg->size().width(), Qimg->size().height()));

////    //颜色转换，QImage目前不支持 BGR888,所以需要转换，不然颜色次序不对

////    cv::cvtColor(des, cvmat, cv::COLOR_BGR2RGB);

////    //最后复制空间，这里要注意的是要保证Mat是连续空间（打开图像和视频默认都是连续空间），QImage也是连续空间（4的倍数）。

////    memcpy(Qimg->bits(), des.data, des.cols * des.rows * des.elemSize());


//    const uchar *pSrc = (const uchar*)cvmat.data;
//    // Create QImage with same dimensions as input Mat
//    QImage image(pSrc, cvmat.cols, cvmat.rows, cvmat.step, QImage::Format_RGB888);
//    memcpy(Qimg->bits(), pSrc, m_CapWidth*m_CapHeigth*3);
//    Qimg->rgbSwapped();


//}

QImage CapThread::Mat2QImage(const cv::Mat &cvMat)
{
    if(cvMat.type() == CV_8UC3)
    {
            //Copy input Mat
            const uchar *pSrc = (const uchar*)cvMat.data;
            // Create QImage with same dimensions as input Mat
            QImage image(pSrc, cvMat.cols, cvMat.rows, cvMat.step, QImage::Format_RGB888);
            return image.rgbSwapped();
    }
#ifdef _MYDEBUG_
    qDebug() << "Mat2QImg error";
    return QImage();
#endif
}

void CapThread::StopCapThread()
{
    m_StopThreadFlag = true;
}
