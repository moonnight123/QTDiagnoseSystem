#include "doctorpatienteditview.h"
#include "ui_doctorpatienteditview.h"
#include "idatebase.h"
#include <QDataWidgetMapper>

DoctorPatientEditView::DoctorPatientEditView(QWidget *parent, int index) :
    QWidget(parent),
    ui(new Ui::DoctorPatientEditView)
{
    ui->setupUi(this);
    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDateBase::getInstance().doctorPatientModel;
    dataMapper->setModel(IDateBase::getInstance( ).doctorPatientModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->dbEditID, tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->dbEditName, tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->dbEditIDCard, tabModel->fieldIndex("ID_CARD"));
    dataMapper->addMapping(ui->dbComboSex, tabModel->fieldIndex("SEX"));
    dataMapper->addMapping(ui->dbSpinHeight, tabModel->fieldIndex("HIGH"));
    dataMapper->addMapping(ui->dbSpinweight, tabModel->fieldIndex("WEIGHT"));
    dataMapper->addMapping(ui->dbEditwobile, tabModel->fieldIndex("PHONE"));
    dataMapper->addMapping(ui->dbIllness, tabModel->fieldIndex("ILLNESS"));

    dataMapper->setCurrentIndex(index);
}

DoctorPatientEditView::~DoctorPatientEditView()
{
    delete ui;
}

void DoctorPatientEditView::on_pushButton_clicked()
{
    IDateBase::getInstance().submitDoctorPatient();
    emit goPreviousView();
}

void DoctorPatientEditView::on_pushButton_2_clicked()
{
    IDateBase::getInstance().revertDoctorPatient();
    emit goPreviousView();
}
