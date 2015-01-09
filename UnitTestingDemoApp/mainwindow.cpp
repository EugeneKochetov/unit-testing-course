#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "recorddialog.h"
#include "csvdataprovider.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _dataProvider = new CsvDataProvider("db.csv");
    _dataProvider->open();
    _finder = NULL;
}

MainWindow::~MainWindow()
{
    _dataProvider->close();
    delete _dataProvider;
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    PhoneRecord* r = new PhoneRecord(*_dataProvider);
    RecordDialog* rd = new RecordDialog(r, this);
    int result = rd->exec();
    if (QDialog::Accepted == result)
    {
        r->save();
    }
    delete r;
}

void MainWindow::on_actionEdit_triggered()
{
    PhoneRecord* r = static_cast<PhoneRecord*>(
                    ui->lwSearchResult->currentItem()->data(Qt::UserRole).value<void*>());
    qDebug() << "Retrieved result from row " << ui->lwSearchResult->currentRow() <<
                " with data " << r;
    RecordDialog* rd = new RecordDialog(r, this);
    int result = rd->exec();
    if (QDialog::Accepted == result)
    {
        r->save();
    }
}


void MainWindow::on_actionDelete_triggered()
{
    PhoneRecord* r = static_cast<PhoneRecord*>(
                    ui->lwSearchResult->currentItem()->data(Qt::UserRole).value<void*>());
    qDebug() << "Retrieved result from row " << ui->lwSearchResult->currentRow() <<
                " with data " << r;
    r->remove();
}

void MainWindow::on_btnSearch_clicked()
{
    if (NULL != _finder) delete _finder;
    ui->lwSearchResult->clear();

    _finder = _dataProvider->getFinder();
    _finder->filterByFirstName(ui->leFirstName->text().toStdString());
    _finder->find();

    for (list<PhoneRecord*>::const_iterator it = _finder->results.begin();
         it != _finder->results.end();
         ++it)
    {
        ui->lwSearchResult->addItem(QString::fromStdString((*it)->toString()));
        ui->lwSearchResult->item(ui->lwSearchResult->count() - 1)->
                setData(Qt::UserRole, QVariant::fromValue((void*)*it));
        qDebug() << "Added result at row " << ui->lwSearchResult->count() - 1 <<
                    " with data " << *it;
    }
}
