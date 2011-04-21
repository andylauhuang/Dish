#include "DishDisplayBusiness.h"

DishDisplayBusiness::DishDisplayBusiness()
{
}

QByteArray DishDisplayBusiness::allInfoGet()
{
    QByteArray allDishInfo;
    DishMasterDAO tblDishMaster;

    //��ȡ���ݿ���iniDish_type����������ʹ��Ψһ
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
    return allDishInfo;//�������ݿ���ĳһ�֣�iniDish_type���˵����������Ӧ�����еĲ˵�id
}
