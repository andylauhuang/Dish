#ifndef TABLEINFODAO_H
#define TABLEINFODAO_H

#include <QObject>
#include <QStringList>

class TableInfoDAO : public QObject
{
public:
    TableInfoDAO();
    QStringList tableIDsSelect(QString area);
    QStringList areaInfoSelect();//区域信息
    QStringList seatNumSelect();//座位数量信息
    bool orderMasterWrite(QStringList &);
    bool tableStatusWrite(const QString &tableID,const QString &status);

    //QStringList allTableID();//所有饭桌信息
};

#endif // TABLEINFODAO_H
