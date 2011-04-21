#ifndef DISHDISPLAY_H
#define DISHDISPLAY_H

#include <QWidget>
#include <QScrollArea>

#include "Dish.h"

class DishDisplay : public QWidget
{
    Q_OBJECT
public:
    DishDisplay(QStringList allDishIds,QWidget *parent = 0);
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidget;
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
signals:
    void showBigPictureText(QString dishID);
};

#endif // DISHDISPLAY_H
