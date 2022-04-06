#include "regexdialog.h"

RegexDialog::RegexDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Regex Dialog");
    setWindowIcon(QIcon(":/IconLogo/img/networklogo.png"));
    mainLayout->addWidget(regexLabel, 0, 0, 1, 1);
    mainLayout->addWidget(regexEdit, 0, 1, 1, 3);
    mainLayout->addWidget(resultDisplayer, 1, 0, 2, 4);
    mainLayout->addWidget(regexBtn, 4, 3, 1, 1);

    resultDisplayer->setReadOnly(true);

    connect(regexBtn, SIGNAL(clicked()), this, SLOT(parseRegex()));
}

void RegexDialog::setContent(const QString &string)
{
    resultDisplayer->setPlainText(string);
}

void RegexDialog::parseRegex()
{
    RegexThread *thread = new RegexThread(this);
    thread->start();
}

RegexThread::RegexThread(QObject *parent) : QThread(parent), dialog((RegexDialog *)parent)
{
}

void RegexThread::run()
{
    if (dialog->resultDisplayer->toPlainText() == nullptr)
    {
        exit(-1);
    }
    else
    {
        // Define the regex expression according to the input from users.
        QRegExp reg(dialog->regexEdit->text());
        if (reg.isValid())
        {
            int pos = 0;
            QString content = dialog->resultDisplayer->toPlainText();
            QTextCursor cursor = dialog->resultDisplayer->textCursor();
            cursor.beginEditBlock();
            // Clean the whole format.
            cursor.setPosition(0, QTextCursor::MoveAnchor);
            cursor.setPosition(content.size(), QTextCursor::KeepAnchor);
            QTextCharFormat fmt;
            fmt.setForeground(Qt::black);
            cursor.setCharFormat(fmt);
            cursor.clearSelection();
            fmt.setForeground(Qt::red);
            while ((pos = reg.indexIn(content, pos)) != -1)
            {
                // Set cursor position to choose the matched result.
                cursor.setPosition(pos, QTextCursor::MoveAnchor);
                pos += reg.matchedLength();
                cursor.setPosition(pos, QTextCursor::KeepAnchor);
                cursor.mergeCharFormat(fmt);
                cursor.clearSelection();
            }
            cursor.endEditBlock();
        }
        else
        {
            QMessageBox::information(dialog, "Regex", "The regex expression is invalid.");
        }
    }
}
