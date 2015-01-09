#ifndef CSVDATAPROVIDER_H
#define CSVDATAPROVIDER_H

#include <list>
#include "dataprovider.h"
#include "finder.h"

using namespace std;

class CsvDataProvider : public DataProvider
{
    friend class CsvFinder;
public:
    CsvDataProvider(string fileName);
    ~CsvDataProvider();

    // DataProvider interface
public:
    virtual void open();
    virtual void close();
    virtual void addPhoneRecord(PhoneRecord& record);
    virtual void savePhoneRecord(PhoneRecord &record);
    virtual void deletePhoneRecord(PhoneRecord &record);
    virtual Finder *getFinder();

private:
    string _fileName;
    bool _isOpen;
    list<PhoneRecord> _records;
};

class CsvFinder : public Finder
{
public:
    CsvFinder(CsvDataProvider &dataProvider);
    ~CsvFinder();

    // Finder interface
public:
    virtual void filterByFirstName(string firstName);
    virtual void find();

private:
    CsvDataProvider &_dataProvider;
    string _firstNameFilter;
};

#endif // CSVDATAPROVIDER_H
