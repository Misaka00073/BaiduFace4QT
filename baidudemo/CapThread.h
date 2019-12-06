#ifndef CAPTHREAD_H
#define CAPTHREAD_H

#include "QThread"
#include "opencv2\opencv.hpp"

class QImage;


//使用opencv打开双摄像头
class CapThread : public QThread
{
    Q_OBJECT
public:
     CapThread();
    ~CapThread();
    //初始化线程
    int CapThreadInit();

    //采集线程 //只有run在新的线程中
    virtual void run();
    //cv的mat转QImage
    //void Mat2QImage(const cv::Mat& cvmat, QImage* Qimg);
    static QImage Mat2QImage(const cv::Mat& cvMat);
    //停止线程
    void StopCapThread();

public:
    //其余控制变量

    //线程停止flag
    bool m_StopThreadFlag;


    cv::VideoCapture *m_CamRGB;
    cv::VideoCapture *m_CamIR;
    //数据帧，rgb数据存储在mat的data中或者使用Mat::read(unsigned char*)读取数据
    cv::Mat m_RGBframe;
    cv::Mat m_IRframe;

    //mat2Qimg用,信号发射带出一帧图像
    QImage* m_IRQimg;
    QImage* m_RGBQimg;
    //一帧图像的buff
    unsigned char* m_ucharIR;
    unsigned char* m_ucharRGB;

    //摄像头宽高
    int m_CapWidth;
    int m_CapHeigth;


signals:
    //有图像数发送图像数据
    void SendRGBData(const QImage& RGBimg);
    void SendIRData(const QImage& IRimg);
    void SendRGBData(const cv::Mat& MatRGBimg);
    void SendIRData(const cv::Mat& MatIRimg);

};

#endif // CAPTHREAD_H
