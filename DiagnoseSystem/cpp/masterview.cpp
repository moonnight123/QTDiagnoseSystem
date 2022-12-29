#include "masterview.h"
#include "ui_masterview.h"
#include <QString>
#include <QDebug>
#include "idatebase.h"

MasterView::MasterView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MasterView)
{
    ui->setupUi(this);
        this->setWindowFlag(Qt::FramelessWindowHint);
    goLoginView();
        IDateBase::getInstance();
}

MasterView::~MasterView()
{
    delete ui;
}

void MasterView::goLoginView()
{
    loginView = new LoginView(this);
    pushWidgetToStackView(loginView);

    connect(loginView,SIGNAL(loginSuccess()),this,SLOT(goWelcomeView()));
    connect(loginView,SIGNAL(goRegisterView()),this,SLOT(goRegisterView()));
}

void MasterView::goWelcomeView()
{
    welcomeView = new WelcomeView(this);
    pushWidgetToStackView(welcomeView);

    connect(welcomeView,SIGNAL(goDepartmentView()),this,SLOT(goDepartmentView()));
    connect(welcomeView,SIGNAL(goDoctorView()),this,SLOT(goDoctorView()));
    connect(welcomeView,SIGNAL(goPatientView()),this,SLOT(goPatientView()));
    connect(welcomeView,SIGNAL(goHistoryView()),this,SLOT(goHistoryView()));
}

void MasterView::goDoctorView()
{
    doctorView = new DoctorView(this);
    pushWidgetToStackView(doctorView);

    connect(doctorView,SIGNAL(goDoctorEditView(int)),this,SLOT(goDoctorEditView(int)));
}

void MasterView::goDoctorEditView(int row)
{
    doctorEditView = new DoctorEditView(this,row);
    pushWidgetToStackView(doctorEditView);

    connect(doctorEditView,SIGNAL(goPreviousView()),this,SLOT(goPreviousView()));
}

void MasterView::goDepartmentView()
{
    departmentView = new DepartmentView(this);
    pushWidgetToStackView(departmentView);

    connect(departmentView,SIGNAL(goDepartmentEditView(int)),this,SLOT(goDepartmentEditView(int)));
}

void MasterView::goDepartmentEditView(int rowNo)
{
    departmentEditView = new DepartmentEditView(this,rowNo);
    pushWidgetToStackView(departmentEditView);
    connect(departmentEditView,SIGNAL(goPreviousView()),this,SLOT(goPreviousView()));
}

void MasterView::goPatientEditView(int rowNo)
{
    patientEditView = new PatientEditView(this,rowNo);
    pushWidgetToStackView(patientEditView);

    connect(patientEditView,SIGNAL(goPreviousView()),this,SLOT(goPreviousView()));
}

void MasterView::goPatientView()
{
    patientView = new PatientView(this);
    pushWidgetToStackView(patientView);
    connect(patientView,SIGNAL(goPatientEditView(int)),this,SLOT(goPatientEditView(int)));
}

void MasterView::goHistoryView()
{
    historyView = new HistoryView(this);
    pushWidgetToStackView(historyView);
}

void MasterView::goPreviousView()
{
    QString title = ui->stackedWidget->currentWidget()->windowTitle();
    if(title == "登录"){
        close();
    }
    int count = ui->stackedWidget->count();//获取当前页面个数
    if(count>1){
        ui->stackedWidget->setCurrentIndex(count-2);//显示第二个页面
        ui->labelTitle->setText(ui->stackedWidget->currentWidget()->windowTitle());//显示页面标题

        QWidget *widget = ui->stackedWidget->widget(count-1);//获取最新的页面
        delete  widget;//清除页面
    }
}

void MasterView::goRegisterView()
{
    registerView = new RegisterView(this);
    pushWidgetToStackView(registerView);

    connect(registerView,SIGNAL(goLoginView()),this,SLOT(goLoginView()));
}

void MasterView::pushWidgetToStackView(QWidget *widget)
{
    ui->stackedWidget->addWidget(widget);//添加新页面
    int count = ui->stackedWidget->count();//获取当前页面个数
    ui->stackedWidget->setCurrentIndex(count-1);//总是显示最新加入的View
    ui->labelTitle->setText(widget->windowTitle());//显示页面标题
}

void MasterView::on_btback_clicked()
{
    goPreviousView();
}

void MasterView::on_btLogout_clicked()
{
    goPreviousView();
}

void MasterView::on_stackedWidget_currentChanged(int arg1)
{
    int count = ui->stackedWidget->count();
    if(count>1){
        ui->btback->setEnabled(true);
    }else{
        ui->btback->setEnabled(false);
    }
    QString title = ui->stackedWidget->currentWidget()->windowTitle();

    if(title == "欢迎"){
        ui->btLogout->setEnabled(true);
        ui->btback->setEnabled(false);
    }
    else{
        ui->btLogout->setEnabled(false);
    }
}
