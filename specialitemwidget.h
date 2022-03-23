#ifndef SPECIALITEMWIDGET_H
#define SPECIALITEMWIDGET_H

#include <QObject>
#include <QWidget>
#include <QListWidgetItem>

/*
    The base class of FileItemWidget and KeyValueItemWidget.
    It derives from QWidget and QListWidgetItem, which can help store the related information about item.
*/
class SpecialItemWidget : public QWidget, public QListWidgetItem
{
    Q_OBJECT
public:
    explicit SpecialItemWidget(QWidget *parent = nullptr);
    // Return whether the item is FileItemWidget.
    virtual bool isFileItemWidget() = 0;
    // Return whether the item is KeyItemWidget.
    virtual bool isKeyValueItemWidget() = 0;

signals:
    // Tell the dialog that it has been deleted.
    void selfDelete();

};

#endif // SPECIALITEMWIDGET_H
