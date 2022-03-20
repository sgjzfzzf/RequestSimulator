#include "keyvalueitemwidget.h"

KeyValueItemWidget::KeyValueItemWidget(QWidget *parent) : SpecialItemWidget(parent)
{
    mainLayout->addWidget(keyLabel);
    mainLayout->addWidget(keyInput);
    mainLayout->addWidget(valueLabel);
    mainLayout->addWidget(valueInput);
    mainLayout->addWidget(deleteBtn);
    deleteBtn->setIcon(QIcon(":/IconLogo/img/deletelogo.png"));
    connect(deleteBtn, SIGNAL(clicked()), this, SLOT(onClickDeleteBtn()));
}

bool KeyValueItemWidget::isFileItemWidget()
{
    return false;
}

bool KeyValueItemWidget::isKeyValueItemWidget()
{
    return true;
}

QString KeyValueItemWidget::getKey()
{
    return keyInput->text();
}

QString KeyValueItemWidget::getValue()
{
    return valueInput->text();
}

void KeyValueItemWidget::onClickDeleteBtn()
{
    emit selfDelete();
}
