#ifndef DISHMASTERDAO_H
#define DISHMASTERDAO_H

#include <QObject>
#include <QStringList>
#include <QtDebug>

class DishMasterDAO : public QObject
{
public:
    DishMasterDAO();
    QStringList getAllKinds();
    QStringList getDishID(int dishKind);
    QStringList idsSelect();
    QStringList namesSelect();
    QString getDishText(const QString &dishID);
    QStringList idToName(const QStringList &IDs);
};

#endif // DISHMASTERDAO_H
