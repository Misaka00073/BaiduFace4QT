#ifndef FACEIDENTIFYTHREAD_H
#define FACEIDENTIFYTHREAD_H

#include <QObject>
#include <QThread>

#include <FaceFingerDef.h>
#include <QImage>
#include <QPixmap>

class CapThread;
class BaiduFaceApi;

class FaceIdentifyThread : public QThread
{
    Q_OBJECT
public:
     FaceIdentifyThread(/*CapThread* CapThread*/);
    void run();

    QString RGBIdent();



public slots:
    void RecvRGBimg(const QImage &qRGBimg);
    void RecvIRimg(const QImage &qIRimg);
public:
    //CapThread* m_pCapThread;
    BaiduFaceApi* m_baiduapi;

private:
    //保存当前RGB帧数据
    QImage m_CurrentQRGBimg;
    //保存当前IR帧数据
    QImage m_CurrentQIRimg;




signals:
    void SendIdentifyResult(const IdentifyResult);//发送识别结果




};

#endif // FACEIDENTIFYTHREAD_H
