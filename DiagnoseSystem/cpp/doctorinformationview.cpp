#include "doctorinformationview.h"
#include "ui_doctorinformationview.h"
#include "idatebase.h"

DoctorInformationView::DoctorInformationView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoctorInformationView)
{
    ui->setupUi(this);
    ui->lineEdit->setText(IDateBase::getInstance().information[0]);
    ui->lineEdit_2->setText(IDateBase::getInstance().information[1]);
    ui->lineEdit_3->setText(IDateBase::getInstance().information[2]);
    ui->lineEdit_4->setText(IDateBase::getInstance().information[6]);
    ui->lineEdit_5->setText(IDateBase::getInstance().information[4]);
    ui->lineEdit_6->setText(IDateBase::getInstance().information[3]);
    ui->lineEdit_7->setText(IDateBase::getInstance().information[5]);
    ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    ui->lineEdit_3->setEnabled(false);
    ui->lineEdit_4->setEnabled(false);
    ui->lineEdit_5->setEnabled(false);
    ui->lineEdit_6->setEnabled(false);
    ui->lineEdit_7->setEnabled(false);
}

DoctorInformationView::~DoctorInformationView()
{
    delete ui;
}
