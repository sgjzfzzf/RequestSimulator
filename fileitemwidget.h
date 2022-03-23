#ifndef FILEITEMWIDGET_H
#define FILEITEMWIDGET_H

#include <QObject>
#include <QWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "specialitemwidget.h"

/*
    The class of QListWidgetItem in the QListWidget.
    It's the implemention of SpecialItemWidget.
    This class stores the item about file sending.
*/
class FileItemWidget : public SpecialItemWidget
{
    Q_OBJECT
public:
    explicit FileItemWidget(QWidget *parent = nullptr);
    bool isFileItemWidget();
    bool isKeyValueItemWidget();
    void setFileName(const QString &);
    QString getFileName();

private:
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QLabel *fileNameLabel = new QLabel(this);
    QPushButton *deleteBtn = new QPushButton("Delete", this);

public slots:
    void onClickDeleteBtn();
};

#endif // FILEITEMWIDGET_H
