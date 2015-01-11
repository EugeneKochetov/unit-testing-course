#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "phonerecord.h"

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

TEST(phoneRecordTest, save_NewRecord_RecordIsNotNew)
{
    MockDataProvider dataProvider;
    PhoneRecord *record = new PhoneRecord(dataProvider);
    record->save();
    EXPECT_FALSE(record->isNew());
}

TEST(phoneRecordTest, save_NewRecord_AddPhoneRecordIsCalled)
{
    MockDataProvider dataProvider;
    PhoneRecord *record = new PhoneRecord(dataProvider);
    EXPECT_CALL(dataProvider, addPhoneRecord(_));
    record->save();
}

TEST(phoneRecordTest, save_NewRecord_AddPhoneRecordIsCalledWithTestedRecord)
{
    MockDataProvider dataProvider;
    PhoneRecord *record = new PhoneRecord(dataProvider);
    EXPECT_CALL(dataProvider, addPhoneRecord(Ref(*record)));
    record->save();
}

TEST(phoneRecordTest, save_NotNewRecord_SavePhoneRecordIsCalled)
{
    MockDataProvider dataProvider;
    PhoneRecord *record = new PhoneRecord(dataProvider, "John", "Lock", "4815162342");
    EXPECT_CALL(dataProvider, savePhoneRecord(_));
    record->save();
}

TEST(phoneRecordTest, save_NotNewRecord_SavePhoneRecordIsCalledWithTestedRecord)
{
    MockDataProvider dataProvider;
    PhoneRecord *record = new PhoneRecord(dataProvider, "John", "Lock", "4815162342");
    EXPECT_CALL(dataProvider, savePhoneRecord(Ref(*record)));
    record->save();
}

