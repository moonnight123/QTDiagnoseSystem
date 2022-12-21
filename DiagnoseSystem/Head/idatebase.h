#ifndef IDATEBASE_H
#define IDATEBASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QtSql>
#include <QDataWidgetMapper>

class IDateBase:public QObject
{
    Q_OBJECT

public:
    static IDateBase& getInstance()
    {
        static IDateBase   instance;
        return instance;
    }

    QString userLogin(QString userName,QString password);

private:
    explicit IDateBase(QObject *parent = nullptr);
    IDateBase(IDateBase const&)               = delete;
    void operator=(IDateBase const&)  = delete;
    QSqlDatabase datebase;
    void ininDataBase();//连接数据库
public:
    bool initPatientModel();
    bool searchPatient(QString filter);
    bool deleteCurrentPatient();
    bool submitPatientEdit();
    void revertPatientEdit();
    int addNewPatient();


    QSqlTableModel  *patientTabModel;  //数据模型
    QItemSelectionModel *thePatientSelection; //选择模型
signals:


};

#endif // IDATEBASE_H
