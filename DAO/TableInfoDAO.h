#ifndef TABLEINFODAO_H
#define TABLEINFODAO_H

#include <QObject>
#include <QStringList>

class TableInfoDAO : public QObject
{
public:
    TableInfoDAO();
    QStringList tableIDsSelect(QString area);
    QStringList areaInfoSelect();//������Ϣ
    QStringList seatNumSelect();//��λ������Ϣ
    bool orderMasterWrite(QStringList &);
    bool tableStatusWrite(const QString &tableID,const QString &status);

    //QStringList allTableID();//���з�����Ϣ
};

#endif // TABLEINFODAO_H
