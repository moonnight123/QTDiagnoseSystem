#include "welcondoctorview.h"
#include "ui_welcondoctorview.h"

WelconDoctorView::WelconDoctorView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelconDoctorView)
{
    ui->setupUi(this);
}

WelconDoctorView::~WelconDoctorView()
{
    delete ui;
}

void WelconDoctorView::on_pushButton_clicked()
{
    emit goDoctorInformationView();
}

void WelconDoctorView::on_pushButton_2_clicked()
{
    emit goDoctorPatientView();
}
