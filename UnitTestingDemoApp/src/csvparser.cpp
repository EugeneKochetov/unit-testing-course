#include "csvparser.h"

void csvParseLine(string line, vector<string>& result)
{
    if (0 == line.size()) return;

    size_t startPos = 0;
    size_t commaPos;
    while (string::npos != (commaPos = line.find_first_of(',', startPos)))
    {
           result.push_back(line.substr(startPos, commaPos - startPos));
           startPos = commaPos + 1;
    }
    result.push_back(line.substr(startPos));
}

string csvEncodeLine(const vector<string>& fields)
{
    string result;

    for (vector<string>::const_iterator it = fields.begin();
         it != fields.end();
         ++it)
    {
        result += *it + ',';
    }
    result.resize(result.size() - 1);

    return result;
}
