#include "doctorpatientview.h"
#include "ui_doctorpatientview.h"
#include "idatebase.h"
#include <QDebug>
DoctorPatientView::DoctorPatientView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoctorPatientView)
{
    ui->setupUi(this);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);
    IDateBase &iDatabase = IDateBase::getInstance();
    if(iDatabase.initDoctorPatientModel()){
        ui->tableView->setModel(iDatabase.doctorPatientModel);
        ui->tableView->setSelectionModel(iDatabase.theDoctorPatientSelection);
    }
}

DoctorPatientView::~DoctorPatientView()
{
    delete ui;
}

void DoctorPatientView::on_btcheck_clicked()
{
    QString filter = QString("name like '%%1%' ").arg(ui->lineEdit->text());//获取查询的字符串，采取模糊查询
    IDateBase::getInstance().searchDoctorPatient(filter);
}

void DoctorPatientView::on_btadd_clicked()
{
    int currow = IDateBase::getInstance().addNewDoctorPatient();
    emit goDoctorPatientEditView(currow);
}

void DoctorPatientView::on_btdel_clicked()
{
    IDateBase::getInstance().deleteDoctorPatient();
}

void DoctorPatientView::on_btchange_clicked()
{
    QModelIndex curIndex = IDateBase::getInstance().theDoctorPatientSelection->currentIndex();//获取当前单元格的模
    emit goDoctorPatientEditView(curIndex.row());
}
