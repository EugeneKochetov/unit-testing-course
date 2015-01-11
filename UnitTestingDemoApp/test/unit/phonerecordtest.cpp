#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "phonerecord.h"
#include <string>

using namespace std;
using ::testing::_;
using ::testing::Ref;

class MockDataProvider : public DataProvider
{
    // DataProvider interface
public:
    MOCK_METHOD0(open, void());
    MOCK_METHOD0(close, void());
    MOCK_METHOD1(addPhoneRecord, void(PhoneRecord &record));
    MOCK_METHOD1(savePhoneRecord, void(PhoneRecord &record));
    MOCK_METHOD1(deletePhoneRecord, void(PhoneRecord &record));
    MOCK_METHOD0(getFinder, Finder*());
};

class PhoneRecordTestWithFixture : public ::testing::Test
{
public:
    PhoneRecordTestWithFixture() :
        notNewRecordFirstName("John"),
        notNewRecordLastName("Lock"),
        notNewRecordPhone("4815162342")
    {}

protected:
    virtual void SetUp()
    {
        newRecord = new PhoneRecord(dataProvider);
        notNewRecord = new PhoneRecord(dataProvider,
                                       notNewRecordFirstName,
                                       notNewRecordLastName,
                                       notNewRecordPhone);
    }

    virtual void TearDown()
    {
        delete newRecord;
        delete notNewRecord;
    }

    MockDataProvider dataProvider;
    PhoneRecord *newRecord;
    PhoneRecord *notNewRecord;
    const string notNewRecordFirstName;
    const string notNewRecordLastName;
    const string notNewRecordPhone;
};

TEST(phoneRecordTest, contructor_WithDataProviderOnly_IsNew)
{
    MockDataProvider dataProvider;
    PhoneRecord *record = new PhoneRecord(dataProvider);
    EXPECT_TRUE(record->isNew());
}

TEST(phoneRecordTest, contructor_WithDataProviderAndValues_IsNotNew)
{
    MockDataProvider dataProvider;
    PhoneRecord *record = new PhoneRecord(dataProvider, "John", "Lock", "4815162342");
    EXPECT_FALSE(record->isNew());
}

TEST(phoneRecordTest, contructor_WithDataProviderOnly_AllFieldsEmpty)
{
    MockDataProvider dataProvider;
    PhoneRecord *record = new PhoneRecord(dataProvider);
    EXPECT_EQ("", record->getFirstName());
    EXPECT_EQ("", record->getLastName());
    EXPECT_EQ("", record->getPhone());
}

TEST(phoneRecordTest, contructor_WithDataProviderAndValues_FieldsNotEmpty)
{
    MockDataProvider dataProvider;
    PhoneRecord *record = new PhoneRecord(dataProvider, "John", "Lock", "4815162342");
    EXPECT_EQ("John", record->getFirstName());
    EXPECT_EQ("Lock", record->getLastName());
    EXPECT_EQ("4815162342", record->getPhone());
}

TEST_F(PhoneRecordTestWithFixture, save_NewRecord_RecordIsNotNew)
{
    newRecord->save();
    EXPECT_FALSE(newRecord->isNew());
}

TEST_F(PhoneRecordTestWithFixture, save_NewRecord_AddPhoneRecordIsCalled)
{
    EXPECT_CALL(dataProvider, addPhoneRecord(_));
    newRecord->save();
}

TEST_F(PhoneRecordTestWithFixture, save_NewRecord_AddPhoneRecordIsCalledWithTestedRecord)
{
    EXPECT_CALL(dataProvider, addPhoneRecord(Ref(*newRecord)));
    newRecord->save();
}

TEST_F(PhoneRecordTestWithFixture, save_NotNewRecord_SavePhoneRecordIsCalled)
{
    EXPECT_CALL(dataProvider, savePhoneRecord(_));
    notNewRecord->save();
}

TEST_F(PhoneRecordTestWithFixture, save_NotNewRecord_SavePhoneRecordIsCalledWithTestedRecord)
{
    EXPECT_CALL(dataProvider, savePhoneRecord(Ref(*notNewRecord)));
    notNewRecord->save();
}
