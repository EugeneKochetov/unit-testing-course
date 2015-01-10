#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "recorddialog.h"
#include "phonerecord.h"

class RecordDialogTest : public QObject
{
    Q_OBJECT

public:
    RecordDialogTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testConstructor();
};

RecordDialogTest::RecordDialogTest()
{
}

void RecordDialogTest::initTestCase()
{
}

void RecordDialogTest::cleanupTestCase()
{
}

void RecordDialogTest::testConstructor()
{
    RecordDialog *rd = new RecordDialog(NULL);
    delete rd;
}

QTEST_MAIN(RecordDialogTest)

#include "tst_recorddialogtest.moc"
