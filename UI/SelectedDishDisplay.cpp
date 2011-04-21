#include "SelectedDishDisplay.h"
#include "ui_SelectedDishDisplay.h"
//#include "Business/DishSelectBusiness.h"
#include "Business/DishDisplayBusiness.h"
#include "Business/MemoryTableBusiness.h"
#include <QLabel>
#include <QByteArray>
#include <QStringList>
#include <QDataStream>
#include <QSettings>
#include <QtDebug>

SelectedDishDisplay::SelectedDishDisplay(QWidget *parent):
        QWidget(parent),ui(new Ui::SelectedDishDisplay)
{
    ui->setupUi(this);
    QFont font;
    font.setPointSize(16);
    this->setFont(font);
    scrollArea=new QScrollArea(this);
    scrollArea->setGeometry(0,33,1000,448);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollAreaWidget=new QWidget();


}

void SelectedDishDisplay::addItem(QString dishID,int amount)
{
    QString dishPicturePath = MemoryTableBusiness::dishPictureMap.value(dishID);
    QString dishName = MemoryTableBusiness::dishNameMap.value(dishID);
    QStringList choiceItem;
    int itemHeight = 115;
    int m = showStore.size();
    choiceItem << dishName<<QString::number(amount);
    static int colorKind = 1;
    SelectedDishItem *s = new SelectedDishItem(dishPicturePath,scrollAreaWidget);
    s->setItemHeight(itemHeight);
    s->setBackgroundColor(colorKind);
    colorKind++;
    if( colorKind == 3)
        colorKind = 1;
    s->setGeometry(ui->label->x(),m*itemHeight,ui->label_2->x()+ui->label_2->width()-ui->label->x(),
                   itemHeight);
    QVector< QPair<int,int> > rectVector(2);
    rectVector[0] = qMakePair(ui->label_1->x(),ui->label_1->width());
    rectVector[1] = qMakePair(ui->label_2->x(),ui->label_2->width());
    s->setPosition(rectVector);
    s->setItem(choiceItem);
    showStore.append(s);

    scrollAreaWidget->adjustSize();
    scrollArea->setWidget(scrollAreaWidget);

}

void SelectedDishDisplay::showContent()
{
    /*for(int i=0;i<showStore.size();++i) {
        showStore.at(i)->show();
    }*/
    //ui->scrollAreaWidget->adjustSize();
    //ui->scrollArea->setWidget(ui->scrollAreaWidget);
}









