#ifndef DIALOGLOGINBUSINESS_H
#define DIALOGLOGINBUSINESS_H

#include <QObject>
#include <QByteArray>

class DialogLoginBusiness : public QObject
{
public:
    void infoWrite(const QString &orderID,const QString &tableID,
                   const QString &status);
    void setLogData(QString data);
    //void clearContent(QString orderID = QString());
    //void checkoutStatusWrite();
};

#endif // DIALOGLOGINBUSINESS_H
