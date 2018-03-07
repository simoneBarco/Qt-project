#include <iostream>
#include "sanitaria.h"

using std::cout;
using std::endl;

Sanitaria::Sanitaria(QString n, QDate dSt, QDate dSc, int m, bool i, bool a,
                     bool dm): Assicurazione(n, dSt, dSc), massimale(m),
                     individuale(i), ambulanza(a), domicilio(dm) {}

Sanitaria::Sanitaria(const Sanitaria& s): Assicurazione(s){
    massimale = s.massimale;
    individuale = s.individuale;
    ambulanza = s.ambulanza;
    domicilio = s.domicilio;
}

bool Sanitaria::operator== (const Sanitaria& s) const{
    return Assicurazione::operator== (s) && massimale == s.massimale &&
            individuale == s.individuale && ambulanza == s.ambulanza &&
            domicilio == s.domicilio;
}

int Sanitaria::getMass() const{
    return massimale;
}

bool Sanitaria::getInd() const{
    return individuale;
}

bool Sanitaria::getAmb() const{
    return ambulanza;
}

bool Sanitaria::getDom() const{
    return domicilio;
}

void Sanitaria::setMass(int mass){
    massimale = mass;
}

void Sanitaria::setInd(bool ind){
    individuale = ind;
}

void Sanitaria::setAmb(bool amb){
    ambulanza = amb;
}

void Sanitaria::setDom(bool dom){
    domicilio = dom;
}

//ridefinizione prezzoAnnuo
double Sanitaria::prezzoAnnuo() const{
    double base= 500;
    if(!individuale)
        base= base*2.5;
    if(!ambulanza && domicilio)
        base= base+50;
    if(ambulanza && !domicilio)
        base= base+100;
    if(ambulanza && domicilio)
        base= base+80;
    return base;
}

Sanitaria* Sanitaria::clone() const{
    return new Sanitaria(*this);
}

bool Sanitaria::isEqual(const Assicurazione &ass) const{
    if(typeid(*this) == typeid(ass)){
        const Sanitaria& s= dynamic_cast<const Sanitaria&>(ass);
        return *this == s;
    }
    else
        return false;
}









