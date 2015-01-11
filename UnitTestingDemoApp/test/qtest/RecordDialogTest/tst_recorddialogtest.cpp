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
    void testChangeUiFieldsAndAcceptWithNewRecord();
    void testChangeUiFieldsAndRejectWithNewRecord();
    void testShowChangeUiFieldsAndAcceptWithNewRecord();
    void testShowChangeUiFieldsAndRejectWithNewRecord();

private:
    DataProviderStub *dataProvider;
    RecordDialogForUiTest *recordDialogForUi;
    PhoneRecord *record;
    const char* sampleFirstName;
    const char* sampleLastName;
    const char* samplePhone;

    void initRecordDialogForUiWithNewRecord();
    void releaseRecordDialogForUiWithNewRecord();
    void clickAllFields(RecordDialogForUiTest *rd, const char *firstName, const char *lastName, const char *phone);
    void verifyAllRecordFields(const PhoneRecord *record, const char *firstName, const char *lastName, const char *phone);
    void verifyAllUiFields(RecordDialogForUiTest *rd, const char *firstName, const char *lastName, const char *phone);
};

RecordDialogTest::RecordDialogTest() :
    sampleFirstName("John"),
    sampleLastName("Lock"),
    samplePhone("4815162342")
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
    initRecordDialogForUiWithNewRecord();
    verifyAllUiFields(recordDialogForUi, "", "", "");
    releaseRecordDialogForUiWithNewRecord();
}

void RecordDialogTest::testUiFieldsWithRecord_data()
{
    QTest::addColumn<QString>("firstName");
    QTest::addColumn<QString>("lastName");
    QTest::addColumn<QString>("phone");

    QTest::newRow("all empty") << "" << "" << "";
    QTest::newRow("all non empty") << sampleFirstName
                                   << sampleLastName
                                   << samplePhone;
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
    verifyAllUiFields(rd,
                      firstName.toStdString().c_str(),
                      lastName.toStdString().c_str(),
                      phone.toStdString().c_str());
    delete rd;
    delete record;
}

void RecordDialogTest::testChangeUiFieldsWithoutSubmitWithNewRecord()
{
    initRecordDialogForUiWithNewRecord();
    clickAllFields(recordDialogForUi, sampleFirstName, sampleLastName, samplePhone);
    // Check that record is not changed
    verifyAllRecordFields(record, "", "", "");
    releaseRecordDialogForUiWithNewRecord();
}

void RecordDialogTest::testChangeUiFieldsAndAcceptWithNewRecord()
{
    initRecordDialogForUiWithNewRecord();
    clickAllFields(recordDialogForUi, sampleFirstName, sampleLastName, samplePhone);
    QTest::mouseClick((QWidget*)recordDialogForUi->getUi()->buttonBox->button(QDialogButtonBox::Ok),
                      Qt::LeftButton);
    // Check that record has changed
    verifyAllRecordFields(record, sampleFirstName, sampleLastName, samplePhone);
    releaseRecordDialogForUiWithNewRecord();
}

void RecordDialogTest::testChangeUiFieldsAndRejectWithNewRecord()
{
    initRecordDialogForUiWithNewRecord();
    clickAllFields(recordDialogForUi, sampleFirstName, sampleLastName, samplePhone);
    QTest::mouseClick((QWidget*)recordDialogForUi->getUi()->buttonBox->button(QDialogButtonBox::Cancel),
                      Qt::LeftButton);
    // Check that record has not changed
    verifyAllRecordFields(record, "", "", "");
    releaseRecordDialogForUiWithNewRecord();
}

void RecordDialogTest::testShowChangeUiFieldsAndAcceptWithNewRecord()
{
    initRecordDialogForUiWithNewRecord();
    recordDialogForUi->show();
    QTest::qWait(1000);
    clickAllFields(recordDialogForUi, sampleFirstName, sampleLastName, samplePhone);
    QTest::qWait(1000);
    QTest::mouseClick((QWidget*)recordDialogForUi->getUi()->buttonBox->button(QDialogButtonBox::Ok),
                      Qt::LeftButton);
    // Check that record has changed
    verifyAllRecordFields(record, sampleFirstName, sampleLastName, samplePhone);
    releaseRecordDialogForUiWithNewRecord();
}

void RecordDialogTest::testShowChangeUiFieldsAndRejectWithNewRecord()
{
    initRecordDialogForUiWithNewRecord();
    recordDialogForUi->show();
    QTest::qWait(1000);
    clickAllFields(recordDialogForUi, sampleFirstName, sampleLastName, samplePhone);
    QTest::qWait(1000);
    QTest::mouseClick((QWidget*)recordDialogForUi->getUi()->buttonBox->button(QDialogButtonBox::Cancel),
                      Qt::LeftButton);
    // Check that record has not changed
    verifyAllRecordFields(record, "", "", "");
    releaseRecordDialogForUiWithNewRecord();
}

void RecordDialogTest::initRecordDialogForUiWithNewRecord()
{
    record = new PhoneRecord(*dataProvider);
    recordDialogForUi = new RecordDialogForUiTest(record);
}

void RecordDialogTest::releaseRecordDialogForUiWithNewRecord()
{
    delete recordDialogForUi;
    delete record;
}

void RecordDialogTest::clickAllFields(RecordDialogForUiTest *rd, const char *firstName, const char *lastName, const char *phone)
{
    QTest::keyClicks(rd->getUi()->leFirstName, firstName);
    QTest::keyClicks(rd->getUi()->leLastName, lastName);
    QTest::keyClicks(rd->getUi()->lePhone, phone);
}

void RecordDialogTest::verifyAllRecordFields(const PhoneRecord *record, const char *firstName, const char *lastName, const char *phone)
{
    QCOMPARE(record->getFirstName(), string(firstName));
    QCOMPARE(record->getLastName(), string(lastName));
    QCOMPARE(record->getPhone(), string(phone));
}

void RecordDialogTest::verifyAllUiFields(RecordDialogForUiTest *rd, const char *firstName, const char *lastName, const char *phone)
{
    QCOMPARE(rd->getUi()->leFirstName->text(), QString(firstName));
    QCOMPARE(rd->getUi()->leLastName->text(), QString(lastName));
    QCOMPARE(rd->getUi()->lePhone->text(), QString(phone));
}

QTEST_MAIN(RecordDialogTest)

#include "tst_recorddialogtest.moc"
