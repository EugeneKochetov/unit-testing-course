#ifndef FINDER_H
#define FINDER_H

#include "phonerecord.h"
#include <string>
#include <list>

using namespace std;

class PhoneRecord;

class Finder
{
public:
    Finder();
    virtual ~Finder();

    virtual void filterByFirstName(string firstName) = 0;
    virtual void find() = 0;

    list<PhoneRecord*> results;
};

#endif // FINDER_H
