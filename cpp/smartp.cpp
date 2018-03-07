#include "smartp.h"

SmartP::SmartP(Assicurazione* a=0): baseP(a){}

SmartP::SmartP(const SmartP& s){
    if(s.baseP)
        baseP= s->clone();
    else
        baseP= 0;
}

SmartP::~SmartP(){
    if(baseP)
        delete baseP;
}

SmartP& SmartP::operator= (const SmartP& s){
    if(this != &s){
        delete baseP;
        baseP= s.baseP;
    }
    return *this;
}

Assicurazione& SmartP::operator* () const{
    return const_cast<Assicurazione&> (*baseP);
}

Assicurazione* SmartP::operator-> () const{
    return const_cast<Assicurazione*> (baseP);
}

bool SmartP::operator== (const SmartP& s) const{
    return baseP->isEqual(*s.baseP);
}

bool SmartP::operator!= (const SmartP& s) const{
    return baseP != s.baseP;
}
