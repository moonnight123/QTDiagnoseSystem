#include "departmentview.h"
#include "ui_departmentview.h"
#include "idatebase.h"
#include <QDebug>

DepartmentView::DepartmentView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DepartmentView)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);
    IDateBase &iDatabase = IDateBase::getInstance();
    if(iDatabase.initDepartmentModel()){
        ui->tableView->setModel(iDatabase.departmentModel);
        ui->tableView->setSelectionModel(iDatabase.theDepartmentSelection);
    }
}

DepartmentView::~DepartmentView()
{
    delete ui;
}

void DepartmentView::on_btcheck_clicked()
{
    QString filter = QString("name like '%%1%' ").arg(ui->lineEdit->text());//获取查询的字符串，采取模糊查询
    IDateBase::getInstance().searchDepartment(filter);
}

void DepartmentView::on_btadd_clicked()
{
    int currow = IDateBase::getInstance().addNewDepartment();
    emit goDepartmentEditView(currow);
}

void DepartmentView::on_btdel_clicked()
{
    IDateBase::getInstance().deleteCurruntDepartment();
}

void DepartmentView::on_btchange_clicked()
{
    QModelIndex curIndex = IDateBase::getInstance().theDepartmentSelection->currentIndex();//获取当前单元格的模
    emit goDepartmentEditView(curIndex.row());
}
