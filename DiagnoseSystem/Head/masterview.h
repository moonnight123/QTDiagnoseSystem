#ifndef MASTERVIEW_H
#define MASTERVIEW_H

#include <QWidget>
#include "loginview.h"
#include "doctorview.h"
#include "departmentview.h"
#include "patientview.h"
#include "patienteditview.h"
#include "welcomeview.h"
#include "doctoreditview.h"
#include "departmenteditview.h"
#include "historyview.h"
#include "registerview.h"
#include "welcondoctorview.h"
#include "doctorinformationview.h"
#include "doctorpatientview.h"
#include "doctorpatienteditview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MasterView; }
QT_END_NAMESPACE

class MasterView : public QWidget
{
    Q_OBJECT

public:
    MasterView(QWidget *parent = nullptr);
    ~MasterView();

public slots:
    //页面转换
    void goLoginView();//登录页面
    void goWelcomeView();//欢迎页面
    void goDoctorView();//医生管理
    void goDoctorEditView(int row);//医生添加
    void goDepartmentView();//科室管理
    void goDepartmentEditView(int rowNo);//科室添加
    void goPatientEditView(int rowNo);//患者添加
    void goPatientView();//患者管理
    void goHistoryView();//历史界面
    void goPreviousView();//返回上一页面
    void goRegisterView();//注册页面
    void goWelcomeDoctorView();
    void goDoctorInformationView();
    void goDoctorPatientView();
    void goDoctorPatientEditView(int rowNo);

private slots:
    void on_btback_clicked();

    void on_btLogout_clicked();

    void on_stackedWidget_currentChanged(int arg1);

private:
    Ui::MasterView *ui;
    void pushWidgetToStackView(QWidget *widget);

    WelcomeView *welcomeView;
    DoctorView *doctorView;
    PatientView *patientView;
    DepartmentView *departmentView;
    LoginView *loginView;
    PatientEditView *patientEditView;
    DoctorEditView *doctorEditView;
    DepartmentEditView *departmentEditView;
    HistoryView *historyView;
    RegisterView *registerView;
    WelconDoctorView *welcomeDoctorView;
    DoctorInformationView *doctorInformationView;
    DoctorPatientView *doctorPatientView;
    DoctorPatientEditView *doctorPatientEdit;
};
#endif // MASTERVIEW_H
