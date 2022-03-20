#ifndef PARSE_H
#define PARSE_H

#include <QString>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include "jsonparserdialog.h"

void parseHTML(const QString&);
void parseJson(QTreeWidget*, const QByteArray&);
void parseJsonObject(QTreeWidgetItem*, const QJsonObject&);
void parseJsonArray(QTreeWidgetItem*, const QJsonArray&, QString);
QString convertJsonValueToString(const QJsonValue&);

#endif // PARSE_H
