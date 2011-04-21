#include "MemoryTableBusiness.h"
#include "DAO/DishMasterDAO.h"
#include <QStringList>
#include "DAO/TableInfoDAO.h"

QHash<QString,QString> MemoryTableBusiness::dishPictureMap;
QHash<QString,QString> MemoryTableBusiness::dishNameMap;
QHash<QString,QString> MemoryTableBusiness::dishTextMap;

QHash<QString,QStringList> MemoryTableBusiness::areaTableMap;
QHash<QString,QString> MemoryTableBusiness::tableAreaMap;

MemoryTableBusiness::MemoryTableBusiness()
{
}

void MemoryTableBusiness::initializeStaticData()
{
    QSettings settings("./Configure/UI/dish.ini",QSettings::IniFormat);
    QString prefixPath = settings.value("DishDisplay/dishPath_mini/prefix").toString();
    QString suffixPath = settings.value("DishDisplay/dishPath_mini/suffix").toString();

    DishMasterDAO allDishInfo;
    QStringList idList = allDishInfo.idsSelect();
    QStringList nameList = allDishInfo.namesSelect();
    for(int i=0;i<idList.size();i++) {
        QString key = idList.at(i);
        dishPictureMap.insert(key,prefixPath+key+suffixPath);
        dishNameMap.insert(key,nameList.at(i));
        dishTextMap.insert(key,allDishInfo.getDishText(key));
    }

    //���ŵ���������������໥ӳ��
    TableInfoDAO tblTableInfo;
    QStringList areaInfoList = tblTableInfo.areaInfoSelect();
    //�ø�����ѭ����������Ϣ����Ϊÿһ���Ψһ
    for(int i=0;i<areaInfoList.size();i++) {
        for(int j=0;j<areaInfoList.size();j++) {
            if( (i!=j) && (areaInfoList.at(i) == areaInfoList.at(j) ) ) {
                areaInfoList.removeAt(j);
                j--;
            }
        }
    }
    for(int i=0;i<areaInfoList.size();i++) {
        QString area = areaInfoList.at(i);
        QStringList areaTables = tblTableInfo.tableIDsSelect(area);
        areaTableMap.insert(area,areaTables);
        for(int i=0;i<areaTables.size();i++) {
            tableAreaMap.insert(areaTables.at(i),area);
        }
    }
}
