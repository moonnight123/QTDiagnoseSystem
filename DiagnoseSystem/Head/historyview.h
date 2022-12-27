#ifndef HISTORYVIEW_H
#define HISTORYVIEW_H

#include <QWidget>

namespace Ui {
class HistoryView;
}

class HistoryView : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryView(QWidget *parent = nullptr);
    ~HistoryView();

private slots:
    void on_btcheck_clicked();

    void on_btdel_clicked();

private:
    Ui::HistoryView *ui;
};

#endif // HISTORYVIEW_H
