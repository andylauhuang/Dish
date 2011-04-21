#include <QSqlTableModel>
#include <QSqlRecord>
#include <QString>
#include "DishMasterDAO.h"

DishMasterDAO::DishMasterDAO()
{
}

//��ȡ���ݿ������еĲ˵�initDish_type����ֵ��Ҳ���ǲ˵����ࣨ����ͬ�����ࣩ
QStringList DishMasterDAO::getAllKinds()
{
    QSqlTableModel model;
    QStringList idList;
    model.setTable("tblDish_master");
    model.setFilter("intDish_type <> 0");
    model.select();
    for(int i=0;i<model.rowCount();i++) {
        idList << model.record(i).value("intDish_type").toString();
    }
    return idList;
}

//��ȡ���ݿ���ĳһ���ࣨinitDish_type���˵����еĲ˵�id��
QStringList DishMasterDAO::getDishID(int dishKind)
{
    QSqlTableModel model;
    QStringList idList;
    model.setTable("tblDish_master");
    model.setFilter(tr("intDish_type = %1").arg(dishKind));
    model.select();
    for(int i=0;i<model.rowCount();i++)
    {
        idList << model.record(i).value("txtDish_id").toString();
    }

    return idList;
}

//��ȡ���ݿ������в˵�id��
QStringList DishMasterDAO::idsSelect()
{
    QSqlTableModel model;
    QStringList idList;
    model.setTable("tblDish_master");
    model.setFilter("txtDish_id<>\"\"");
    model.select();
    for(int i=0;i<model.rowCount();i++)
    {
        idList << model.record(i).value("txtDish_id").toString();
    }
    qDebug()<<idList;
    return idList;
}

//��ȡid�Ŷ�Ӧ�Ĳ˵Ĳ���
QStringList DishMasterDAO::namesSelect()
{
    QStringList IDs = idsSelect();
    return idToName(IDs);
}

//��id��������ת��������id������Ĳ���
QStringList DishMasterDAO::idToName(const QStringList &IDs)
{
    QSqlTableModel model;
    QStringList name;
    model.setTable("tblDish_master");
    for(int i=0;i<IDs.size();++i)
    {
        model.setFilter(tr("txtDish_id = '%1'").arg(IDs.at(i)));
        model.select();
        name << model.record(0).value("txtDish_name").toString();
    }
    return name;
}

QString DishMasterDAO::getDishText(const QString &dishID)
{
    QString text;
    QSqlTableModel model;

    model.setTable("tblDish_master");
    model.setFilter(tr("txtDish_id = '%1'").arg(dishID));
    model.select();
    text = model.record(0).value("txtDish_desc").toString();

    return text;
}
