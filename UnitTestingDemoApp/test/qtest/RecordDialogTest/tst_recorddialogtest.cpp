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
    void testUiFieldsWithRecord_data();
    void testUiFieldsWithRecord();
    void testChangeUiFieldsWithoutSubmitWithNewRecord();

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

void RecordDialogTest::testUiFieldsWithRecord_data()
{
    QTest::addColumn<QString>("firstName");
    QTest::addColumn<QString>("lastName");
    QTest::addColumn<QString>("phone");

    QTest::newRow("all empty") << "" << "" << "";
    QTest::newRow("all non empty") << "John" << "Lock" << "4815162342";
}

void RecordDialogTest::testUiFieldsWithRecord()
{
    QFETCH(QString, firstName);
    QFETCH(QString, lastName);
    QFETCH(QString, phone);
    PhoneRecord *record = new PhoneRecord(*dataProvider,
                                          firstName.toStdString(),
                                          lastName.toStdString(),
                                          phone.toStdString());
    RecordDialogForUiTest *rd = new RecordDialogForUiTest(record);
    QCOMPARE(rd->getUi()->leFirstName->text(), firstName);
    QCOMPARE(rd->getUi()->leLastName->text(), lastName);
    QCOMPARE(rd->getUi()->lePhone->text(), phone);
    delete rd;
    delete record;
}

void RecordDialogTest::testChangeUiFieldsWithoutSubmitWithNewRecord()
{
    PhoneRecord *record = dataProvider->getNewPhoneRecord();
    RecordDialogForUiTest *rd = new RecordDialogForUiTest(record);
    QTest::keyClicks(rd->getUi()->leFirstName, "John");
    QTest::keyClicks(rd->getUi()->leLastName, "Lock");
    QTest::keyClicks(rd->getUi()->lePhone, "4815162342");
    // Check that record is not changed
    QCOMPARE(rd->record()->getFirstName(), string(""));
    QCOMPARE(rd->record()->getLastName(), string(""));
    QCOMPARE(rd->record()->getPhone(), string(""));
    delete rd;
    delete record;
}

QTEST_MAIN(RecordDialogTest)

#include "tst_recorddialogtest.moc"
