#ifndef BAIDUFACEMAINDIALOG_H
#define BAIDUFACEMAINDIALOG_H

#include <QDialog>

class FaceDrawDlg;
class CapThread;
class FaceIdentifyThread;


namespace Ui {
class BaiduFaceMainDialog;
}

class BaiduFaceMainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BaiduFaceMainDialog(QWidget *parent = nullptr);
    ~BaiduFaceMainDialog();

    //void closeEvent(QCloseEvent* e);
    //人脸(主界面)绘制窗口
    FaceDrawDlg* m_FaceDrawDlg;
    //视频采集线程
    CapThread* m_CapThread;
    //人脸验证线程
    FaceIdentifyThread* m_FaceIdentifyThread;
    //数据管理
    //
    //指静脉验证线程
    //
    //设备设置
    //
    //







private:
    Ui::BaiduFaceMainDialog *ui;
};

#endif // BAIDUFACEMAINDIALOG_H
