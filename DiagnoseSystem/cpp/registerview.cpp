#include "registerview.h"
#include "ui_registerview.h"
#include "idatebase.h"
#include <QMessageBox>

RegisterView::RegisterView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterView)
{
    ui->setupUi(this);
}

RegisterView::~RegisterView()
{
    delete ui;
}

void RegisterView::on_btregister_clicked()
{
    QString state = IDateBase::getInstance().userRegister(ui->dbID->text(),ui->dbFullName->text(),ui->dbuserName->text()
                                                          ,ui->dbpassword->text(),ui->dbrepassword->text());
    std::string str = state.toStdString();
    const char* ch = str.c_str();
    emit goLoginView();
    QMessageBox::about(this, tr("消息框"), tr(ch));
}

void RegisterView::on_btback_clicked()
{
    emit goLoginView();
}
