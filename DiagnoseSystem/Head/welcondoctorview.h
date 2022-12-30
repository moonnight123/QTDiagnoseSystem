#ifndef WELCONDOCTORVIEW_H
#define WELCONDOCTORVIEW_H

#include <QWidget>

namespace Ui {
class WelconDoctorView;
}

class WelconDoctorView : public QWidget
{
    Q_OBJECT

public:
    explicit WelconDoctorView(QWidget *parent = nullptr);
    ~WelconDoctorView();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
signals:
    void goDoctorInformationView();
    void goDoctorPatientView();
private:
    Ui::WelconDoctorView *ui;
};

#endif // WELCONDOCTORVIEW_H
