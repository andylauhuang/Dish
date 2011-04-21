#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>
#include <QLabel>
#include <QSettings>
#include <QPixmap>
#include <QPushButton>

namespace Ui {
    class DialogLogin;
}

class DialogLogin : public QDialog
{
    Q_OBJECT
    Q_DISABLE_COPY(DialogLogin)
public:
    explicit DialogLogin(QWidget *parent = 0);
    virtual ~DialogLogin();
protected:
    virtual void changeEvent(QEvent *e);
signals:
    void deviceSelected(QString tableInfo);
    //void clearSelectedShow();
public slots:
    void addAmount();
    void decAmount();
    void areaToTable(QString area);
    void tableToArea(QString tableID);
    void itemsSelected();
    void openTableResult(QString orderID,char status);
    void setUiSkin();
    void setLogData(QString data);


private:
    Ui::DialogLogin *ui;
    int number;
};

#endif // DIALOGLOGIN_H
