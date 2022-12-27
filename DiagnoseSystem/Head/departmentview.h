#ifndef DEPARTMENTVIEW_H
#define DEPARTMENTVIEW_H

#include <QWidget>

namespace Ui {
class DepartmentView;
}

class DepartmentView : public QWidget
{
    Q_OBJECT

public:
    explicit DepartmentView(QWidget *parent = nullptr);
    ~DepartmentView();

private slots:
    void on_btcheck_clicked();

    void on_btadd_clicked();

    void on_btdel_clicked();

    void on_btchange_clicked();
signals:
    void goDepartmentEditView(int idx);
private:
    Ui::DepartmentView *ui;

};

#endif // DEPARTMENTVIEW_H
