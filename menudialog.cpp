#include "menudialog.h"
#include "ui_menudialog.h"

MenuDialog::MenuDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::MenuDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/IconLogo/img/networklogo.png"));
    setWindowTitle("Menu Dialog");
    setFixedSize(200, 100);
    mainLayout->addWidget(getBtn);
    mainLayout->addWidget(postBtn);
    connect(getBtn, SIGNAL(clicked()), this, SLOT(openGetDialog()));
    connect(postBtn, SIGNAL(clicked()), this, SLOT(openPostDialog()));
}

MenuDialog::~MenuDialog()
{
    delete ui;
}

void MenuDialog::openGetDialog()
{
    GetDialog *dialog = new GetDialog(this);
    dialog->show();
}

void MenuDialog::openPostDialog()
{
    PostDialog *dialog = new PostDialog(this);
    dialog->show();
}
