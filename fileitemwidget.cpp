#include "fileitemwidget.h"

FileItemWidget::FileItemWidget(QWidget *parent) : SpecialItemWidget(parent)
{
    mainLayout->addWidget(fileNameLabel);
    mainLayout->addWidget(deleteBtn);
    deleteBtn->setIcon(QIcon(":/IconLogo/img/deletelogo.png"));
    connect(deleteBtn, SIGNAL(clicked()), this, SLOT(onClickDeleteBtn()));
}

bool FileItemWidget::isFileItemWidget()
{
    return true;
}

bool FileItemWidget::isKeyValueItemWidget()
{
    return false;
}

void FileItemWidget::setFileName(const QString & fileName)
{
    fileNameLabel->setText(fileName);
}

QString FileItemWidget::getFileName()
{
    return fileNameLabel->text();
}

void FileItemWidget::onClickDeleteBtn()
{
    emit selfDelete();
}
