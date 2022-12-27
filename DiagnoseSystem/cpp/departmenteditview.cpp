#include "departmenteditview.h"
#include "ui_departmenteditview.h"
#include "idatebase.h"
#include <QDataWidgetMapper>
#include <QDebug>
DepartmentEditView::DepartmentEditView(QWidget *parent, int index) :
    QWidget(parent),
    ui(new Ui::DepartmentEditView)
{
    ui->setupUi(this);

    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDateBase::getInstance().departmentModel;
    dataMapper->setModel(IDateBase::getInstance( ).departmentModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->dbDepartmentNo, tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->dbDepartmentName, tabModel->fieldIndex("NAME"));

    dataMapper->setCurrentIndex(index);

}

DepartmentEditView::~DepartmentEditView()
{
    delete ui;
}

void DepartmentEditView::on_btSave_clicked()
{
    IDateBase::getInstance().submitDepartmentEdit();
    emit goPreviousView();
}

void DepartmentEditView::on_btBack_clicked()
{
    IDateBase::getInstance().revertDepartmentEdit();
    emit goPreviousView();
}
