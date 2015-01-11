#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "phonerecord.h"

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

