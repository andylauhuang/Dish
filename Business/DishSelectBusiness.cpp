#include "DishSelectBusiness.h"
#include "DAO/DishMasterDAO.h"
#include "DAO/TableInfoDAO.h"
#include "DAO/OrderDetailDAO.h"
#include <QDataStream>
#include <QStringList>
#include <QSettings>
#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

/************************************************
Function: detailItemGet
Description: ���ݲ�Ʒid��ȡ��Ʒ��װxml�ĵ�һ���꾡item
Input: dishID����Ʒid��amount����Ʒ����������ЩorderDetail
    �ı�����Ϣ
Output: ��װ�õ�һ��item
************************************************/
QStringList DishSelectBusiness::detailItemGet(QString &dishID,int amount) const
{
    TableInfoDAO orderIdGet;

    QSettings settings("./Configure/Connection/Connection.ini",QSettings::IniFormat);
    QString orderID = settings.value("HttpPost/orderId").toString();

    if(orderID.isEmpty()) {
        qDebug()<<__FILE__<<__LINE__<<"The order_detail table can't be written because of the empty orderID!";
        return QStringList();
    }

    DishMasterDAO dishInfo;
    QStringList item;
    //item << QString::number(keyNum);
    item << orderID;
    item << dishID;
    item << QDateTime::currentDateTime().toString("yyyy-MM-dd h:m:s");
    item << QString::number(amount);
    item << "N";
    item << "";   //confirm ��
    double finalPrice = 20.0;
    item << QString::number(finalPrice);
    item << "Y";  //available: yes
    item << "y";
    item << "y";

    return item;
}

bool DishSelectBusiness::oneDishWrite(int no,const QStringList &item)
{
    OrderDetailDAO tblOrderDetail;
    return tblOrderDetail.oneItemWrite(no,item);
}

