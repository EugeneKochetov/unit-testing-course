#include "gtest/gtest.h"
#include "csvparser.h"

TEST(csvParseLineTest, csvParseLine_EmptyLine_EmptyResult)
{
  vector<string> result;
  csvParseLine("", result);
  EXPECT_EQ(0, result.size());
}
