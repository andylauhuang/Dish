#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTextCodec>


inline void createTables()
{
    QSqlQuery query;
    query.exec("GEGIN");
//==============delete all the tables===========================
{
    query.exec("DROP TABLE tblDish_master");//菜品的详细信息数据库表

    query.exec("DROP TABLE tblTabel");//座位的详细信息数据库表

    query.exec("DROP TABLE tblOrder_master");//顾客开桌后的详细信息
    query.exec("DROP TABLE tblOrder_detail");//顾客点菜后的详细信息数据库表

}

//==============create all the tables(15)===========================
{
    query.exec("CREATE TABLE tblDish_master ("
               "txtDish_id VARCHAR(8) NOT NULL PRIMARY KEY, "
               "txtDish_name VARCHAR(50) NOT NULL, "
               "txtDish_desc VARCHAR(3000) NOT NULL, "
               "intDish_type SMALLINT)");
    query.exec("CREATE TABLE tblTabel ("
               "txtTable_id VARCHAR(4) NOT NULL PRIMARY KEY,"
               "txtType VARCHAR(2) NOT NULL,"
               "txtSeat_num INTEGER,"
               "txtStatus VARCHAR(1) NOT NULL,"
               "txtBookable_flag VARCHAR(1) NOT NULL,"
               "txtBook_status VARCHAR(1) NOT NULL)");

}

{
    query.exec("CREATE TABLE tblOrder_detail ("
               "intNo INTEGER PRIMARY KEY,"
               "txtOrder_id VARCHAR(15) NOT NULL, "
               "txtDish_id VARCHAR(8) NOT NULL, "
               "dteOrder_time DATETIME,"
               "intAmount   INTEGER,"
               "txtStatus VARCHAR(3) NOT NULL,"
               "txtConfirm VARCHAR(1) NOT NULL,"
               "decFinal_price DECIMAL(10,2),"
               "txtAvailable VARCHAR(10) NOT NULL,"
               "txtUpdate_user VARCHAR(8) NOT NULL,"
               "decUpdate_date DATETIME)");

    query.exec("CREATE TABLE tblOrder_master ("
               "txtOrder_id VARCHAR(15) PRIMARY KEY ,"
               "txtTable_id VARCHAR(4)  NOT NULL,"
               "txtDevice_id VARCHAR(15)  NOT NULL,"
               "txtWaiter_id VARCHAR(8)  NOT NULL,"
               "dteStart_order DATETIME,"
               "txtMember_id VARCHAR(15) NOT NULL,"
               "decTotal DECIMAL(10,2),"
               "txtAvailable VARCHAR(1) NOT NULL,"
               "txtStatus SMALLINT,"
               "intGuestAmount interger )");
}

//==============write data to the table that will be used===========================
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("gb2312"));
    QTextCodec::setCodecForTr( QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
{
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc, intDish_type) "
               "VALUES ('00000001', '水煮鱼', '东北松花江的鱼,四川成都的配料,北京小肥羊的调料',"
               "1)");

    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc,  intDish_type) "
               "VALUES ('00000005', '金豌豆', '中国菜，世界一绝！',"
               "1 )");
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc,intDish_type) "
               "VALUES ('00000006', '干炸小黄鱼', '中国菜，世界一绝！',"
               "1)");
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_descintDish_type) "
               "VALUES ('00000007', '黑椒牛柳', '中国菜，世界一绝！',"
               "1)");
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc, intDish_type) "
               "VALUES ('00000002', '地三鲜', '御花园的菜园培育的地三鲜',"
               "1)");
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc, intDish_type) "
               "VALUES ('00000003', '香木耳', '中国菜，世界一绝！',"
               "1)");
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc, intDish_type) "
               "VALUES ('00000004', '香煎肉片', '中国菜，世界一绝！',"
               "1)");
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc, intDish_type) "
               "VALUES ('00000008', '冰糖蜜果', '中国菜，世界一绝！',"
               "1)");
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc, intDish_type) "
               "VALUES ('00000009', '干烧排骨', '中国菜，世界一绝！',"
               "1)");
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc, intDish_type) "
               "VALUES ('00000010', '香玉米', '中国菜，世界一绝！',"
               " 1)");
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc, intDish_type) "
               "VALUES ('00000011', '红烧童子鸡', '中国菜，世界一绝！',"
                       "1)");
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc, intDish_type) "
               "VALUES ('00000012', '香椿肉', '中国菜，世界一绝！',"
               "1)");
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc, intDish_type) "
               "VALUES ('00010001','毛血旺','四川特色菜',"
               "2)");
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc, intDish_type) "
               "VALUES ('00010002','烤鱼','簋街精品烤鱼',"
               "2)");

    query.exec("INSERT INTO tblTabel ("
               "txtTable_id,txtType,txtSeat_num,txtStatus,txtBookable_flag,txtBook_status)"
               "VALUES('0001','AA',10,'C','Y','N')");
    query.exec("INSERT INTO tblTabel ("
               "txtTable_id,txtType,txtSeat_num,txtStatus,txtBookable_flag,txtBook_status)"
               "VALUES('0002','AA',10,'C','Y','N')");
    query.exec("INSERT INTO tblTabel ("
               "txtTable_id,txtType,txtSeat_num,txtStatus,txtBookable_flag,txtBook_status)"
               "VALUES('0003','AA',10,'C','Y','N')");
    query.exec("INSERT INTO tblTabel ("
               "txtTable_id,txtType,txtSeat_num,txtStatus,txtBookable_flag,txtBook_status)"
               "VALUES('0004','AA',10,'C','Y','N')");
    query.exec("INSERT INTO tblTabel ("
               "txtTable_id,txtType,txtSeat_num,txtStatus,txtBookable_flag,txtBook_status)"
               "VALUES('0005','AA',10,'C','Y','N')");
    query.exec("INSERT INTO tblTabel ("
               "txtTable_id,txtType,txtSeat_num,txtStatus,txtBookable_flag,txtBook_status)"
               "VALUES('0006','AA',10,'C','Y','N')");
    query.exec("INSERT INTO tblTabel ("
               "txtTable_id,txtType,txtSeat_num,txtStatus,txtBookable_flag,txtBook_status)"
               "VALUES('0007','AA',10,'C','Y','N')");
    query.exec("INSERT INTO tblTabel ("
               "txtTable_id,txtType,txtSeat_num,txtStatus,txtBookable_flag,txtBook_status)"
               "VALUES('0008','AA',10,'C','Y','N')");
    query.exec("INSERT INTO tblTabel ("
               "txtTable_id,txtType,txtSeat_num,txtStatus,txtBookable_flag,txtBook_status)"
               "VALUES('0009','AA',10,'C','Y','N')");
    query.exec("INSERT INTO tblTabel ("
               "txtTable_id,txtType,txtSeat_num,txtStatus,txtBookable_flag,txtBook_status)"
               "VALUES('0010','AA',15,'C','Y','N')");
    query.exec("INSERT INTO tblTabel ("
               "txtTable_id,txtType,txtSeat_num,txtStatus,txtBookable_flag,txtBook_status)"
               "VALUES('0011','AA',15,'C','Y','N')");
    query.exec("INSERT INTO tblTabel ("
               "txtTable_id,txtType,txtSeat_num,txtStatus,txtBookable_flag,txtBook_status)"
               "VALUES('0012','AA',15,'C','Y','N')");
    query.exec("INSERT INTO tblTabel ("
               "txtTable_id,txtType,txtSeat_num,txtStatus,txtBookable_flag,txtBook_status)"
               "VALUES('0013','AA',15,'C','Y','N')");
    query.exec("INSERT INTO tblTabel ("
               "txtTable_id,txtType,txtSeat_num,txtStatus,txtBookable_flag,txtBook_status)"
               "VALUES('0014','AA',15,'C','Y','N')");
    query.exec("INSERT INTO tblTabel ("
               "txtTable_id,txtType,txtSeat_num,txtStatus,txtBookable_flag,txtBook_status)"
               "VALUES('0015','AA',15,'C','Y','N')");
    query.exec("INSERT INTO tblTabel ("
               "txtTable_id,txtType,txtSeat_num,txtStatus,txtBookable_flag,txtBook_status)"
               "VALUES('0016','AA',15,'C','Y','N')");
    query.exec("INSERT INTO tblTabel ("
               "txtTable_id,txtType,txtSeat_num,txtStatus,txtBookable_flag,txtBook_status)"
               "VALUES('0017','AA',8,'C','Y','N')");
    query.exec("INSERT INTO tblTabel ("
               "txtTable_id,txtType,txtSeat_num,txtStatus,txtBookable_flag,txtBook_status)"
               "VALUES('0018','BB',6,'C','Y','N')");
    query.exec("INSERT INTO tblTabel ("
               "txtTable_id,txtType,txtSeat_num,txtStatus,txtBookable_flag,txtBook_status)"
               "VALUES('0019','BB',6,'C','Y','N')");
}
   query.exec("COMMIT");
}
/************************************************
Function: createConnection
Description: 用于连接到一个数据库
Called By: main函数中调用，用于连接到数据库
Input: 无
Output: 无
Return: 成功打开数据库返回true，否则返回false
************************************************/
inline bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("dish.db3");
    if (!db.open()) {
        QMessageBox::warning(0, QObject::tr("Database Error"),db.lastError().text());
        return false;
    }
    createTables();  //调试时如果没有数据库可以打开该注释创建一个有结构无内容的数据库
    return true;
}

#endif
