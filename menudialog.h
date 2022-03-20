#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include "getdialog.h"
#include "postdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MenuDialog; }
QT_END_NAMESPACE

class MenuDialog : public QDialog
{
    Q_OBJECT

public:
    MenuDialog(QWidget *parent = nullptr);
    ~MenuDialog();

private:
    Ui::MenuDialog *ui;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QPushButton *getBtn = new QPushButton("Get", this);
    QPushButton *postBtn = new QPushButton("Post", this);

public slots:
    void openGetDialog();
    void openPostDialog();
};
#endif // MENUDIALOG_H
