#include "dataprovider.h"

DataProvider::DataProvider()
{

}

DataProvider::~DataProvider()
{

}

PhoneRecord* DataProvider::getNewPhoneRecord()
{
    return new PhoneRecord(*this);
}

