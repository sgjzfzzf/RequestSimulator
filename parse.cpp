#include "parse.h"

void parseHTML(const QString &html)
{
    QMessageBox::information(nullptr, "Error", "This part is waiting for development.");
}

void parseJson(QTreeWidget *tree, const QByteArray &json)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(json, &error);
    if (!doc.isNull() && error.error == QJsonParseError::NoError){
        if (doc.isObject())
        {
            QTreeWidgetItem *item = new QTreeWidgetItem;
            tree->addTopLevelItem(item);
            parseJsonObject(item, doc.object());
        }
        else if (doc.isArray())
        {
            QTreeWidgetItem *item = new QTreeWidgetItem;
            tree->addTopLevelItem(item);
            parseJsonArray(item, doc.array(), "");
        }
    }
}

void parseJsonObject(QTreeWidgetItem *item, const QJsonObject &obj)
{
    for (QJsonObject::const_iterator it = obj.begin(); it != obj.end(); ++it)
    {
        QJsonValue value = it.value();
        if (value.isObject())
        {
            QTreeWidgetItem *nextItem = new QTreeWidgetItem;
            nextItem->setText(0, it.key());
            item->addChild(nextItem);
            parseJsonObject(nextItem, value.toObject());
        }
        else if (value.isArray())
        {
            QTreeWidgetItem *nextItem = new QTreeWidgetItem;
            nextItem->setText(0, it.key());
            item->addChild(nextItem);
            parseJsonArray(nextItem, value.toArray(), it.key());
        }
        else if (!value.isNull())
        {
            QTreeWidgetItem *nextItem = new QTreeWidgetItem;
            nextItem->setText(0, QString::fromLocal8Bit("%1 : %2").arg(it.key(), convertJsonValueToString(it.value())));
            item->addChild(nextItem);
        }
    }
}

void parseJsonArray(QTreeWidgetItem *item, const QJsonArray &array, QString parentName)
{
    int counter = 0;
    for (QJsonArray::const_iterator it = array.begin(); it != array.end(); ++counter, ++it)
    {
        QJsonValue value = *it;
        QString name = QString::fromLocal8Bit("%1[%2]").arg(parentName, QString::number(counter));
        if (value.isObject())
        {
            QTreeWidgetItem *nextItem = new QTreeWidgetItem;
            nextItem->setText(0, name);
            item->addChild(nextItem);
            parseJsonObject(nextItem, value.toObject());
        }
        else if (value.isArray())
        {
            QTreeWidgetItem *nextItem = new QTreeWidgetItem;
            nextItem->setText(0, name);
            item->addChild(nextItem);
            parseJsonArray(nextItem, value.toArray(), name);
        }
        else if (!value.isNull())
        {
            QTreeWidgetItem *nextItem = new QTreeWidgetItem;
            nextItem->setText(0, QString::fromLocal8Bit("%1 : %2").arg(name, convertJsonValueToString(*it)));
            item->addChild(nextItem);
        }
    }
}

QString convertJsonValueToString(const QJsonValue &value)
{
    if (value.isBool())
    {
        if (value.toBool())
        {
            return "true";
        }
        else
        {
            return "false";
        }
    }
    else if (value.isDouble())
    {
        return QString::number(value.toDouble());
    }
    else if (value.isString())
    {
        return value.toString();
    }
    else
    {
        return "";
    }
}
