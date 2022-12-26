#include "patientview.h"
#include "ui_patientview.h"
#include "idatebase.h"

PatientView::PatientView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientView)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    IDateBase &iDatabase = IDateBase::getInstance();
    if(iDatabase.initPatientModel()){
        ui->tableView->setModel(iDatabase.patientTabModel);
        ui->tableView->setSelectionModel(iDatabase.thePatientSelection);
    }
}

PatientView::~PatientView()
{
    delete ui;
}

void PatientView::on_btadd_2_clicked()
{
    int currow = IDateBase::getInstance().addNewPatient();
    emit goPatientEditView(currow);
}

void PatientView::on_btcheck_2_clicked()
{
    QString filter = QString("name like '%%1%' ").arg(ui->lineEdit_2->text());//获取查询的字符串，采取模糊查询
    IDateBase::getInstance().searchPatient(filter);
}

void PatientView::on_btdel_2_clicked()
{
    IDateBase::getInstance().deleteCurrentPatient();
}

void PatientView::on_btchange_2_clicked()
{
    QModelIndex curIndex = IDateBase::getInstance().thePatientSelection->currentIndex();//获取当前单元格的模
    emit goPatientEditView(curIndex.row());
}
