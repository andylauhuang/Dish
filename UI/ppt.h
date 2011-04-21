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
    void showNext();//显示幻灯片中的下一张图片
    void showPrevious();//显示幻灯片中的上一张图片
    void setPause();//暂停幻灯片的放映
    void setContinue();//继续幻灯片的放映
    void exitPlay();//退出幻灯片的放映
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
