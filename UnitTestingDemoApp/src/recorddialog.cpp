#include "recorddialog.h"
#include "ui_recorddialog.h"

RecordDialog::RecordDialog(PhoneRecord *record, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecordDialog),
    _record(record)
{
    ui->setupUi(this);
    ui->leFirstName->setText(QString::fromStdString(_record->getFirstName()));
    ui->leLastName->setText(QString::fromStdString(_record->getLastName()));
    ui->lePhone->setText(QString::fromStdString(_record->getPhone()));
}

RecordDialog::~RecordDialog()
{
    delete ui;
}
PhoneRecord *RecordDialog::record() const
{
    return _record;
}

void RecordDialog::accept()
{
    _record->setFirstName(ui->leFirstName->text().toStdString());
    _record->setLastName(ui->leLastName->text().toStdString());
    _record->setPhone(ui->lePhone->text().toStdString());
    QDialog::accept();
}

