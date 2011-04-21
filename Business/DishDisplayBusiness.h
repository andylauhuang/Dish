#ifndef DISHDISPLAYBUSINESS_H
#define DISHDISPLAYBUSINESS_H

#include <QObject>
#include <QByteArray>
#include <QDebug>
#include "DAO/DishMasterDAO.h"

class DishDisplayBusiness : public QObject
{
public:
    DishDisplayBusiness();
    QByteArray allInfoGet();

};

#endif // DISHDISPLAYBUSINESS_H
