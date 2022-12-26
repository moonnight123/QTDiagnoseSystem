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

bool IDateBase::initPatientModel()
{
    patientTabModel = new QSqlTableModel(this,datebase);//数据表
    patientTabModel->setTable("Patient");//与数据库的表关联
    patientTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//数据保存方式，OnManualSubmit , OnRowChange
    patientTabModel->setSort(patientTabModel->fieldIndex("name"),Qt::AscendingOrder); //排序
    if (!(patientTabModel->select()))//查询数据
    {
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

bool IDateBase::deleteCurrentPatient()
{
    QModelIndex curIndex = thePatientSelection->currentIndex();//获取当前单元格的模型索引
    patientTabModel->removeRow( curIndex.row( ));
    patientTabModel->submitAll();
    patientTabModel->select();
}

bool IDateBase::searchPatient(QString filter)
{
    patientTabModel->setFilter(filter);//查询操作
    return patientTabModel->select();
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
