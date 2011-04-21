#ifndef DISH_H
#define DISH_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QMimeData>

class Dish : public QWidget
{
    Q_OBJECT
public:
    Dish(const QString &dishID,const QString &name,const QString &picturePath,
         int height,int width,QWidget *parent = 0);
private:
    void performDrag();

    QPoint startPos;
    QLabel *dishPictureLabel;
    int myWidth,myHeight;
    QString m_dishName,m_dishPicturePath;
    QRect dishPictureRect;
    QRect dishNameRect;
    QString dishName;
    QString myDishId;
    QPixmap thisPicture,darkPicture,smallPicture;
protected:
    void paintEvent(QPaintEvent *);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
signals:
    void bigPictureTextShow(QString);
};

#endif // DISH_H
