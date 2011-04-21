#include <QPainter>
#include <QSettings>
#include <QtDebug>
#include <QPalette>
#include <QBitmap>
#include "SelectedDishItem.h"

SelectedDishItem::SelectedDishItem(const QString &picturePath,QWidget *parent)
    :QWidget(parent),picturePath(picturePath),itemHeight(86)
{

}

void SelectedDishItem::setBackgroundColor(int number)
{
    QPalette pal;
    switch(number) {
        case 1:
        pal.setBrush(QPalette::Window,QBrush(QColor(255,255,255)));
        break;
        case 2:
        pal.setBrush(QPalette::Window,QBrush(QColor(246,246,246)));
        break;
    }
    setPalette(pal);
    setAutoFillBackground(true);
}

void SelectedDishItem::setPosition(QVector<QPair<int,int> > rectVector)
{
    if( rectVector.size() == 2) {
        for(int i=0;i<rectVector.size();i++) {
            positionRectVector.append(rectVector.at(i));
        }
    }
    else {
        qDebug() <<__FILE__<<__LINE__<< "item size wrong! size is:"<<rectVector.size();
        return;
    }
    // These code is used to draw a ellipse picture
    QBitmap maskBitmap(width(), height());
    maskBitmap.clear();

    int pictureWidth = positionRectVector.at(0).first;
    QPainter p(&maskBitmap);
    p.setBrush(Qt::black);
    p.drawEllipse(0,0,pictureWidth,itemHeight);
    p.drawRect(pictureWidth,0,width()-pictureWidth,itemHeight);
    p.end();

    setMask(maskBitmap);
}
//说明：通过setItem函数设置5个待显示的选项；通过id自动转化成菜品名字。所以这个item总共需要6个string信息
void SelectedDishItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int pictureWidth = positionRectVector.at(0).first;

    painter.drawPixmap(0,0,pictureWidth,itemHeight,QPixmap(picturePath));
    for(int i = 0;i<item.size();i++) {
        int x = positionRectVector.at(i).first;
        int w = positionRectVector.at(i).second;
        painter.drawText(x,0,w,itemHeight,Qt::AlignHCenter | Qt::AlignVCenter,item.at(i));
    }
}

