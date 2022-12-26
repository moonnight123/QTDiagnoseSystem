#include "doctorview.h"
#include "ui_doctorview.h"
#include "idatebase.h"
#include <QDebug>

DoctorView::DoctorView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoctorView)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);
    IDateBase &iDatabase = IDateBase::getInstance();
    if(iDatabase.initDoctorModel()){
        ui->tableView->setModel(iDatabase.doctorTabModel);
        ui->tableView->setSelectionModel(iDatabase.theDoctorSelection);
    }
}

DoctorView::~DoctorView()
{
    delete ui;
}

void DoctorView::on_btcheck_clicked()
{
    QString filter = QString("name like '%%1%' ").arg(ui->lineEdit->text());//获取查询的字符串，采取模糊查询
    IDateBase::getInstance().searchDoctor(filter);
}

void DoctorView::on_btadd_clicked()
{
    int currow = IDateBase::getInstance().addNewDoctor();
    emit goDoctorEditView(currow);
}

void DoctorView::on_btdel_clicked()
{
     IDateBase::getInstance().deleteCurruntDoctor();
}

void DoctorView::on_btchange_clicked()
{
    QModelIndex curIndex = IDateBase::getInstance().theDoctorSelection->currentIndex();//获取当前单元格的模
    emit goDoctorEditView(curIndex.row());
}
