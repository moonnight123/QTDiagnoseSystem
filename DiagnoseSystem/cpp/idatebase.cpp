#include "idatebase.h"
#include <QDebug>
#include <QUuid>
#include "loginview.h"
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
    query.prepare("select ID,username,password from user where username = :USER");
    query.bindValue(":USER",userName);
    query.exec();
    query.first();
    if(query.first() && query.value("username").isValid()){
           QString passwd = query.value("password").toString();
           if(passwd == password){
               QString userID = query.value("ID").toString();
               this->userName = userID;
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

QString IDateBase::userRegister(QString ID, QString FullName, QString userName, QString passWord, QString repassWord)
{
    QSqlQuery query;
    if(passWord!=repassWord){
        return "密码重复";
    }

    else{
        query.prepare("select ID,username,password from user where username = :USER");
        query.bindValue(":USER",userName);
        query.exec();
        query.first();
        if(query.first() && query.value("username").isValid()){
            return "用户名已存在";
        }

        else{
            query.prepare("insert into user(ID,FULLNAME,USERNAME,PASSWORD)values(:id,:full,:username,:password)");
            query.bindValue(":id",ID);
            query.bindValue(":full",FullName);
            query.bindValue(":username",userName);
            query.bindValue(":password",passWord);
            bool ni= query.exec();
            if(!ni)
            {
                return "注册失败";
            }
            else
            {
                return "注册成功";
            }
        }
    }
}

void IDateBase::addNewHistory(QString Event)
{
    QSqlQuery query;
    query.prepare("insert into history(ID,USER_ID,EVENT,TIMESTAMP)values(:id,:user,:event,:time)");
    QString UID = QUuid::createUuid().toString();
    UID.remove("{").remove("}").remove("-");
    query.bindValue(":id",UID);
    query.bindValue(":user",userName);
    query.bindValue(":event",Event);
    query.bindValue(":time",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    bool ni= query.exec();
    if(!ni)
    {
        QSqlError lastError=query.lastError ();
        qDebug()<<lastError.driverText ()<<QString(QObject::tr ("插入失败\n"));
    }
    else
    {
        qDebug()<<QObject::tr ("插入成功\n");
    }
}

int IDateBase::initHistoryModel()
{
    historyTabModel = new QSqlTableModel(this,datebase);//数据表
    if(!initModel(historyTabModel,"History","TIMESTAMP")){
        return false;
    }
    theHistorySelection = new QItemSelectionModel(historyTabModel);//选择模型和patientTabModel模型关联
    return true;
}

bool IDateBase::searchHistory(QString filter)
{
    return search(historyTabModel,filter);
}

void IDateBase::deleteCurruntHistory()
{
    deleteCurrunt(historyTabModel,theHistorySelection);
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


