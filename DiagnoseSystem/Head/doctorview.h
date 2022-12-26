#ifndef DOCTORVIEW_H
#define DOCTORVIEW_H

#include <QWidget>

namespace Ui {
class DoctorView;
}

class DoctorView : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorView(QWidget *parent = nullptr);
    ~DoctorView();

private slots:
    void on_btcheck_clicked();

    void on_btadd_clicked();

    void on_btdel_clicked();

    void on_btchange_clicked();

signals:
    void goDoctorEditView(int idx);
private:
    Ui::DoctorView *ui;
};

#endif // DOCTORVIEW_H
