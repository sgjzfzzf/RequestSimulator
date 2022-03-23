/*
    The dialog which help users to send get request.
*/
#ifndef GETDIALOG_H
#define GETDIALOG_H

#include <QDialog>
#include <QObject>
#include <QGridLayout>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QTextEdit>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "jsonparserdialog.h"
#include "keyvalueitemwidget.h"
#include "parse.h"

class GetDialog : public QDialog
{
    Q_OBJECT
public:
    GetDialog(QWidget *parent = nullptr);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QGridLayout *mainLayout = new QGridLayout(this);
    QMenu *networkMenu = new QMenu("Network", this);
    QMenu *parsingkMenu = new QMenu("Parse", this);
    QMenuBar *menuBar = new QMenuBar(this);
    QAction *addAction = new QAction("Add", this);
    QAction *sendAction = new QAction("Send", this);
    QAction *HTMLAction = new QAction("Parse HTML", this);
    QAction *JsonAction = new QAction("Parse Json", this);
    QLabel *urlLabel = new QLabel("URL:", this);
    QLineEdit *urlInput = new QLineEdit(this);
    QLabel *paramsLabel = new QLabel("Parameters:", this);
    QListWidget *paramsList = new QListWidget(this);
    QTextEdit *resultDisplayer = new QTextEdit(this);

public slots:
    void addItem();
    void deleteItem();
    void sendRequest();
    void receiveReply();
    /*
        TODO:
        It's waiting for further development.
    */
    void getParseHTML();
    void getParseJson();
};

#endif // GETDIALOG_H
