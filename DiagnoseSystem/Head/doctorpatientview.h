#ifndef DOCTORPATIENTVIEW_H
#define DOCTORPATIENTVIEW_H

#include <QWidget>

namespace Ui {
class DoctorPatientView;
}

class DoctorPatientView : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorPatientView(QWidget *parent = nullptr);
    ~DoctorPatientView();

private slots:
    void on_btcheck_clicked();

    void on_btadd_clicked();

    void on_btdel_clicked();

    void on_btchange_clicked();

signals:
    void goDoctorPatientEditView(int index);

private:
    Ui::DoctorPatientView *ui;
};

#endif // DOCTORPATIENTVIEW_H
