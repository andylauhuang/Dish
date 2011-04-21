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
    query.exec("DROP TABLE tblDish_master");//��Ʒ����ϸ��Ϣ���ݿ��

    query.exec("DROP TABLE tblTabel");//��λ����ϸ��Ϣ���ݿ��

    query.exec("DROP TABLE tblOrder_master");//�˿Ϳ��������ϸ��Ϣ
    query.exec("DROP TABLE tblOrder_detail");//�˿͵�˺����ϸ��Ϣ���ݿ��

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
               "VALUES ('00000001', 'ˮ����', '�����ɻ�������,�Ĵ��ɶ�������,����С����ĵ���',"
               "1)");

    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc,  intDish_type) "
               "VALUES ('00000005', '���㶹', '�й��ˣ�����һ����',"
               "1 )");
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc,intDish_type) "
               "VALUES ('00000006', '��ըС����', '�й��ˣ�����һ����',"
               "1)");
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_descintDish_type) "
               "VALUES ('00000007', '�ڽ�ţ��', '�й��ˣ�����һ����',"
               "1)");
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc, intDish_type) "
               "VALUES ('00000002', '������', '����԰�Ĳ�԰�����ĵ�����',"
               "1)");
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc, intDish_type) "
               "VALUES ('00000003', '��ľ��', '�й��ˣ�����һ����',"
               "1)");
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc, intDish_type) "
               "VALUES ('00000004', '�����Ƭ', '�й��ˣ�����һ����',"
               "1)");
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc, intDish_type) "
               "VALUES ('00000008', '�����۹�', '�й��ˣ�����һ����',"
               "1)");
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc, intDish_type) "
               "VALUES ('00000009', '�����Ź�', '�й��ˣ�����һ����',"
               "1)");
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc, intDish_type) "
               "VALUES ('00000010', '������', '�й��ˣ�����һ����',"
               " 1)");
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc, intDish_type) "
               "VALUES ('00000011', '����ͯ�Ӽ�', '�й��ˣ�����һ����',"
                       "1)");
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc, intDish_type) "
               "VALUES ('00000012', '�㴻��', '�й��ˣ�����һ����',"
               "1)");
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc, intDish_type) "
               "VALUES ('00010001','ëѪ��','�Ĵ���ɫ��',"
               "2)");
    query.exec("INSERT INTO tblDish_master (txtDish_id, txtDish_name, "
               "txtDish_desc, intDish_type) "
               "VALUES ('00010002','����','���־�Ʒ����',"
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
Description: �������ӵ�һ�����ݿ�
Called By: main�����е��ã��������ӵ����ݿ�
Input: ��
Output: ��
Return: �ɹ������ݿⷵ��true�����򷵻�false
************************************************/
inline bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("dish.db3");
    if (!db.open()) {
        QMessageBox::warning(0, QObject::tr("Database Error"),db.lastError().text());
        return false;
    }
    createTables();  //����ʱ���û�����ݿ���Դ򿪸�ע�ʹ���һ���нṹ�����ݵ����ݿ�
    return true;
}

#endif
