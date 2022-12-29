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
    QString userRegister(QString ID,QString FullName,QString userName,QString passWord,QString repassWord);
    QString userName;

private:
    explicit IDateBase(QObject *parent = nullptr);
    IDateBase(IDateBase const&)               = delete;
    void operator=(IDateBase const&)  = delete;
    QSqlDatabase datebase;
    void ininDataBase();//连接数据库

public:
    bool initModel(QSqlTableModel *TableModel,QString name,QString fIndex);//初始化模型
    bool search(QSqlTableModel *TableModel,QString filter);//查询
    void deleteCurrunt(QSqlTableModel *TableModel,QItemSelectionModel *SelectionModel);//删除

    bool initPatientModel();//初始化患者模型
    bool searchPatient(QString filter);//Patient数据查询
    void deleteCurrentPatient();
    bool submitPatientEdit();//提交所有未更新的修改到数据库
    void revertPatientEdit();
    int addNewPatient();

    bool initDoctorModel();
    bool searchDoctor(QString filter);
    void deleteCurruntDoctor();
    int addNewDoctor();
    bool submitDoctorEdit();
    void revertDoctorEdit();

    bool initDepartmentModel();
    bool searchDepartment(QString filter);
    void deleteCurruntDepartment();
    int addNewDepartment();
    bool submitDepartmentEdit();
    void revertDepartmentEdit();

    void addNewHistory(QString Event);
    int initHistoryModel();
    bool searchHistory(QString filter);
    void deleteCurruntHistory();

    //数据模型
    QSqlTableModel  *patientTabModel;
    QSqlTableModel *doctorTabModel;
    QSqlTableModel *departmentModel;
    QSqlTableModel *historyTabModel;

    //选择模型
    QItemSelectionModel *thePatientSelection;
    QItemSelectionModel *theDoctorSelection;
    QItemSelectionModel *theDepartmentSelection;
    QItemSelectionModel *theHistorySelection;
signals:


};

#endif // IDATEBASE_H
