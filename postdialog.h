#ifndef POSTDIALOG_H
#define POSTDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QButtonGroup>
#include <QRadioButton>
#include <QTextEdit>
#include <QFileDialog>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QHttpMultiPart>
#include <QHttpPart>
#include "fileitemwidget.h"
#include "jsonparserdialog.h"
#include "keyvalueitemwidget.h"
#include "parse.h"

class PostDialog : public QDialog
{
    Q_OBJECT
public:
    PostDialog(QWidget *parent = nullptr);
    bool isFileAvailable();
    QNetworkReply* sendXWWWRequest(QNetworkRequest&);
    QNetworkReply* sendJsonRequest(QNetworkRequest&);
    QNetworkReply* sendMultiRequest(QNetworkRequest&);

private:
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QGridLayout *mainLayout = new QGridLayout(this);
    QMenu *networkMenu = new QMenu("Network", this);
    QMenu *parsingkMenu = new QMenu("Parse", this);
    QMenuBar *menuBar = new QMenuBar(this);
    QAction *addParamAction = new QAction("Add Parameters", this);
    QAction *addDataAction = new QAction("Add Data", this);
    QAction *addFileAction = new QAction("Add File", this);
    QAction *sendAction = new QAction("Send", this);
    QAction *HTMLAction = new QAction("Parse HTML", this);
    QAction *JsonAction = new QAction("Parse Json", this);
    QLabel *urlLabel = new QLabel("URL:", this);
    QLineEdit *urlInput = new QLineEdit(this);
    QLabel *paramsLabel = new QLabel("Parameters:", this);
    QListWidget *paramsList = new QListWidget(this);
    QLabel *dataLabel = new QLabel("Data:", this);
    QLabel *formLabel = new QLabel("Form:", this);
    QButtonGroup *btnGroup = new QButtonGroup(this);
    QRadioButton *xBtn = new QRadioButton("x-www-form-urlencode", this);
    QRadioButton *jsonBtn = new QRadioButton("JSON", this);
    QRadioButton *multiBtn = new QRadioButton("Multipart/form-data", this);
    QListWidget *dataList = new QListWidget(this);
    QTextEdit *resultDisplayer = new QTextEdit(this);

public slots:
    void addParamItem();
    void deleteParamItem();
    void addDataItem();
    void deleteDataItem();
    void addFileItem();
    void deleteFileItem();
    void sendRequest();
    void receiveReply();
    void getParseHTML();
    void getParseJson();
};

#endif // POSTDIALOG_H
