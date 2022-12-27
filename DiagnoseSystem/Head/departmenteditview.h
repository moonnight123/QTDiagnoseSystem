#ifndef DEPARTMENTEDITVIEW_H
#define DEPARTMENTEDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>
namespace Ui {
class DepartmentEditView;
}

class DepartmentEditView : public QWidget
{
    Q_OBJECT

public:
    explicit DepartmentEditView(QWidget *parent = nullptr,int index = 0);
    ~DepartmentEditView();

private:
    Ui::DepartmentEditView *ui;
    QDataWidgetMapper *dataMapper;//数据映射

signals:
    void goPreviousView();
private slots:
    void on_btSave_clicked();
    void on_btBack_clicked();
};

#endif // DEPARTMENTEDITVIEW_H
