#ifndef DOCTORPATIENTEDITVIEW_H
#define DOCTORPATIENTEDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>

namespace Ui {
class DoctorPatientEditView;
}

class DoctorPatientEditView : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorPatientEditView(QWidget *parent = nullptr,int index = 0);
    ~DoctorPatientEditView();

private:
    Ui::DoctorPatientEditView *ui;
    QDataWidgetMapper *dataMapper;//数据映射

signals:
    void goPreviousView();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // DOCTORPATIENTEDITVIEW_H
