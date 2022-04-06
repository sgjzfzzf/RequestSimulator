/*
    The dialog which helps to parse regex parsing.
*/

#ifndef REGEXDIALOG_H
#define REGEXDIALOG_H

#include <QDialog>
#include <QObject>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QRegExp>
#include <QThread>
#include <QMessageBox>

class RegexDialog : public QDialog
{
    Q_OBJECT
public:
    RegexDialog(QWidget *parent = nullptr);
    void setContent(const QString &);
    friend class RegexThread;

private:
    QGridLayout *mainLayout = new QGridLayout(this);
    QLabel *regexLabel = new QLabel("Regex:", this);
    QLineEdit *regexEdit = new QLineEdit(this);
    QTextEdit *resultDisplayer = new QTextEdit(this);
    QPushButton *regexBtn = new QPushButton("Regex Parse", this);

public slots:
    void parseRegex();
};

// In order to avoid obvious block, a thread is launched to finish the regex work.
class RegexThread : public QThread
{
    Q_OBJECT
public:
    explicit RegexThread(QObject *parent = nullptr);
    void run() override;

private:
    RegexDialog *dialog;
};

#endif // REGEXDIALOG_H
