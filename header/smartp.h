#ifndef SMARTP_H
#define SMARTP_H

#include "assicurazione.h"

class SmartP{
private:
        Assicurazione* baseP;
public:
    SmartP(Assicurazione*);
    ~SmartP();
    SmartP(const SmartP&);
    SmartP& operator= (const SmartP&);
    Assicurazione& operator*() const;
    Assicurazione* operator->() const;
    bool operator== (const SmartP&) const;
    bool operator!= (const SmartP&) const;
};

#endif // SMARTP_H
