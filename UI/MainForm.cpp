#include "MainForm.h"
#include "ui_MainForm.h"
#include "DishDisplay.h"
#include <QSettings>
#include "Business/MemoryTableBusiness.h"
#include "Business/DishSelectBusiness.h"


MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{

    setAutoFillBackground(true);
    ui->setupUi(this);

    DishDisplayBusiness displayDish;
    QByteArray info = displayDish.allInfoGet();
    QDataStream dataStream(&info,QIODevice::ReadOnly);
    QStringList dishKinds;
    dataStream >> dishKinds;
    if(dishKinds.isEmpty())
        return;

    //创建几种可点菜的选项卡页面
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(currentWidget()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(currentWidget()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(currentWidget()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(currentWidget()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(currentWidget()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(currentWidget()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(currentWidget()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(currentWidget()));
    ui->stackedWidget->removeWidget(ui->page_2);
    delete ui->page_2;
    ui->stackedWidget->removeWidget(ui->page);
    delete ui->page;
    //qDebug()<<dishKinds;
    QStringList allDishIds;
    for(int i=0;i<dishKinds.size();++i)
    {
        dataStream >> allDishIds;
        //qDebug()<<allDishIds;
        DishDisplay *dishBoard = new DishDisplay(allDishIds);
        ui->stackedWidget->addWidget(dishBoard);
        qDebug()<<ui->stackedWidget->count();
        connect(dishBoard,SIGNAL(showBigPictureText(QString)),
                this,SLOT(pictureTextShow(QString)));
    }
    for(int count=dishKinds.size();count<7;count++)
    {
        ui->stackedWidget->addWidget(new QWidget(this));
    }

    selected=new SelectedDishDisplay();
    ui->stackedWidget->addWidget(selected);

    setUiSkin();

    //开桌功能
    ui->checkOut->hide();
    ui->openDesk->show();
    winLogin=new DialogLogin(this);

    connect(ui->openDesk,SIGNAL(clicked()),this,SLOT(openDesk()));
    connect(winLogin,SIGNAL(deviceSelected(QString)),this,SLOT(getTableInfo(QString)));


    //点菜按钮
    ui->dishPicture->hide();
    ui->introduce->hide();
    ui->selecteDish->hide();
    connect(ui->selecteDish,SIGNAL(clicked()),this,SLOT(selecteDish()));
    connect(ui->dishPicture,SIGNAL(clicked()),this,SLOT(dishPicture()));
    connect(ui->introduce,SIGNAL(clicked()),this,SLOT(introduce()));


    ui->dragEnterArea->setAcceptDrops(true);
    setAcceptDrops(true);
    //this->setAcceptDrops(true);

    //菜品介绍
    dishShow = new DishPictureText(this);
    dishShow->setGeometry(0,ui->pushButton_1->y()+ui->pushButton_1->height(),
                          ui->stackedWidget->width(),ui->stackedWidget->height());
    dishShow->hide();


    //幻灯播放功能
    pptDisplay=new ppt(this);
    pptDisplay->hide();
    timerInterval=6000;
    autoShowTimer = new QTimer(this);
    autoShowTimer->start(timerInterval);
    pptDisplay->hide();
    connect(autoShowTimer,SIGNAL(timeout()),this,SLOT(setAutoShow()));
    connect(pptDisplay,SIGNAL(hided()),autoShowTimer,SLOT(start()));
    //pptDisplay->show();
    //pptDisplay->setAutoShow(true);
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainForm::currentWidget()
{
    dishShow->hide();
    ui->dragEnterArea->show();
    ui->dishPicture->hide();
    ui->introduce->hide();
    ui->selecteDish->hide();
    //获得的哪个按钮按下，并显示它所对应的窗口
    QString name = QObject::sender()->objectName();
    int index = name.at(name.size()-1).digitValue()-1;
    if(index==3)
    {
        ui->dishPicture->hide();
        ui->introduce->hide();
        ui->dragEnterArea->hide();
    }


    ui->stackedWidget->setCurrentIndex(index);

}

void MainForm::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

/************************************************
Function: dropEvent，放下对象事件
Description: 拖动时部件被放下自动调用该事件函数,即对点菜的
    处理，将已点菜的信息写入数据库
Input: event，部件放下事件，
Output: 无
Return: 无
************************************************/
void MainForm::dropEvent(QDropEvent *event)
{
    QRect dragRect(ui->dragEnterArea->x(),ui->dragEnterArea->y(),
                   ui->dragEnterArea->width(),ui->dragEnterArea->height());

    QString dishID;
    //================================================================================
    if (event->mimeData()->hasText())
          dishID = event->mimeData()->text();
    //================================================================================
    else
        qDebug()<<"Can't get the dishid when drop!";
    if(dragRect.contains(mapFromGlobal(QCursor::pos())))
    {
        currentDishID = dishID;
        selecteDish();
        qDebug()<<dishID;
    }
    event->setDropAction(Qt::CopyAction);
    event->accept();

}

void MainForm::pictureTextShow(QString dishID)
{
    QString tmp = MemoryTableBusiness::dishNameMap.value(dishID);
    //setLogData("【菜品图文显示操作】  菜品名:"+tmp);

    //PRINT()<<"Show:"<<dishID;
    currentDishID = dishID;
    //QSettings settings0("./Configure/UI/dish.ini",QSettings::IniFormat);
    //settings0.setValue("MainWindow/dishPicture/currentID",dishID);

    ui->dragEnterArea->hide();
    ui->selecteDish->show();
    ui->dishPicture->hide();
    ui->introduce->show();
    dishShow->show();
    dishShow->setGeometry(0,ui->pushButton_1->y()+ui->pushButton_1->height(),
                          ui->stackedWidget->width(),ui->stackedWidget->height());
    //isNewShow = true;
    dishPicture();
}
void MainForm::dishPicture()
{
    //QString tmp = MemoryTableBusiness::dishNameMap.value(currentDishID);
    //setLogData("【菜品图片显示操作】  菜品名:"+tmp);

    //QSettings settings("./Configure/UI/dish.ini",QSettings::IniFormat);
    //QString soundPath = settings.value("MainWindow/dishPicture/sound").toString();
    //QSound::play(soundPath);

    //ui->introduce->show();
    ui->dishPicture->hide();
    ui->introduce->show();

    dishShow->showPicture(currentDishID);
    //dishShow->showText(currentDishID);
}

void MainForm::introduce()
{
    ui->introduce->hide();
    ui->dishPicture->show();
    dishShow->showText(currentDishID);
}

void MainForm::selecteDish()
{
    selected->addItem(currentDishID,1);
    DishSelectBusiness detailItem;
    selecteDishItem = detailItem.detailItemGet(currentDishID,1);

    //Write into the database, when the server don't response,this item will be deleted
    DishSelectBusiness selectedWrite;
    selectedWrite.oneDishWrite(0,selecteDishItem);
}

void MainForm::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(6,0,942,56,buttonGroupBackground);
}

void MainForm::mousePressEvent(QMouseEvent *event)
{
    //qDebug()<<__FILE__<<__LINE__<<"The position is:"<<event->pos();
    pptDisplay->setAutoShow(false);
    autoShowTimer->stop();
    autoShowTimer->start(timerInterval);
    QWidget::mousePressEvent(event);
}

void MainForm::setAutoShow()
{
    pptDisplay->setAutoShow(true);
    autoShowTimer->stop();
}

void MainForm::openDesk()
{
    winLogin->show();
}

void MainForm::getTableInfo(QString tableID)
{
    this->tableID = tableID;
    ui->openDesk->hide();
    ui->checkOut->show();
    qDebug()<<"tableID"<<tableID;
}

void MainForm::setUiSkin()
{
    QSettings settings("./Configure/UI/dish.ini",QSettings::IniFormat);
    QString picturePath = settings.value("MainWindow/topButtonGroup/backgroundImage").toString();
    buttonGroupBackground.load(picturePath);

    QString path;
    path = settings.value("MainWindow/mainDishBoard/pushButton1/NormalIcon").toString();
    pushButton1Normal.load(path);
    path = settings.value("MainWindow/mainDishBoard/pushButton1/SelectedIcon").toString();
    pushButton1Selected.load(path);
    path = settings.value("MainWindow/mainDishBoard/pushButton2/NormalIcon").toString();
    pushButton2Normal.load(path);
    path = settings.value("MainWindow/mainDishBoard/pushButton2/SelectedIcon").toString();
    pushButton2Selected.load(path);
    path = settings.value("MainWindow/mainDishBoard/pushButton3/NormalIcon").toString();
    pushButton3Normal.load(path);
    path = settings.value("MainWindow/mainDishBoard/pushButton3/SelectedIcon").toString();
    pushButton3Selected.load(path);
    path = settings.value("MainWindow/mainDishBoard/pushButton4/NormalIcon").toString();
    pushButton4Normal.load(path);
    path = settings.value("MainWindow/mainDishBoard/pushButton4/SelectedIcon").toString();
    pushButton4Selected.load(path);
    path = settings.value("MainWindow/mainDishBoard/pushButton5/NormalIcon").toString();
    pushButton5Normal.load(path);
    path = settings.value("MainWindow/mainDishBoard/pushButton5/SelectedIcon").toString();
    pushButton5Selected.load(path);
    path = settings.value("MainWindow/mainDishBoard/pushButton6/NormalIcon").toString();
    pushButton6Normal.load(path);
    path = settings.value("MainWindow/mainDishBoard/pushButton6/SelectedIcon").toString();
    pushButton6Selected.load(path);
    path = settings.value("MainWindow/mainDishBoard/pushButton7/NormalIcon").toString();
    pushButton7Normal.load(path);
    path = settings.value("MainWindow/mainDishBoard/pushButton7/SelectedIcon").toString();
    pushButton7Selected.load(path);
    path = settings.value("MainWindow/mainDishBoard/pushButton8/NormalIcon").toString();
    pushButton8Normal.load(path);
    path = settings.value("MainWindow/mainDishBoard/pushButton8/SelectedIcon").toString();
    pushButton8Selected.load(path);

    ui->pushButton_1->setIconSize(QSize(134,46));
    ui->pushButton_1->setIcon(QIcon(pushButton1Normal));
    ui->pushButton_1->setFlat(true);
    ui->pushButton_2->setIconSize(QSize(111,46));
    ui->pushButton_2->setIcon(QIcon(pushButton2Normal));
    ui->pushButton_2->setFlat(true);
    ui->pushButton_3->setIconSize(QSize(111,46));
    ui->pushButton_3->setIcon(QIcon(pushButton3Normal));
    ui->pushButton_3->setFlat(true);
    ui->pushButton_4->setIconSize(QSize(111,46));
    ui->pushButton_4->setIcon(QIcon(pushButton4Normal));
    ui->pushButton_4->setFlat(true);
    ui->pushButton_5->setIconSize(QSize(111,46));
    ui->pushButton_5->setIcon(QIcon(pushButton5Normal));
    ui->pushButton_5->setFlat(true);
    ui->pushButton_6->setIconSize(QSize(111,46));
    ui->pushButton_6->setIcon(QIcon(pushButton6Normal));
    ui->pushButton_6->setFlat(true);
    ui->pushButton_7->setIconSize(QSize(111,46));
    ui->pushButton_7->setIcon(QIcon(pushButton7Normal));
    ui->pushButton_7->setFlat(true);
    ui->pushButton_8->setIconSize(QSize(136,46));
    ui->pushButton_8->setIcon(QIcon(pushButton8Normal));
    ui->pushButton_8->setFlat(true);

    path = settings.value("MainWindow/callWaiter/normalIcon").toString();
    callWaiterNormal.load(path);
    path = settings.value("MainWindow/callWaiter/selectedIcon").toString();
    callWaiterSelected.load(path);
    path = settings.value("MainWindow/openDesk/normalIcon").toString();
    openDeskNormal.load(path);
    path = settings.value("MainWindow/openDesk/selectedIcon").toString();
    openDeskSelected.load(path);
    path = settings.value("MainWindow/checkOut/normalIcon").toString();
    checkOutNormal.load(path);
    path = settings.value("MainWindow/checkOut/selectedIcon").toString();
    checkOutSelected.load(path);
    path = settings.value("MainWindow/dishPicture/normalIcon").toString();
    dishPictureNormal.load(path);
    path = settings.value("MainWindow/dishPicture/activeIcon").toString();
    dishPictureSelected.load(path);
    path = settings.value("MainWindow/introduce/normalIcon").toString();
    introduceNormal.load(path);
    path = settings.value("MainWindow/introduce/selectedIcon").toString();
    introduceSelected.load(path);
    path = settings.value("MainWindow/selecteDish/normalIcon").toString();
    selecteDishNormal.load(path);
    path = settings.value("MainWindow/selecteDish/selectedIcon").toString();
    selecteDishSelected.load(path);

    ui->callWaiter->setFlat(true);
    ui->callWaiter->setIconSize(QSize(98,63));
    ui->callWaiter->setIcon(QIcon(callWaiterNormal));
    ui->openDesk->setFlat(true);
    ui->openDesk->setIconSize(QSize(120,65));
    ui->openDesk->setIcon(QIcon(openDeskNormal));
    ui->checkOut->setFlat(true);
    ui->checkOut->setIconSize(QSize(120,65));
    ui->checkOut->setIcon(QIcon(checkOutNormal));
    ui->dishPicture->setFlat(true);
    ui->dishPicture->setIconSize(QSize(75,38));
    ui->dishPicture->setIcon(QIcon(dishPictureNormal));
    ui->introduce->setFlat(true);
    ui->introduce->setIconSize(QSize(75,38));
    ui->introduce->setIcon(QIcon(introduceNormal)); 
    ui->selecteDish->setFlat(true);
    ui->selecteDish->setIconSize(QSize(75,38));
    ui->selecteDish->setIcon(QIcon(selecteDishNormal));

    path = settings.value("MainWindow/dragArea/normalIcon").toString();
    dragAreaNormal.load(path);
    path = settings.value("MainWindow/dragArea/selectedIcon").toString();
    dragAreaSelected.load(path);
    ui->dragEnterArea->setPixmap(dragAreaNormal);
    ui->stackedWidget->setFrameStyle(QFrame::NoFrame);
}




