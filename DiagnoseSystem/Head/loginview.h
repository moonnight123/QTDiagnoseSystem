#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>

namespace Ui {
class LoginView;
}

class LoginView : public QWidget
{
    Q_OBJECT

public:
    explicit LoginView(QWidget *parent = nullptr);
    ~LoginView();

private slots:
    void on_btSignIn_clicked();

    void on_btSignOn_clicked();

signals:
    void loginSuccess();
    void loginFailed();
    void goRegisterView();
    void loginSuccess2();

private:
    Ui::LoginView *ui;
};

#endif // LOGINVIEW_H
