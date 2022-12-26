#ifndef PATIENTVIEW_H
#define PATIENTVIEW_H

#include <QWidget>


namespace Ui {
class PatientView;
}

class PatientView : public QWidget
{
    Q_OBJECT

public:
    explicit PatientView(QWidget *parent = nullptr);
    ~PatientView();

private slots:
    void on_btadd_2_clicked();

    void on_btcheck_2_clicked();

    void on_btdel_2_clicked();

    void on_btchange_2_clicked();

signals:
    void goPatientEditView(int idx);

private:
    Ui::PatientView *ui;
};

#endif // PATIENTVIEW_H
