#include "loginview.h"
#include "ui_loginview.h"
#include "idatebase.h"

LoginView::LoginView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginView)
{
    ui->setupUi(this);
    ui->rbmanage->setChecked(true);
}

LoginView::~LoginView()
{
    delete ui;
}

void LoginView::on_btSignIn_clicked()
{
    if(ui->rbmanage->isChecked()){
        QString status = IDateBase::getInstance().userLogin(ui->inputuserName->text(),ui->inputPassWord->text());
        if(status == "loginOK"){
                emit loginSuccess();
        }
    }
    else if(ui->rbdoctor->isChecked()){
        QString status = IDateBase::getInstance().userDoctorLogin(ui->inputuserName->text(),ui->inputPassWord->text());
        if(status == "loginOK"){
            emit loginSuccess2();
        }
    }
}

void LoginView::on_btSignOn_clicked()
{
    emit goRegisterView();
}
