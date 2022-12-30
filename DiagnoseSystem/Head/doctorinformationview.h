#ifndef DOCTORINFORMATIONVIEW_H
#define DOCTORINFORMATIONVIEW_H

#include <QWidget>

namespace Ui {
class DoctorInformationView;
}

class DoctorInformationView : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorInformationView(QWidget *parent = nullptr);
    ~DoctorInformationView();

private:
    Ui::DoctorInformationView *ui;
};

#endif // DOCTORINFORMATIONVIEW_H
