#include "getdialog.h"

GetDialog::GetDialog(QWidget *parent) : QDialog(parent)
{
    setFixedSize(1000, 750);
    setWindowIcon(QIcon(":/IconLogo/img/networklogo.png"));
    setWindowTitle("Get Request Dialog");

    networkMenu->addAction(addAction);
    networkMenu->addAction(sendAction);
    parsingkMenu->addAction(HTMLAction);
    parsingkMenu->addAction(JsonAction);
    regexMenu->addAction(regexAction);
    menuBar->addMenu(networkMenu);
    menuBar->addMenu(parsingkMenu);
    menuBar->addMenu(regexMenu);
    mainLayout->setMenuBar(menuBar);

    mainLayout->addWidget(urlLabel, 0, 0, 1, 1);
    mainLayout->addWidget(urlInput, 0, 1, 1, 3);
    mainLayout->addWidget(paramsLabel, 1, 0, 1, 1);
    mainLayout->addWidget(paramsList, 2, 0, 1, 4);
    mainLayout->addWidget(resultDisplayer, 3, 0, 1, 4);

    addAction->setIcon(QIcon(":/IconLogo/img/addlogo.png"));
    resultDisplayer->setReadOnly(true);

    connect(addAction, SIGNAL(triggered()), this, SLOT(addItem()));
    connect(sendAction, SIGNAL(triggered()), this, SLOT(sendRequest()));
    connect(HTMLAction, SIGNAL(triggered()), this, SLOT(getParseHTML()));
    connect(JsonAction, SIGNAL(triggered()), this, SLOT(getParseJson()));
    connect(regexAction, SIGNAL(triggered()), this, SLOT(getRegex()));
}

void GetDialog::addItem()
{
    KeyValueItemWidget *itemWidget = new KeyValueItemWidget(this);
    paramsList->addItem(itemWidget);
    paramsList->setItemWidget(itemWidget, itemWidget);
    itemWidget->setSizeHint(itemWidget->size() * 1.5);
    connect(itemWidget, SIGNAL(selfDelete()), this, SLOT(deleteItem()));
}

void GetDialog::deleteItem()
{
    KeyValueItemWidget *itemWidget = (KeyValueItemWidget *)sender();
    paramsList->removeItemWidget(itemWidget);
    delete itemWidget;
}

void GetDialog::sendRequest()
{
    QString url = urlInput->text();
    if (paramsList->count())
        url.append('?');
    // Add parameters to the end of url.
    for (int i = 0; i < paramsList->count(); ++i)
    {
        KeyValueItemWidget *itemWidget = (KeyValueItemWidget *)paramsList->item(i);
        QString param = QString::fromLocal8Bit("%1=%2&").arg(itemWidget->getKey(), itemWidget->getValue());
        url.append(param);
    }
    QNetworkRequest request(url);
    resultDisplayer->clear();
    QNetworkReply *reply = manager->get(request);
    connect(reply, SIGNAL(readyRead()), this, SLOT(receiveReply()));
}

void GetDialog::receiveReply()
{
    QNetworkReply *reply = (QNetworkReply *)sender();
    resultDisplayer->insertPlainText(reply->readAll());
}

void GetDialog::getParseHTML()
{
    parseHTML(resultDisplayer->toPlainText());
}

void GetDialog::getParseJson()
{
    JsonParserDialog *dialog = new JsonParserDialog(this);
    parseJson(dialog->getTreeWidget(), resultDisplayer->toPlainText().toLocal8Bit());
    dialog->show();
}

void GetDialog::getRegex()
{
    RegexDialog *dialog = new RegexDialog(this);
    dialog->setContent(resultDisplayer->toPlainText());
    dialog->show();
}
