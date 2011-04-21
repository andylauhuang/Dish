#ifndef MEMORYTABLEBUSINESS_H
#define MEMORYTABLEBUSINESS_H

#include <QObject>
#include <QHash>
#include <QSettings>

class MemoryTableBusiness : public QObject
{
public:
    MemoryTableBusiness();
    static void initializeStaticData();

    static QHash<QString,QString> dishPictureMap;
    static QHash<QString,QString> dishNameMap;
    static QHash<QString,QString> dishTextMap;

    static QHash<QString,QStringList> areaTableMap;
    static QHash<QString,QString> tableAreaMap;
};

#endif // MEMORYTABLEBUSINESS_H
