#include "loginview.h"
#include "ui_loginview.h"
#include "idatebase.h"

LoginView::LoginView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginView)
{
    ui->setupUi(this);
}

LoginView::~LoginView()
{
    delete ui;
}

void LoginView::on_btSignIn_clicked()
{
    QString status = IDateBase::getInstance().userLogin(ui->inputuserName->text(),ui->inputPassWord->text());

    if(status == "loginOK"){
        emit loginSuccess();
    }
}

void LoginView::on_btSignOn_clicked()
{
    emit goRegisterView();
}
