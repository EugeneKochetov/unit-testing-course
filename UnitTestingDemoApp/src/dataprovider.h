#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include "phonerecord.h"
#include "finder.h"

class PhoneRecord;
class Finder;

class DataProvider
{
public:
    DataProvider();
    virtual ~DataProvider();

    virtual void open() = 0;
    virtual void close() = 0;

    virtual PhoneRecord *getNewPhoneRecord();

    virtual void addPhoneRecord(PhoneRecord& record) = 0;
    virtual void savePhoneRecord(PhoneRecord& record) = 0;
    virtual void deletePhoneRecord(PhoneRecord& record) = 0;
    virtual Finder *getFinder() = 0;
};

#endif // DATAPROVIDER_H
