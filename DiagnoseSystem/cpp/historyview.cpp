#include "historyview.h"
#include "ui_historyview.h"
#include "idatebase.h"

HistoryView::HistoryView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryView)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);
    IDateBase &iDatabase = IDateBase::getInstance();
    if(iDatabase.initHistoryModel()){
        ui->tableView->setModel(iDatabase.historyTabModel);
        ui->tableView->setSelectionModel(iDatabase.theHistorySelection);
    }
}

HistoryView::~HistoryView()
{
    delete ui;
}

void HistoryView::on_btcheck_clicked()
{
    QString filter = QString("TIMESTAMP like '%%1%' ").arg(ui->lineEdit->text());//获取查询的字符串，采取模糊查询
    IDateBase::getInstance().searchHistory(filter);
}

void HistoryView::on_btdel_clicked()
{
    IDateBase::getInstance().deleteCurruntHistory();
}
