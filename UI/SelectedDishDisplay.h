#ifndef SELECTEDDISHDISPLAY_H
#define SELECTEDDISHDISPLAY_H

#include <QWidget>
#include <QList>
#include <QLabel>
#include <QList>
#include "SelectedDishItem.h"
#include <QScrollArea>

namespace Ui {
    class SelectedDishDisplay;
}

class SelectedDishDisplay : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(SelectedDishDisplay)
public:
    explicit SelectedDishDisplay(QWidget *parent = 0);

public slots:
    void addItem(QString dishID,int amount);
    void showContent();
private:
    Ui::SelectedDishDisplay *ui;
    QList <SelectedDishItem *> showStore;
    QStringList itemList;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidget;
};

#endif // SELECTEDDISHDISPLAY_H
