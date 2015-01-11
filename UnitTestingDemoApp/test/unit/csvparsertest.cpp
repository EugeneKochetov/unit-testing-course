#include "gtest/gtest.h"
#include "csvparser.h"
#include <vector>

using namespace std;

class TestParam
{
public:
    TestParam(string line, int nOfFields) : line(line), nOfFields(nOfFields) {}
    TestParam(string line,
              int nOfFields,
              string v0,
              string v1 = "",
              string v2 = "",
              string v3 = "",
              string v4 = "") : line(line), nOfFields(nOfFields)
    {
        values.push_back(v0);
        values.push_back(v1);
        values.push_back(v2);
        values.push_back(v3);
        values.push_back(v4);
    }

    string line;
    int nOfFields;
    vector<string> values;
};

class CsvParseLineParameterizedTests : public ::testing::TestWithParam< TestParam > {};


TEST(csvParseLineTest, csvParseLine_EmptyLine_EmptyResult)
{
  vector<string> result;
  csvParseLine("", result);
  EXPECT_EQ(0, result.size());
}

TEST_P(CsvParseLineParameterizedTests, csvParseLine_ParameterLine_VerifyNumberOfFields)
{
    vector<string> result;
    csvParseLine(GetParam().line, result);
    EXPECT_EQ(GetParam().nOfFields, result.size());
}

TEST_P(CsvParseLineParameterizedTests, csvParseLine_ParameterLine_VerifyValues)
{
    vector<string> result;
    csvParseLine(GetParam().line, result);
    // Verify values but not more than number of fields
    int nOfValuesToVerfiy = min<int>(GetParam().nOfFields, GetParam().values.size());
    for (int i = 0; i < nOfValuesToVerfiy; ++i)
    {
        EXPECT_EQ(GetParam().values[i], result[i]);
    }
}

INSTANTIATE_TEST_CASE_P(SingleField,
                        CsvParseLineParameterizedTests,
                        ::testing::Values(TestParam(" ", 1, " "),
                                          TestParam("Field1", 1, "Field1"),
                                          TestParam("Field with space", 1, "Field with space")));

INSTANTIATE_TEST_CASE_P(TwoFields,
                        CsvParseLineParameterizedTests,
                        ::testing::Values(TestParam(",", 2, "", ""),
                                          TestParam(" , ", 2, " ", " "),
                                          TestParam("Field1,Field2", 2, "Field1", "Field2"),
                                          TestParam("Field1 with space, Field2", 2, "Field1 with space", "Field2")));

INSTANTIATE_TEST_CASE_P(MultipleFields,
                        CsvParseLineParameterizedTests,
                        ::testing::Values(TestParam(",,", 3, "", "", ""),
                                          TestParam("", 0),
                                          TestParam("1,2,3,4,5", 5, "1", "2", "3", "4", "5"),
                                          TestParam(",,,,,,,,,10", 10)));
