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
