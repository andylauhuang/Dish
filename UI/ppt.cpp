#include "ppt.h"
#include "ui_ppt.h"
#include <QSettings>
#include <QMouseEvent>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QtDebug>

#define PRINT() qDebug()<<__FILE__<<__LINE__

ppt::ppt(QWidget *parent) :
    QWidget(parent),ui(new Ui::ppt),timer(new QTimer(this)),
    p(new QPixmap),isAuto(false)
{
    ui->setupUi(this);

    timer->setInterval(2500);

    QSettings settings("./Configure/UI/dish.ini",QSettings::IniFormat);
    QString prefixPath = settings.value("PPT/dishPath_mini/prefix").toString();
    QString suffixPath = settings.value("PPT/dishPath_mini/suffix").toString();
    max = settings.value("PPT/pathMaxNo").toInt();
    for(int i=0;i<max;i++) {
        QString tmp = QString::number(i+1);
        tmp.append(suffixPath);
        tmp.prepend(prefixPath);
        picturePath.append(tmp);
    }
    current = 0;
    qDebug()<<"picturePath is"<<picturePath;
    connect(timer,SIGNAL(timeout()),this,SLOT(showNext()));
    connect(ui->exitButton,SIGNAL(clicked()),this,SLOT(exitPlay()));
    connect(ui->downButton,SIGNAL(clicked()),this,SLOT(showNext()));
    connect(ui->upButton,SIGNAL(clicked()),this,SLOT(showPrevious()));
    connect(ui->pauseButton,SIGNAL(clicked()),this,SLOT(setPause()));
    connect(ui->autoPlay,SIGNAL(clicked()),this,SLOT(setContinue()));

    setUiSkin();
}

ppt::~ppt()
{
    delete ui;

}
void ppt::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),*p);
}
void ppt::mousePressEvent(QMouseEvent *event)
{
    static bool flag = true;
    if(flag) {
        setPause();
        flag = false;
    }
    else {
        setContinue();
        flag = true;
    }
    QWidget::mousePressEvent(event);

}
void ppt::setAutoShow(bool flag)
{
    if(flag) {
        this->showFullScreen();
        timer->start();

        setLogData("【幻灯自动播放】");
    }
    else {
        this->hide();
        timer->stop();

        setLogData("【幻灯自动播放停止】");
    }
    ui->autoPlay->hide();
    ui->pauseButton->show();
    PRINT()<<"The auto show!";

}
void ppt::showNext()
{
    if (current +1 <= max) {
        current++;
    }
    else
    {
        current = 1;
    }
    p->load(picturePath.at(current-1));
    qDebug()<<"jiazaitupianchenggong"<<p->load(picturePath.at(current-1));
    update();
}
void ppt::showPrevious()
{
    if (current - 1 >= 0) {
       current--;
    }
    else
        current = max -1;
    p->load(picturePath.at(current));
    update();
}
void ppt::setPause()
{
    ui->autoPlay->show();
    ui->pauseButton->hide();
    timer->stop();
}
void ppt::setContinue()
{
    ui->autoPlay->hide();
    ui->pauseButton->show();
    timer->start();
}
void ppt::exitPlay()
{
    this->hide();
    timer->stop();
    emit hided();
}
void ppt::changeEvent(QEvent *e)
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
void ppt::setUiSkin()
{
    QSettings settings("./Configure/UI/dish.ini",QSettings::IniFormat);
    QString path = settings.value("PPT/previousLabel/picturePath").toString();
    ui->upButton->setIcon(QIcon(path));
    ui->upButton->setFlat(true);

    path = settings.value("PPT/nextLabel/picturePath").toString();
    ui->downButton->setIcon(QIcon(path));
    ui->downButton->setFlat(true);

    path = settings.value("PPT/autoPlay/picturePath").toString();
    ui->autoPlay->setIcon(QIcon(path));
    ui->autoPlay->setFlat(true);

    path = settings.value("PPT/exitButton/picturePath").toString();
    ui->exitButton->setIcon(QIcon(path));
    ui->exitButton->setFlat(true);

    path = settings.value("PPT/pauseButton/picturePath").toString();
    ui->pauseButton->setIcon(QIcon(path));
    ui->pauseButton->setFlat(true);
}

//向文件中写入一些信息
void ppt::setLogData(QString data)
{
    QFile log("log.txt");
    if (log.open(QFile::WriteOnly | QFile::Append)) {
         QTextStream in(&log);
         in << "\r\n" << QDateTime::currentDateTime().toString("yyyy年MM月dd日  hh:mm:ss");
         in << "\r\n" << data << "\r\n";
         in << endl;
    }
    log.close();
}
