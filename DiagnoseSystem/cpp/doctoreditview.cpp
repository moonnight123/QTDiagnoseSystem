#include "doctoreditview.h"
#include "ui_doctoreditview.h"
#include "idatebase.h"
#include <QDataWidgetMapper>
DoctorEditView::DoctorEditView(QWidget *parent, int index) :
    QWidget(parent),
    ui(new Ui::DoctorEditView)
{
    ui->setupUi(this);
    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDateBase::getInstance().doctorTabModel;
    dataMapper->setModel(IDateBase::getInstance( ).doctorTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->dbEditID, tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->dbEditName, tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->dbEditEmployee, tabModel->fieldIndex("EMPLOYEENO"));
    dataMapper->addMapping(ui->dbEditDepartmentID, tabModel->fieldIndex("DEPARTMENT_ID"));

    dataMapper->setCurrentIndex(index);
}

DoctorEditView::~DoctorEditView()
{
    delete ui;
}

void DoctorEditView::on_btSave_clicked()
{
    IDateBase::getInstance().submitDoctorEdit();
    emit goPreviousView();
}

void DoctorEditView::on_btBack_clicked()
{
    IDateBase::getInstance().revertDoctorEdit();
    emit goPreviousView();
}
