#include "Dish.h"
#include <QBitmap>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QDebug>

Dish::Dish(const QString &dishID,const QString &name, const QString &picturePath, int height, int width, QWidget *parent)
    :QWidget(parent),m_dishName(name),m_dishPicturePath(picturePath)
{
    //设置部件可接收拖拽事件
    setAcceptDrops(true);
    myDishId=dishID;
    thisPicture.load(picturePath);
    dishName=name;

    dishPictureLabel = new QLabel(this);
    dishPictureLabel->setGeometry(0,0,150,145*7/10);
    dishPictureLabel->setScaledContents(true);

    //准备拖拽时的置灰图片
    QPainter painter;
    darkPicture = thisPicture;
    painter.begin(&darkPicture);
    painter.fillRect(darkPicture.rect(), QColor(127, 127, 127, 127));
    painter.end();

    //准备小图
    smallPicture = thisPicture.scaled(30,30);

    QBitmap maskBitmap(150, 145);//maskBitmap的像素没有被初始化
    maskBitmap.clear();//设置maskBitmap的像素为0

    QPainter p(&maskBitmap);
    p.setBrush(Qt::black);
    p.drawEllipse(0,0,150,145*7/10);
    p.drawRect(0,145*7/10,150,3*145/10);
    p.end();
    this->setMask(maskBitmap);
}

void Dish::paintEvent(QPaintEvent *)
{
    //设置要显示的图片的内容和菜名等信息
    dishPictureRect.setRect(0,0,150,145*7/10);
    dishNameRect.setRect(0,145*7/10,150,145*3/10);
    QPainter painter(this);
    painter.drawPixmap(dishPictureRect,thisPicture);
    QFont font("Arial",12,QFont::Bold);
    painter.setFont(font);
    painter.drawText(dishNameRect,Qt::AlignHCenter | Qt::AlignVCenter,dishName);

}

/************************************************
Function: dropEvent，放下对象事件
Description: 拖动时部件被放下自动调用该事件函数
Input: event，部件放下事件
Output: 无
Return: 无
************************************************/
void Dish::dropEvent(QDropEvent *event)
{
    //emit txtchange(myDishId);
    dishPictureLabel->setPixmap(thisPicture);

    if (event->source() == this)
    {
        emit bigPictureTextShow(myDishId);
    }      
    else
        event->ignore();
}
/************************************************
Function: dragEnterEvent，拖动进入区域事件
Description: 只接受指定类型的部件拖动到某区域。当拖拽是本类
    自己时，把它动作MoveAction来处理，如果是其它类，则
Input: event，部件进入区域事件
Output: 无
Return: 无
************************************************/
void Dish::dragEnterEvent(QDragEnterEvent *event)
{
    Dish *source = qobject_cast<Dish *>(event->source());
    if(source && source == this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
        event->acceptProposedAction();
}
/************************************************
Function: dragMoveEvent，拖动鼠标事件
Description:
Input:
Output: 无
Return: 无
************************************************/
void Dish::dragMoveEvent(QDragMoveEvent *event)
{
    Dish *source = qobject_cast<Dish *>(event->source());
    if(source && source == this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
        event->acceptProposedAction();
}
/************************************************
Function: mousePressEvent，鼠标点击事件
Description: 单击某一项时，该项以大图显示；
Input: event，QMouseEvent事件类对象
Output: 无
Return: 无
************************************************/
void Dish::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        startPos = event->pos();
    }
    QWidget::mousePressEvent(event);
}
void Dish::mouseReleaseEvent(QMouseEvent *event)
{
    int distance = (event->pos() - startPos).manhattanLength();
    if(distance <=5)
    {
        emit bigPictureTextShow(myDishId);
    }

}
void Dish::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        int distance = (event->pos() - startPos).manhattanLength();
        if (distance >= QApplication::startDragDistance())
            performDrag();
    }
    QWidget::mouseMoveEvent(event);
}

void Dish::performDrag()
{
    //设置拖拽时的外观、数据内容等信息
    QMimeData *mimeData = new QMimeData;
    mimeData->setText(myDishId);
    qDebug()<<"myDishId is"<<myDishId;
    //准备drag
    QDrag *drag = new QDrag(this);
    drag->setPixmap(smallPicture);
    drag->setHotSpot(QPoint(15, 15));
    drag->setMimeData(mimeData);

    //执行拖拽动作被对应菜品图片的变化
    dishPictureLabel->setPixmap(darkPicture);
    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) != Qt::MoveAction)
       dishPictureLabel->setPixmap(thisPicture);
}
