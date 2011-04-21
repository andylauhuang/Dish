#include <QSqlTableModel>
#include <QSqlRecord>
#include <QtDebug>
#include "TableInfoDAO.h"

TableInfoDAO::TableInfoDAO()
{
}

bool TableInfoDAO::orderMasterWrite(QStringList &item)
{
    if(item.size() < 10) {
        qDebug()<<__FILE__<<__LINE__<<"Wrong! item less than the ordermaster item!";
        return false;
    }
    QSqlTableModel model;
    model.setTable("tblOrder_master");
    model.setEditStrategy(QSqlTableModel::OnManualSubmit);
    model.insertRows(0,1);
    for(int i = 0;i<item.size();i++) {
        model.setData(model.index(0,i),item.at(i));
    }
    model.submitAll();
    return true;
}

bool TableInfoDAO::tableStatusWrite(const QString &tableID,const QString &status)
{
    QSqlTableModel model;
    model.setTable("tblTabel");
    model.setFilter(tr("txtTable_id = '%1'").arg(tableID));
    model.select();
    if(model.rowCount() > 0) {
        QSqlRecord record = model.record(0);
        record.setValue("txtStatus",status);
        model.setRecord(0,record);
        model.submitAll();
    }
    return true;
}

//��ȡ������(AA,BB)����ӵ���ķ�����id
QStringList TableInfoDAO::tableIDsSelect(QString area)
{
    QSqlTableModel model;
    QStringList ID;
    model.setTable("tblTabel");
    model.setFilter(tr("txtType = '%1'").arg(area));
    model.select();
    for(int i=0;i<model.rowCount();i++) {
        ID << model.record(i).value("txtTable_id").toString();
    }
    return ID;
}

//��ȡ�����ֲ�������������������ΪAA��BB
QStringList TableInfoDAO::areaInfoSelect()
{
    QSqlTableModel model;
    QStringList table;
    model.setTable("tblTabel");
    model.setFilter("txtType<>\"\"");
    model.select();
    for(int i=0;i<model.rowCount();i++) {
        table << model.record(i).value("txtType").toString();
    }
    return table;
}

//��ȡ������ӵ�е���λ�ĸ���,��һ�ŷ����������ɵ�����
QStringList TableInfoDAO::seatNumSelect()
{
   QSqlTableModel model;
   QStringList table;
   model.setTable("tblTabel");
   model.setFilter("txtSeat_num<>\"\"");
   model.select();
   for(int i=0;i<model.rowCount();i++) {
       table << QString::number(model.record(i).value("txtSeat_num").toInt());
   }
   return table;
}

/*QStringList TableInfoDAO::allTableID()
{
    QSqlTableModel model;
    QStringList tableIdList;
    model.setTable("tblDevice");
    model.setFilter("txtTable_id<>\"\"");
    model.select();
    for(int i=0;i<model.rowCount();i++) {
        tableIdList << model.record(i).value("txtTable_id").toString();
    }
    return tableIdList;
}*/
