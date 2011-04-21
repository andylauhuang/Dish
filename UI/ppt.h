#ifndef PPT_H
#define PPT_H

#include <QtGui/QWidget>
#include <QTimer>
#include <QPainter>
#include <QRect>
#include <QHashIterator>
#include "Business/MemoryTableBusiness.h"


namespace Ui {
    class ppt;
}

class ppt : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(ppt)
public:
    explicit ppt(QWidget *parent = 0);
    virtual ~ppt();

    void setAutoShow(bool flag);
    void setUiSkin();
    void setLogData(QString);
signals:
    void hided();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    virtual void changeEvent(QEvent *e);

private slots:
    void showNext();//��ʾ�õ�Ƭ�е���һ��ͼƬ
    void showPrevious();//��ʾ�õ�Ƭ�е���һ��ͼƬ
    void setPause();//��ͣ�õ�Ƭ�ķ�ӳ
    void setContinue();//�����õ�Ƭ�ķ�ӳ
    void exitPlay();//�˳��õ�Ƭ�ķ�ӳ
private:
    Ui::ppt *ui;
    QTimer *timer;
    QPixmap *p;
    bool isAuto;
    QHashIterator<QString, QString> *dishPictureMap;
    QStringList picturePath;
    int max,current;

};

#endif // PPT_H
