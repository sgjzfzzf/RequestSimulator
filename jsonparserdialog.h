#ifndef JSONPARSERDIALOG_H
#define JSONPARSERDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QTreeWidget>

class JsonParserDialog : public QDialog
{
    Q_OBJECT
public:
    JsonParserDialog(QWidget *parent = nullptr);
    QTreeWidget *getTreeWidget();

private:
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QTreeWidget *tree = new QTreeWidget(this);
};

#endif // JSONPARSERDIALOG_H
