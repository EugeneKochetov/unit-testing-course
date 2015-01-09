#ifndef RECORDDIALOG_H
#define RECORDDIALOG_H

#include <QDialog>
#include "phonerecord.h"

namespace Ui {
class RecordDialog;
}

class RecordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecordDialog(PhoneRecord *record, QWidget *parent = 0);
    ~RecordDialog();

    PhoneRecord *record() const;
private:
    Ui::RecordDialog *ui;
    PhoneRecord* _record;

private slots:
    virtual void accept();

};

#endif // RECORDDIALOG_H
