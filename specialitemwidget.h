#ifndef SPECIALITEMWIDGET_H
#define SPECIALITEMWIDGET_H

#include <QObject>
#include <QWidget>
#include <QListWidgetItem>

class SpecialItemWidget : public QWidget, public QListWidgetItem
{
    Q_OBJECT
public:
    explicit SpecialItemWidget(QWidget *parent = nullptr);
    virtual bool isFileItemWidget() = 0;
    virtual bool isKeyValueItemWidget() = 0;

signals:

};

#endif // SPECIALITEMWIDGET_H
