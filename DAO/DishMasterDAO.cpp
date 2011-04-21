#include <QSqlTableModel>
#include <QSqlRecord>
#include <QString>
#include "DishMasterDAO.h"

DishMasterDAO::DishMasterDAO()
{
}

//获取数据库中所有的菜的initDish_type属性值，也就是菜的种类（有雷同的种类）
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

//获取数据库中某一种类（initDish_type）菜的所有的菜的id号
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

//获取数据库中所有菜的id号
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

//获取id号对应的菜的菜名
QStringList DishMasterDAO::namesSelect()
{
    QStringList IDs = idsSelect();
    return idToName(IDs);
}

//从id到菜名的转换，即从id获得它的菜名
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
