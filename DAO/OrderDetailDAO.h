#ifndef ORDERDETAILDAO_H
#define ORDERDETAILDAO_H

#include <QObject>
#include <QStringList>

class OrderDetailDAO : public QObject
{
public:
    OrderDetailDAO();
    bool oneItemWrite(int no,const QStringList &item);
};

#endif // ORDERDETAILDAO_H
