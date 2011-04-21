#ifndef DISHPICTURETEXT_H
#define DISHPICTURETEXT_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPalette>
#include <QTimer>

class DishPictureText : public QWidget
{
    Q_OBJECT
public:
    DishPictureText(QWidget *parent = 0);
public slots:
    void showPicture(QString dishID);
    void showText(QString dishID);

protected:
    void resizeEvent(QResizeEvent *);

private:
    QLabel *dishPicture,*dishText;
    QPixmap *p;

    int w,h;
};

#endif // DISHPICTURETEXT_H
