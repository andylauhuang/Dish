#include "DishPictureText.h"
#include <QPainter>
#include "Business/MemoryTableBusiness.h"
#include <QDebug>

DishPictureText::DishPictureText(QWidget *parent)
    :QWidget(parent),dishPicture(new QLabel(this)),dishText(new QLabel(this)),
    p(new QPixmap)
{
    dishText->setAlignment(Qt::AlignTop);
    setAutoFillBackground(true);

}
void DishPictureText::resizeEvent(QResizeEvent *)
{
    w = width();
    h = height();
}

void DishPictureText::showPicture(QString dishID)
{
    p->load(MemoryTableBusiness::dishPictureMap.value(dishID));
    dishPicture->setPixmap(*p);

    QPainter painter;
    painter.begin(p);
    //painter.fillRect(p->rect(),QColor(100,100,100,100));
    painter.fillRect(p->rect(),QColor(200,200,200,200));
    //painter.fillRect(p->rect(),QColor(80,80,80,80));
    painter.end();

    QPalette pal;
    pal.setBrush(QPalette::Window,QBrush(QPixmap(*p)));
    setPalette(pal);

    int startX = (w - p->width())/2;
    int startY = (h - p->height())/2;
    dishPicture->setGeometry(startX,startY,p->width(),p->height());
    dishText->hide();
    dishPicture->show();
}

void DishPictureText::showText(QString dishID)
{
    QString text = MemoryTableBusiness::dishTextMap.value(dishID);
    text.prepend("<h1><B><font color = black>");
    text.append("</font></B></h1>");
    dishText->setText(text);
    dishText->setGeometry(0,0,w,h);
    dishPicture->hide();
    dishText->show();
    //qDebug()<<dishText->font();
}
