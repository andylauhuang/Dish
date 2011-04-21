#include "DialogLoginBusiness.h"
#include <QDataStream>
#include <QDateTime>
#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QSettings>
#include "DAO/TableInfoDAO.h"


void DialogLoginBusiness::infoWrite(const QString &orderID,const QString &tableID,
                                    const QString &status)
{
    TableInfoDAO orderMaster;
    QStringList item;
    item << orderID<< tableID << "" << "" <<
            QDateTime::currentDateTime().toString("yyyy-MM-dd h:m:s") <<
            "" << "0" << status << "0" << "5";
    orderMaster.orderMasterWrite(item);
    orderMaster.tableStatusWrite(tableID,status);

    QString tmp;
    tmp.append("[����]  ���ţ�");
    tmp.append(tableID+";"+"��ˮ��:"+orderID+";");
    setLogData(tmp);
}

void DialogLoginBusiness::setLogData(QString data)
{
    QFile log("log.txt");
    if (log.open(QFile::WriteOnly | QFile::Append)) {
         QTextStream in(&log);
         in << "\r\n" << QDateTime::currentDateTime().toString("yyyy��MM��dd��  hh:mm:ss");
         in << "\r\n" << data << "\r\n";
         in << endl;
    }
    log.close();
}
