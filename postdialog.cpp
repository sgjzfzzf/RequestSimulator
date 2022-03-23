#include "postdialog.h"

PostDialog::PostDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Post Request Dialog");
    setWindowIcon(QIcon(":/IconLogo/img/networklogo.png"));
    setFixedSize(1000, 750);

    networkMenu->addAction(addParamAction);
    networkMenu->addAction(addDataAction);
    networkMenu->addAction(addFileAction);
    networkMenu->addAction(sendAction);
    parsingkMenu->addAction(HTMLAction);
    parsingkMenu->addAction(JsonAction);
    menuBar->addMenu(networkMenu);
    menuBar->addMenu(parsingkMenu);
    mainLayout->setMenuBar(menuBar);

    mainLayout->addWidget(urlLabel, 0, 0, 1, 1);
    mainLayout->addWidget(urlInput, 0, 1, 1, 3);
    mainLayout->addWidget(paramsLabel, 1, 0, 1, 1);
    mainLayout->addWidget(paramsList, 2, 0, 1, 4);
    mainLayout->addWidget(dataLabel, 3, 0, 1, 1);
    mainLayout->addWidget(formLabel, 4, 0, 1, 1);
    mainLayout->addWidget(xBtn, 4, 1, 1, 1);
    mainLayout->addWidget(jsonBtn, 4, 2, 1, 1);
    mainLayout->addWidget(multiBtn, 4, 3, 1, 1);
    mainLayout->addWidget(dataList, 5, 0, 1, 4);
    mainLayout->addWidget(resultDisplayer, 6, 0, 1, 4);

    addParamAction->setIcon(QIcon(":/IconLogo/img/addlogo.png"));
    addDataAction->setIcon(QIcon(":/IconLogo/img/addlogo.png"));
    addFileAction->setIcon(QIcon(":/IconLogo/img/addlogo.png"));
    btnGroup->setExclusive(true);
    btnGroup->addButton(xBtn);
    btnGroup->addButton(jsonBtn);
    btnGroup->addButton(multiBtn);
    resultDisplayer->setReadOnly(true);

    connect(addParamAction, SIGNAL(triggered()), this, SLOT(addParamItem()));
    connect(addDataAction, SIGNAL(triggered()), this, SLOT(addDataItem()));
    connect(addFileAction, SIGNAL(triggered()), this, SLOT(addFileItem()));
    connect(sendAction, SIGNAL(triggered()), this, SLOT(sendRequest()));
    connect(HTMLAction, SIGNAL(triggered()), this, SLOT(getParseHTML()));
    connect(JsonAction, SIGNAL(triggered()), this, SLOT(getParseJson()));
}

bool PostDialog::isFileAvailable()
{
    for (int i = 0; i < dataList->count(); ++i)
    {
        SpecialItemWidget *itemWidget = (SpecialItemWidget *)dataList->item(i);
        if (itemWidget->isFileItemWidget())
        {
            return true;
        }
    }
    return false;
}

QNetworkReply *PostDialog::sendXWWWRequest(QNetworkRequest &request)
{
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QString data = "";
    for (int i = 0; i < dataList->count(); ++i)
    {
        KeyValueItemWidget *itemWidget = (KeyValueItemWidget *)dataList->item(i);
        data.append(QString::fromLocal8Bit("%1=%2&").arg(itemWidget->getKey(), itemWidget->getValue()));
    }
    return manager->post(request, data.toLocal8Bit());
}

QNetworkReply *PostDialog::sendJsonRequest(QNetworkRequest &request)
{
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject obj;
    for (int i = 0; i < dataList->count(); ++i)
    {
        KeyValueItemWidget *itemWidget = (KeyValueItemWidget *)dataList->item(i);
        obj.insert(itemWidget->getKey(), itemWidget->getValue());
    }
    QJsonDocument doc(obj);
    return manager->post(request, doc.toJson());
}

QNetworkReply *PostDialog::sendMultiRequest(QNetworkRequest &request)
{
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    for (int i = 0; i < dataList->count(); ++i)
    {
        SpecialItemWidget *itemWidget = (SpecialItemWidget *)dataList->item(i);
        QHttpPart part;
        if (itemWidget->isKeyValueItemWidget())
        {
            part.setHeader(QNetworkRequest::ContentDispositionHeader, QString::fromLocal8Bit("form-data; name=\"%1\"").arg(((KeyValueItemWidget *)itemWidget)->getKey()));
            part.setBody(((KeyValueItemWidget *)itemWidget)->getValue().toLocal8Bit());
        }
        else if (itemWidget->isFileItemWidget())
        {
            QString path = ((FileItemWidget *)itemWidget)->getFileName();
            QFile *file = new QFile(path);
            if (file->open(QFile::ReadOnly))
            {
                QString fileName = path.split("/").last();
                part.setHeader(QNetworkRequest::ContentDispositionHeader, QString::fromLocal8Bit("form-data; name=\"%1\"; filename=\"%2\"").arg(fileName, fileName));
                part.setBodyDevice(file);
            }
        }
        multiPart->append(part);
    }
    return manager->post(request, multiPart);
}

void PostDialog::addParamItem()
{
    KeyValueItemWidget *itemWidget = new KeyValueItemWidget(this);
    paramsList->addItem(itemWidget);
    paramsList->setItemWidget(itemWidget, itemWidget);
    itemWidget->setSizeHint(itemWidget->size() * 1.5);
    connect(itemWidget, SIGNAL(selfDelete()), this, SLOT(deleteParamItem()));
}

void PostDialog::deleteParamItem()
{
    KeyValueItemWidget *itemWidget = (KeyValueItemWidget *)sender();
    paramsList->removeItemWidget(itemWidget);
    delete itemWidget;
}

void PostDialog::addDataItem()
{
    KeyValueItemWidget *itemWidget = new KeyValueItemWidget(this);
    dataList->addItem(itemWidget);
    dataList->setItemWidget(itemWidget, itemWidget);
    itemWidget->setSizeHint(itemWidget->size() * 1.5);
    connect(itemWidget, SIGNAL(selfDelete()), this, SLOT(deleteParamItem()));
}

void PostDialog::deleteDataItem()
{
    KeyValueItemWidget *itemWidget = (KeyValueItemWidget *)sender();
    dataList->removeItemWidget(itemWidget);
    delete itemWidget;
}

void PostDialog::addFileItem()
{
    FileItemWidget *itemWidget = new FileItemWidget(this);
    QString fileName = QFileDialog::getOpenFileName(this, "Choose the sent file");
    dataList->addItem(itemWidget);
    dataList->setItemWidget(itemWidget, itemWidget);
    itemWidget->setSizeHint(itemWidget->size() * 1.5);
    itemWidget->setFileName(fileName);
    // If there are files sending, only multipart-data form is available according to the standard of post method.
    if (isFileAvailable())
    {
        xBtn->setCheckable(false);
        jsonBtn->setCheckable(false);
    }
    connect(itemWidget, SIGNAL(selfDelete()), this, SLOT(deleteFileItem()));
}

void PostDialog::deleteFileItem()
{
    FileItemWidget *itemWidget = (FileItemWidget *)sender();
    dataList->removeItemWidget(itemWidget);
    delete itemWidget;
    if (!isFileAvailable())
    {
        xBtn->setCheckable(true);
        jsonBtn->setCheckable(true);
    }
}

void PostDialog::sendRequest()
{
    QString url = urlInput->text();
    // If no parameters need to add, no '?' needs to add in the end of url.
    if (paramsList->count())
        url.append('?');
    for (int i = 0; i < paramsList->count(); ++i)
    {
        KeyValueItemWidget *itemWidget = (KeyValueItemWidget *)paramsList->item(i);
        QString param = QString::fromLocal8Bit("%1=%2&").arg(itemWidget->getKey(), itemWidget->getValue());
        url.append(param);
    }
    QNetworkRequest request(url);
    resultDisplayer->clear();
    QNetworkReply *reply = nullptr;
    // Choose to send request in which form according to the clicked button.
    if ((QRadioButton *)btnGroup->checkedButton() == xBtn)
    {
        reply = sendXWWWRequest(request);
    }
    else if ((QRadioButton *)btnGroup->checkedButton() == jsonBtn)
    {
        reply = sendJsonRequest(request);
    }
    else if ((QRadioButton *)btnGroup->checkedButton() == multiBtn)
    {
        reply = sendMultiRequest(request);
    }
    else
    {
        QMessageBox::information(this, "Notice", "Remember to choose the form of post method.");
    }
    if (reply != nullptr)
    {
        // Let receiveReply method deal with the reply.
        connect(reply, SIGNAL(readyRead()), this, SLOT(receiveReply()));
    }
}

void PostDialog::receiveReply()
{
    // Find the reply with the help of sender method.
    QNetworkReply *reply = (QNetworkReply *)sender();
    resultDisplayer->insertPlainText(reply->readAll());
}

void PostDialog::getParseHTML()
{
    parseHTML(resultDisplayer->toPlainText());
}

void PostDialog::getParseJson()
{
    JsonParserDialog *dialog = new JsonParserDialog(this);
    dialog->show();
    parseJson(dialog->getTreeWidget(), resultDisplayer->toPlainText().toLocal8Bit());
}
