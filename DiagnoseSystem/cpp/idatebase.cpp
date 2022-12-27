#include "idatebase.h"
#include <QDebug>
#include <QUuid>
IDateBase::IDateBase(QObject *parent) : QObject(parent){
    ininDataBase();
}

void IDateBase::ininDataBase()
{
    datebase=QSqlDatabase::addDatabase("QSQLITE"); //添加 SQL LITE数据库驱动
    QString aFile = "D:/QT/DiagnoseSystem.db";
    datebase.setDatabaseName(aFile); //设置数据库名称

    if (!datebase.open())   //打开数据库
    {
       qDebug()<<"failed to open database";
    }else{
        qDebug()<<" open database is ok";
    }
}

bool IDateBase::initModel(QSqlTableModel *TableModel,QString name,QString fIndex)
{
    TableModel->setTable(name);//与数据库的表关联
    TableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//数据保存方式，OnManualSubmit , OnRowChange
    TableModel->setSort(TableModel->fieldIndex(fIndex),Qt::AscendingOrder); //排序
    if (!(TableModel->select()))//查询数据
    {
       return false;
    }
    return true;
}

bool IDateBase::search(QSqlTableModel *TableModel,QString filter)
{
    TableModel->setFilter(filter);//查询操作
    return TableModel->select();
}

void IDateBase::deleteCurrunt(QSqlTableModel *TableModel,QItemSelectionModel *SelectionModel)
{
    QModelIndex curIndex = SelectionModel->currentIndex();//获取当前单元格的模型索引
    TableModel->removeRow( curIndex.row( ));
    TableModel->submitAll();
    TableModel->select();
}

bool IDateBase::initPatientModel()
{
    patientTabModel = new QSqlTableModel(this,datebase);//数据表
    if(!initModel(patientTabModel,"Patient","name")){
        return false;
    }
    thePatientSelection = new QItemSelectionModel(patientTabModel);//选择模型和patientTabModel模型关联
    return true;
}

QString IDateBase::userLogin(QString userName, QString password)
{
    //return  "loginOK";
    QSqlQuery query; //查询出当前记录的所有字段
    query.prepare("select username,password from user where username = :USER");
    query.bindValue(":USER",userName);
    query.exec();
    query.first();
    if(query.first() && query.value("username").isValid()){
           QString passwd = query.value("password").toString();
           if(passwd == password){
               return "loginOK";
           }else{
               qDebug()<<"wrong password";
               return "wrongPassword";
           }
    }
    else{
        qDebug()<<"no such username";
        return "wrongUsername";
    }

}

void IDateBase::deleteCurrentPatient()
{
    deleteCurrunt(patientTabModel,thePatientSelection);
}

bool IDateBase::searchPatient(QString filter)
{
    return search(patientTabModel,filter);
}

bool IDateBase::submitPatientEdit()
{
    return patientTabModel->submitAll();//提交所有未更新的修改到数据库
}

void IDateBase::revertPatientEdit()
{
    patientTabModel->revertAll();
}

int IDateBase::addNewPatient(){
    patientTabModel->insertRow(patientTabModel->rowCount(),QModelIndex());//在末尾添加一个记录
    QModelIndex curIndex = patientTabModel->index(patientTabModel->rowCount()-1,1);

    int curRecNo  = curIndex.row();
    QSqlRecord curRec = patientTabModel->record(curRecNo);
    curRec.setValue("CREATEDTIMESTAMP",QDateTime::currentDateTime().toString("yyyy-MM-dd"));

    QString UID = QUuid::createUuid().toString();
    UID.remove("{").remove("}").remove("-");
    curRec.setValue("ID",UID);
    patientTabModel->setRecord(curRecNo,curRec);
    return curIndex.row();
}

bool IDateBase::initDoctorModel()
{
    doctorTabModel = new QSqlTableModel(this,datebase);//数据表
    if(!initModel(doctorTabModel,"Doctor","name")){
        return false;
    }
    theDoctorSelection = new QItemSelectionModel(doctorTabModel);//选择模型和patientTabModel模型关联
    return true;
}

bool IDateBase::searchDoctor(QString filter)
{
    return search(doctorTabModel,filter);
}

void IDateBase::deleteCurruntDoctor()
{
    deleteCurrunt(doctorTabModel,theDoctorSelection);
}

int IDateBase::addNewDoctor()
{
    doctorTabModel->insertRow(doctorTabModel->rowCount(),QModelIndex());//在末尾添加一个记录
    QModelIndex curIndex = doctorTabModel->index(doctorTabModel->rowCount()-1,1);
    return curIndex.row();
}

bool IDateBase::submitDoctorEdit()
{
    return doctorTabModel->submitAll();//提交所有未更新的修改到数据库
}

void IDateBase::revertDoctorEdit()
{
    doctorTabModel->revertAll();
}

bool IDateBase::initDepartmentModel()
{
    departmentModel = new QSqlTableModel(this,datebase);//数据表
    if(!initModel(departmentModel,"Department","name")){
        return false;
    }
    theDepartmentSelection = new QItemSelectionModel(departmentModel);//选择模型和patientTabModel模型关联
    return true;
}

bool IDateBase::searchDepartment(QString filter)
{
    return search(departmentModel,filter);
}

void IDateBase::deleteCurruntDepartment()
{
    deleteCurrunt(departmentModel,theDepartmentSelection);
}

int IDateBase::addNewDepartment()
{
    departmentModel->insertRow(departmentModel->rowCount(),QModelIndex());//在末尾添加一个记录
    QModelIndex curIndex = departmentModel->index(departmentModel->rowCount()-1,1);
    return curIndex.row();
}

bool IDateBase::submitDepartmentEdit()
{
    return departmentModel->submitAll();//提交所有未更新的修改到数据库
}

void IDateBase::revertDepartmentEdit()
{
    departmentModel->revertAll();
}
