#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <string>
#include <vector>

using namespace std;

void csvParseLine(string line, vector<string>& result);
string csvEncodeLine(const vector<string>& fields);

#endif // CSVPARSER_H

