#ifndef KEYVALUEITEMWIDGET_H
#define KEYVALUEITEMWIDGET_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidgetItem>
#include "specialitemwidget.h"

/*
    The class of QListWidgetItem in the QListWidget.
    It's the implemention of SpecialItemWidget.
    This class stores the item about key-value pair sending.
*/
class KeyValueItemWidget : public SpecialItemWidget
{
    Q_OBJECT
public:
    explicit KeyValueItemWidget(QWidget *parent = nullptr);
    bool isFileItemWidget();
    bool isKeyValueItemWidget();
    QString getKey();
    QString getValue();

private:
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QLabel *keyLabel = new QLabel("Key:", this);
    QLineEdit *keyInput = new QLineEdit(this);
    QLabel *valueLabel = new QLabel("Value:", this);
    QLineEdit *valueInput = new QLineEdit(this);
    QPushButton *deleteBtn = new QPushButton("Delete", this);

public slots:
    void onClickDeleteBtn();
};

#endif // KEYVALUEITEMWIDGET_H
