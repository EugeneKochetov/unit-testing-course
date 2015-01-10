#ifndef RECORDDIALOG_H
#define RECORDDIALOG_H

#include <QDialog>
#include "phonerecord.h"
#include <stdexcept>

namespace Ui {
class RecordDialog;
}

class RecordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecordDialog(PhoneRecord *record, QWidget *parent = 0) throw(std::invalid_argument);
    ~RecordDialog();

    PhoneRecord *record() const;
protected:
    Ui::RecordDialog *ui;
private:
    PhoneRecord* _record;

private slots:
    virtual void accept();

};

#endif // RECORDDIALOG_H
