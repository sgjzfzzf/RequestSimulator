#include "jsonparserdialog.h"

JsonParserDialog::JsonParserDialog(QWidget *parent): QDialog(parent)
{
    setWindowTitle("Parse Json Dialog");
    setWindowIcon(QIcon(":/IconLogo/img/networklogo.png"));
    mainLayout->addWidget(tree);
    tree->clear();
}

QTreeWidget* JsonParserDialog::getTreeWidget()
{
    return tree;
}
