#ifndef REGISTERVIEW_H
#define REGISTERVIEW_H

#include <QWidget>

namespace Ui {
class RegisterView;
}

class RegisterView : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterView(QWidget *parent = nullptr);
    ~RegisterView();

private slots:
    void on_btregister_clicked();

    void on_btback_clicked();

private:
    Ui::RegisterView *ui;
signals:
    void goLoginView();
};

#endif // REGISTERVIEW_H
