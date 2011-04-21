#include "DialogLogin.h"
#include "ui_DialogLogin.h"
#include "Business/MemoryTableBusiness.h"
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include "Business/DialogLoginBusiness.h"


DialogLogin::DialogLogin(QWidget *parent)
        :QDialog(parent,Qt::Dialog | Qt::FramelessWindowHint),number(5)
{
    ui=new Ui::DialogLogin;
    ui->setupUi(this);

    QStringList areaInfo,deskInfo;
    QHashIterator<QString, QStringList> i(MemoryTableBusiness::areaTableMap);
    while (i.hasNext()) {
        i.next();
        areaInfo << i.key();
        deskInfo << i.value();
    }
    ui->areaInfoBox->addItems(areaInfo);
    ui->deskInfoBox->addItems(deskInfo);
    ui->lineEdit->setText(QString::number(number));

    connect(ui->areaInfoBox,SIGNAL(currentIndexChanged(QString)),
            this,SLOT(areaToTable(QString)));
    connect(ui->deskInfoBox,SIGNAL(currentIndexChanged(QString)),
            this,SLOT(tableToArea(QString)));

    connect(ui->addButton,SIGNAL(clicked()),this,SLOT(addAmount()));
    connect(ui->decButton,SIGNAL(clicked()),this,SLOT(decAmount()));
    connect(ui->okButton,SIGNAL(clicked()),this,SLOT(itemsSelected()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(hide()));

    setUiSkin();
}

DialogLogin::~DialogLogin()
{
    delete ui;
}

void DialogLogin::areaToTable(QString area)
{
    disconnect(ui->deskInfoBox,SIGNAL(currentIndexChanged(QString)),
               this,SLOT(tableToArea(QString)));
    qDebug()<<__FILE__<<__LINE__<<"The area is:"<<area;
    if(!MemoryTableBusiness::areaTableMap.contains(area))
        return;
    QStringList tableList = MemoryTableBusiness::areaTableMap.value(area);
    ui->deskInfoBox->clear();
    ui->deskInfoBox->addItems(tableList);

    connect(ui->deskInfoBox,SIGNAL(currentIndexChanged(QString)),
            this,SLOT(tableToArea(QString)));
}

void DialogLogin::tableToArea(QString tableID)
{
    disconnect(ui->areaInfoBox,SIGNAL(currentIndexChanged(QString)),
               this,SLOT(areaToTable(QString)));
    qDebug()<<__FILE__<<__LINE__<<"The tableID is:"<<tableID;
    if(!MemoryTableBusiness::tableAreaMap.contains(tableID))
        return;
    QString area = MemoryTableBusiness::tableAreaMap.value(tableID);
    ui->areaInfoBox->clear();
    ui->areaInfoBox->addItem(area);

    connect(ui->areaInfoBox,SIGNAL(currentIndexChanged(QString)),
            this,SLOT(tableToArea(QString)));
}

void DialogLogin::addAmount()
{
    number++;
    ui->lineEdit->setText(QString::number(number));
}

void DialogLogin::decAmount()
{
    if(number<1)
        return;
    number--;
    ui->lineEdit->setText(QString::number(number));
}

void DialogLogin::itemsSelected()
{
    QString orderID;
    QString tableID = ui->deskInfoBox->currentText();
    emit deviceSelected(tableID);

    QString tmp;
    tmp.append("【开桌操作】  ");
    tmp.append("桌号:"+tableID+"人数:"+QString::number(number)+";");
    setLogData(tmp);
    QSettings settings("./Configure/Connection/Connection.ini",QSettings::IniFormat);
    orderID=settings.value("HttpPost/orderId").toString();
    openTableResult(orderID,'Y');
    hide();
}

void DialogLogin::openTableResult(QString orderID,char status)
{
    QSettings settings("./Configure/Connection/Connection.ini",QSettings::IniFormat);
    QString tableID = ui->deskInfoBox->currentText();
    DialogLoginBusiness dataWrite;
    int orderIDnew=orderID.toInt()+1;
    orderID=QString::number(orderIDnew);
    dataWrite.infoWrite(orderID,tableID,"Y");
    settings.setValue("HttpPost/orderId",orderID);
}

void DialogLogin::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void DialogLogin::setUiSkin()
{
    QSettings settings("./Configure/UI/dish.ini",QSettings::IniFormat);
    QString path;

    ui->addButton->setFlat(true);
    ui->decButton->setFlat(true);
    ui->okButton->setFlat(true);
    ui->cancelButton->setFlat(true);

    QLabel *label=new QLabel(this);
    label->setGeometry(0,0,400,25);
    path=settings.value("DialogLogin/head/picturePath").toString();
    label->setPixmap(QPixmap(path));
    label->setScaledContents(true);

    //设置DialogLogin对话框的关闭按钮
    QPushButton *button=new QPushButton(this);
    button->setGeometry(365,0,25,25);
    button->setIconSize(QSize(25,25));
    path = settings.value("DialogLogin/closeButton/picturePath").toString();
    button->setIcon(QIcon(path));
    button->setFlat(true);
    connect(button,SIGNAL(clicked()),this,SLOT(hide()));
}

void DialogLogin::setLogData(QString data)
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
