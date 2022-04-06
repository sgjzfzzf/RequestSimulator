/*
    This is the implemention of some function helping to parse reply content.
*/
#ifndef PARSE_H
#define PARSE_H

#include <QString>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include "jsonparserdialog.h"

/*
    TODO:
    It's waiting for further development.
*/
void parseHTML(const QString &);
/*
    Initialize the QTreeWidget while parsing json.
    @param QTreeWidget* the pointer of the QTreeWidget which need initialization
    @param QByteArray the ref of byte array of json
*/
void parseJson(QTreeWidget *, const QByteArray &);
/*
    Initialize related QTreeWidgetItem based on QJsonObject.
    @param QTreeWidget* the pointer of the QTreeWidget which need initialization
    @param QByteArray the ref of byte array of json object
*/
void parseJsonObject(QTreeWidgetItem *, const QJsonObject &);
/*
    Initialize related QTreeWidgetItem based on QJsonArray.
    @param QTreeWidget* the pointer of the QTreeWidget which need initialization
    @param QByteArray the ref of byte array of json array
    @param QString the name of parent node, which can help to give name to the array nodes which don't have key
*/
void parseJsonArray(QTreeWidgetItem *, const QJsonArray &, const QString &);
/*
    Covert the json value into string based on their class instead of default method.
    @param QJsonValue the value needing to translate
    @return the result string
*/
QString convertJsonValueToString(const QJsonValue &);

#endif // PARSE_H
