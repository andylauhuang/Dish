#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include "Dish.h"
#include <QScrollArea>
#include "Business/DishDisplayBusiness.h"
#include <QStringList>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMouseEvent>
#include "DishPictureText.h"
#include "SelectedDishDisplay.h"
#include <QPushButton>
#include "ppt.h"

#include "UI/DialogLogin.h"


namespace Ui {
    class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(MainForm)
public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

protected:
    void changeEvent(QEvent *e);
    //void paintEvent(QPaintEvent *);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *);

private:
    Ui::MainForm *ui;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidget;
    DishPictureText *dishShow;
    QString currentDishID;
    QStringList selecteDishItem;
    QPixmap pixmap;

    SelectedDishDisplay *selected;

    ppt *pptDisplay;
    int selectedIndex,timerInterval;
    QTimer *autoShowTimer;
    QString tableID;

    //选中和不选中哪个button时的不同的反应时用到的图标
    QPushButton *selectedTabButton;
    QPixmap selectedTabIcon;
    QPixmap pushButton1Normal,pushButton1Selected;
    QPixmap pushButton2Normal,pushButton2Selected;
    QPixmap pushButton3Normal,pushButton3Selected;
    QPixmap pushButton4Normal,pushButton4Selected;
    QPixmap pushButton5Normal,pushButton5Selected;
    QPixmap pushButton6Normal,pushButton6Selected;
    QPixmap pushButton7Normal,pushButton7Selected;
    QPixmap pushButton8Normal,pushButton8Selected;

    QPixmap openDeskNormal,openDeskSelected;
    QPixmap callWaiterNormal,callWaiterSelected;
    QPixmap checkOutNormal,checkOutSelected;
    QPixmap dishPictureNormal,dishPictureSelected;
    QPixmap introduceNormal,introduceSelected;
    QPixmap selecteDishNormal,selecteDishSelected;

    QPixmap dragAreaNormal,dragAreaSelected;

    QPixmap buttonGroupBackground;

    DialogLogin *winLogin;
public slots:
    void getTableInfo(QString tableID);

    void currentWidget();
    void pictureTextShow(QString dishID);
    void dishPicture();
    void selecteDish();

    void setUiSkin();
    void introduce();

    void openDesk();//开桌功能

    void setAutoShow();
};

#endif // MAINFORM_H
