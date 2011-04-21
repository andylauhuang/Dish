#include <QtGui/QApplication>
#include "UI/MainForm.h"
#include "DAO/Connection.h"
#include <QTextCodec>
#include "Business/MemoryTableBusiness.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr( QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

    if (!createConnection())
        return 1;

    MemoryTableBusiness::initializeStaticData();
    MainForm w;
    w.show();
    return a.exec();
}
