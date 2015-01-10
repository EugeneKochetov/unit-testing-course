#include "csvdataprovider.h"
#include <fstream>
#include <QtDebug>
#include "csvparser.h"

CsvDataProvider::CsvDataProvider(string fileName) :
    _fileName(fileName),
    _isOpen(false)
{
}

CsvDataProvider::~CsvDataProvider()
{
    if (_isOpen) close();
}

void CsvDataProvider::open()
{
    fstream input;

    input.open(_fileName.c_str(), fstream::in);
    if (!input.is_open())
    {
        qDebug() << "Failed to open file: " << _fileName.c_str();
        return;
    }

    while (!input.eof())
    {
        string line;
        getline(input, line);
        qDebug() << "Read line: \"" << line.c_str() << "\"";

        vector<string> fields;
        csvParseLine(line, fields);

        if (fields.size() < 3) continue;

        _records.push_back(PhoneRecord(*this, fields[0], fields[1], fields[2]));

        qDebug() << "Added record: " << fields[0].c_str() << ", "
                 << fields[1].c_str() << ", "
                 << fields[2].c_str();
    }
    input.close();
}

void CsvDataProvider::close()
{
    fstream output;
    output.open(_fileName.c_str(), fstream::out);

    for (list<PhoneRecord>::const_iterator it = _records.begin(); it != _records.end(); ++it)
    {
        vector<string> fields;
        fields.push_back(it->getFirstName());
        fields.push_back(it->getLastName());
        fields.push_back(it->getPhone());
        output << csvEncodeLine(fields) << endl;
    }
    output.close();
}

void CsvDataProvider::addPhoneRecord(PhoneRecord &record)
{
    _records.push_back(record);
}

void CsvDataProvider::savePhoneRecord(PhoneRecord &record)
{
    // Assume that application uses the same objects that are stored in data provider
    // So, do nothing here
}

void CsvDataProvider::deletePhoneRecord(PhoneRecord &record)
{
    _records.remove(record);
}

Finder *CsvDataProvider::getFinder()
{
    return new CsvFinder(*this);
}


CsvFinder::CsvFinder(CsvDataProvider &dataProvider) :
    _dataProvider(dataProvider)
{

}

CsvFinder::~CsvFinder()
{

}

void CsvFinder::filterByFirstName(string firstName)
{
    _firstNameFilter = firstName;
}

void CsvFinder::find()
{
    results.clear();
    for (list<PhoneRecord>::iterator it = _dataProvider._records.begin();
         it != _dataProvider._records.end();
         ++it)
    {
        if (("" == _firstNameFilter) || (it->getFirstName() == _firstNameFilter))
            results.push_back(&(*it));
    }
}
