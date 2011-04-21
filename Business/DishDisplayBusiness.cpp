#include "DishDisplayBusiness.h"

DishDisplayBusiness::DishDisplayBusiness()
{
}

QByteArray DishDisplayBusiness::allInfoGet()
{
    QByteArray allDishInfo;
    DishMasterDAO tblDishMaster;

    //获取数据库中iniDish_type的种数，并使其唯一
    QStringList allKinds = tblDishMaster.getAllKinds();
    for(int i=0;i<allKinds.size();i++)
    {
        for(int j=0;j<allKinds.size();j++)
        {
            if( i != j && allKinds.at(i) == allKinds.at(j) )
            {
                allKinds.removeAt(j);
                j--;
            }
        }
    }


    QDataStream dataStream(&allDishInfo,QIODevice::WriteOnly);
    if(!allKinds.isEmpty())
    {
        dataStream << allKinds;
        for(int i=0;i<allKinds.size();++i)
        {
            dataStream << tblDishMaster.getDishID(allKinds.at(i).toInt());
        }
    }
    return allDishInfo;//返回数据库中某一种（iniDish_type）菜的种类和它对应的所有的菜的id
}
