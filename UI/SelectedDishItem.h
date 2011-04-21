#ifndef SELECTEDDISHITEM_H
#define SELECTEDDISHITEM_H

#include <QWidget>
#include <QStringList>
#include <QRect>
#include <QVector>
#include <QColor>

class SelectedDishItem : public QWidget
{
public:
    SelectedDishItem(const QString &picturePath,QWidget *parent = 0);
    void setPosition(QVector< QPair<int,int> > rectVector);
    void setItemHeight(int h) {itemHeight = h;}
    void setBackgroundColor(int number);
    void setItem(QStringList &item) {this->item.clear();this->item << item;}
protected:
    void paintEvent(QPaintEvent *event);
private:
    QColor backGroundColor;
    QStringList item;
    QVector<QPair<int,int> > positionRectVector;
    //bool isSimple;
    QString picturePath;
    int dishNameX,mainChoiceNameX,subChoiceNameX,avoidNameX,amount;
    int itemHeight;
    int itemWidth,pictureWidth;
};

#endif // SELECTEDDISHITEM_H
