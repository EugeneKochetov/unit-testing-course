#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "recorddialog.h"
#include "ui_recorddialog.h"
#include "phonerecord.h"
#include "dataprovider.h"

// DataProvider class for tests
class DataProviderStub : public DataProvider
{
    // DataProvider interface
public:
    virtual void open() {};
    virtual void close() {};
    virtual void addPhoneRecord(PhoneRecord &record) {};
    virtual void savePhoneRecord(PhoneRecord &record) {};
    virtual void deletePhoneRecord(PhoneRecord &record) {};
    virtual Finder *getFinder() { return NULL; };
};

// RecordDialog class for UI tests
class RecordDialogForUiTest : public RecordDialog
{
public:
    explicit RecordDialogForUiTest(PhoneRecord* record, QWidget *parent = 0) : RecordDialog(record, parent) {}
    Ui::RecordDialog *getUi() { return ui; }
};

class RecordDialogTest : public QObject
{
    Q_OBJECT

public:
    RecordDialogTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testConstructorWithNull();
    void testConstructorWithNewRecord();
    void testUiFieldsWithNewRecord();

private:
    DataProviderStub *dataProvider;
};

RecordDialogTest::RecordDialogTest()
{
}

void RecordDialogTest::initTestCase()
{
    dataProvider = new DataProviderStub();
}

void RecordDialogTest::cleanupTestCase()
{
    delete dataProvider;
}

void RecordDialogTest::testConstructorWithNull()
{
    RecordDialog *rd;
    QVERIFY_EXCEPTION_THROWN(rd = new RecordDialog(NULL), std::invalid_argument);
}

void RecordDialogTest::testConstructorWithNewRecord()
{
    PhoneRecord *record = dataProvider->getNewPhoneRecord();
    RecordDialog *rd = new RecordDialog(record);
    QCOMPARE(rd->record(), record);
    delete rd;
    delete record;
}

void RecordDialogTest::testUiFieldsWithNewRecord()
{
    PhoneRecord *record = dataProvider->getNewPhoneRecord();
    RecordDialogForUiTest *rd = new RecordDialogForUiTest(record);
    QCOMPARE(rd->getUi()->leFirstName->text(), QString(""));
    QCOMPARE(rd->getUi()->leLastName->text(), QString(""));
    QCOMPARE(rd->getUi()->lePhone->text(), QString(""));
    delete rd;
    delete record;
}

QTEST_MAIN(RecordDialogTest)

#include "tst_recorddialogtest.moc"
