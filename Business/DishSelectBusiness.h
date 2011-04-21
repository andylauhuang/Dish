#ifndef DISHSELECTBUSINESS_H
#define DISHSELECTBUSINESS_H

#include <QObject>
#include <QByteArray>

class DishSelectBusiness : public QObject
{
public:
    DishSelectBusiness(){}
    QStringList detailItemGet(QString &dishID,int amount) const;
    bool oneDishWrite(int no,const QStringList &item);

    void setLogData(QString data);
};

#endif // DISHSELECTBUSINESS_H
