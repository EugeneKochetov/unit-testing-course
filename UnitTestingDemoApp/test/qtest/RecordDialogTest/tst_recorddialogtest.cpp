#include <QString>
#include <QtTest>
#include <QCoreApplication>

class RecordDialogTest : public QObject
{
    Q_OBJECT

public:
    RecordDialogTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1_data();
    void testCase1();
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

void RecordDialogTest::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

void RecordDialogTest::testCase1()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(RecordDialogTest)

#include "tst_recorddialogtest.moc"
