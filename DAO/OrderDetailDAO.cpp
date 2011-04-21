#include "OrderDetailDAO.h"
#include <QSettings>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTime>
#include <QStringList>
#include <QString>
#include <QtDebug>



OrderDetailDAO::OrderDetailDAO()
{
}

//直接按接收的数据插入，不做数据长度的检查，前面有几项插入几项，这样更为灵活
bool OrderDetailDAO::oneItemWrite(int no,const QStringList &item)
{
    bool flag = true;
    int size = item.size();
    Q_ASSERT(size >= 10);
    qDebug()<<__FILE__<<__LINE__<<"The item that DAO get is:"<<item;

    QSqlTableModel model;
    model.setTable("tblOrder_detail");
    if(!model.insertRows(0,1))
        flag = false;
    model.setData(model.index(0,0),no);
    for(int i=0;i<size;i++) {
        if(!model.setData(model.index(0,i+1),item.at(i)))
            flag = false;
    }
    if(!model.submitAll())
        flag = false;
    return flag;
}
