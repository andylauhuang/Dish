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
    //���ò����ɽ�����ק�¼�
    setAcceptDrops(true);
    myDishId=dishID;
    thisPicture.load(picturePath);
    dishName=name;

    dishPictureLabel = new QLabel(this);
    dishPictureLabel->setGeometry(0,0,150,145*7/10);
    dishPictureLabel->setScaledContents(true);

    //׼����קʱ���û�ͼƬ
    QPainter painter;
    darkPicture = thisPicture;
    painter.begin(&darkPicture);
    painter.fillRect(darkPicture.rect(), QColor(127, 127, 127, 127));
    painter.end();

    //׼��Сͼ
    smallPicture = thisPicture.scaled(30,30);

    QBitmap maskBitmap(150, 145);//maskBitmap������û�б���ʼ��
    maskBitmap.clear();//����maskBitmap������Ϊ0

    QPainter p(&maskBitmap);
    p.setBrush(Qt::black);
    p.drawEllipse(0,0,150,145*7/10);
    p.drawRect(0,145*7/10,150,3*145/10);
    p.end();
    this->setMask(maskBitmap);
}

void Dish::paintEvent(QPaintEvent *)
{
    //����Ҫ��ʾ��ͼƬ�����ݺͲ�������Ϣ
    dishPictureRect.setRect(0,0,150,145*7/10);
    dishNameRect.setRect(0,145*7/10,150,145*3/10);
    QPainter painter(this);
    painter.drawPixmap(dishPictureRect,thisPicture);
    QFont font("Arial",12,QFont::Bold);
    painter.setFont(font);
    painter.drawText(dishNameRect,Qt::AlignHCenter | Qt::AlignVCenter,dishName);

}

/************************************************
Function: dropEvent�����¶����¼�
Description: �϶�ʱ�����������Զ����ø��¼�����
Input: event�����������¼�
Output: ��
Return: ��
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
Function: dragEnterEvent���϶����������¼�
Description: ֻ����ָ�����͵Ĳ����϶���ĳ���򡣵���ק�Ǳ���
    �Լ�ʱ����������MoveAction����������������࣬��
Input: event���������������¼�
Output: ��
Return: ��
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
Function: dragMoveEvent���϶�����¼�
Description:
Input:
Output: ��
Return: ��
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
Function: mousePressEvent��������¼�
Description: ����ĳһ��ʱ�������Դ�ͼ��ʾ��
Input: event��QMouseEvent�¼������
Output: ��
Return: ��
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
    //������קʱ����ۡ��������ݵ���Ϣ
    QMimeData *mimeData = new QMimeData;
    mimeData->setText(myDishId);
    qDebug()<<"myDishId is"<<myDishId;
    //׼��drag
    QDrag *drag = new QDrag(this);
    drag->setPixmap(smallPicture);
    drag->setHotSpot(QPoint(15, 15));
    drag->setMimeData(mimeData);

    //ִ����ק��������Ӧ��ƷͼƬ�ı仯
    dishPictureLabel->setPixmap(darkPicture);
    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) != Qt::MoveAction)
       dishPictureLabel->setPixmap(thisPicture);
}
