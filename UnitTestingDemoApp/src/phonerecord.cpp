#include "phonerecord.h"

PhoneRecord::PhoneRecord(DataProvider &dataProvider) :
    _newRecord(true),
    _dataProvider(dataProvider)
{
}

PhoneRecord::PhoneRecord(DataProvider &dataProvider, string firstName, string lastName, string phone) :
    _newRecord(false),
    _dataProvider(dataProvider),
    _firstName(firstName),
    _lastName(lastName),
    _phone(phone)
{
}

PhoneRecord::~PhoneRecord()
{
}

bool PhoneRecord::operator ==(const PhoneRecord &r)
{
    return (_firstName == r._firstName) &&
            (_lastName == r._lastName);
}

string PhoneRecord::toString()
{
    return _firstName + " " + _lastName + ": " + _phone;
}

void PhoneRecord::save()
{
    if (_newRecord)
    {
        _dataProvider.addPhoneRecord(*this);
        _newRecord = false;
    }
    else
    {
        _dataProvider.savePhoneRecord(*this);
    }
}

void PhoneRecord::remove()
{
    _dataProvider.deletePhoneRecord(*this);
    _newRecord = true;
}

