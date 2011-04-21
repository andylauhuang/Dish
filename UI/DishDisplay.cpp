#include "DishDisplay.h"
#include "Business/MemoryTableBusiness.h"
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QDebug>

DishDisplay::DishDisplay(QStringList allDishIds, QWidget *parent):QWidget(parent)
{
    if(allDishIds.isEmpty())
        return;
    setAutoFillBackground(true);
    int lineNumber = 5;
    int rowNumber = 3;
    int myWidth = 1024;
    int myHeight = 481;
    int dishWidth = 150;
    int dishHeight = 145;

    scrollArea=new QScrollArea(this);
    scrollArea->setGeometry(0,0,myWidth,481);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollAreaWidget=new QWidget();

    int hSpace = (myWidth-35-dishWidth*lineNumber)/(lineNumber+1);
    int vSpace = (myHeight - dishHeight*rowNumber)/( rowNumber + 1 );

    for(int i=0;i<allDishIds.size();++i)
    {
        QString dishID = allDishIds.at(i);
        QString dishPicturePath=MemoryTableBusiness::dishPictureMap.value(dishID);
        QString dishName = MemoryTableBusiness::dishNameMap.value(dishID);
        Dish *dish = new Dish(dishID,dishName,dishPicturePath,dishWidth,dishHeight,scrollAreaWidget);
        //手工控制每个菜品的绝对位置
        dish->setGeometry(hSpace+(i%lineNumber)*(hSpace+dishWidth),
                          vSpace+(i/lineNumber)*(vSpace+dishHeight),dishWidth,dishHeight);
        connect(dish,SIGNAL(bigPictureTextShow(QString)),this,SIGNAL(showBigPictureText(QString)));

    }

    /*Dish *dish1=new Dish("1","../Configure/images/00000001_big.jpg",150,145,scrollAreaWidget);
    Dish *dish2=new Dish("2","../Configure/images/00000002_big.jpg",150,145,scrollAreaWidget);
    Dish *dish3=new Dish("1","../Configure/images/00000001_big.jpg",150,145,scrollAreaWidget);
    Dish *dish4=new Dish("2","../Configure/images/00000002_big.jpg",150,145,scrollAreaWidget);

    dish1->setGeometry(10,10,150,145);
    dish2->setGeometry(10,160,150,145);
    dish3->setGeometry(10,310,150,145);
    dish4->setGeometry(10,460,150,145);*/


    scrollAreaWidget->adjustSize();
    scrollArea->setWidget(scrollAreaWidget);

    setAcceptDrops(true);
}

void DishDisplay::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}
void DishDisplay::dropEvent(QDropEvent *event)
{
    QString dishID;
    if (event->mimeData()->hasText())
    {
        dishID=event->mimeData()->text();
    }
    qDebug()<<"bei xuan zhong de id"<<dishID;

     emit showBigPictureText(dishID);
}
