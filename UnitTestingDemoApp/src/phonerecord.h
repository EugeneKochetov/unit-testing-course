#ifndef RECORD_H
#define RECORD_H

#include <string>
#include "dataprovider.h"

using namespace std;

class DataProvider;

class PhoneRecord
{
private:
    bool _newRecord;
    DataProvider& _dataProvider;

    string _firstName;
    string _lastName;
    string _phone;

public:
    PhoneRecord(DataProvider& dataProvider);
    PhoneRecord(DataProvider& dataProvider,
                string firstName,
                string lastName,
                string phone);
    ~PhoneRecord();

    bool operator ==(const PhoneRecord& r);
    string toString();

    void save();
    void remove();
    bool isNew() const { return _newRecord; }
    string getFirstName() const { return _firstName; }
    void setFirstName(const string &value) { _firstName = value; }
    string getLastName() const { return _lastName; }
    void setLastName(const string &value) { _lastName = value; }
    string getPhone() const { return _phone; }
    void setPhone(const string &value) { _phone = value; }
};

#endif // RECORD_H
