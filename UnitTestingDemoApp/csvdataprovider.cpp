#include "csvdataprovider.h"
#include <fstream>
#include <QtDebug>

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

        string firstName;
        string lastName;
        string phone;

        size_t startPos = 0;
        size_t commaPos = line.find_first_of(',', startPos);
        if (string::npos == commaPos) continue;
        firstName = line.substr(startPos, commaPos - startPos);

        startPos = commaPos + 1;
        commaPos = line.find_first_of(',', startPos);
        if (string::npos == commaPos) continue;
        lastName = line.substr(startPos, commaPos - startPos);

        startPos = commaPos + 1;
        phone = line.substr(startPos);

        _records.push_back(PhoneRecord(*this, firstName, lastName, phone));

        qDebug() << "Added record: " << firstName.c_str() << ", "
                 << lastName.c_str() << ", "
                 << phone.c_str();
    }
    input.close();
}

void CsvDataProvider::close()
{
    fstream output;
    output.open(_fileName.c_str(), fstream::out);

    for (list<PhoneRecord>::const_iterator it = _records.begin(); it != _records.end(); ++it)
    {
        output << it->getFirstName() << "," << it->getLastName() << "," << it->getPhone() << endl;
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
