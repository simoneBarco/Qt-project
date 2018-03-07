#include <iostream>
#include "rcauto.h"

using std::cout;
using std::endl;

RCAuto::RCAuto(QString n, QDate dSt, QDate dSc, int c,
               int e, int m, int cDm):
        Assicurazione(n, dSt, dSc), cavalliFiscali(c),
        etaCliente(e), massimale(m), classeDiMerito(cDm){}

RCAuto::RCAuto(const RCAuto & rc): Assicurazione(rc){
    cavalliFiscali = rc.cavalliFiscali;
    etaCliente = rc.etaCliente;
    massimale = rc.massimale;
    classeDiMerito = rc.classeDiMerito;
}

bool RCAuto::operator== (const RCAuto& r) const{
    return Assicurazione::operator== (r) && cavalliFiscali == r.cavalliFiscali &&
            etaCliente == r.etaCliente && massimale == r.massimale &&
            classeDiMerito == r.classeDiMerito;
}

int RCAuto::getCv() const{
    return cavalliFiscali;
}

int RCAuto::getEtaC() const{
    return etaCliente;
}

int RCAuto::getMass() const{
    return massimale;
}

int RCAuto::getClasse() const{
    return classeDiMerito;
}

//ridefinizione prezzoAnnuo()
double RCAuto::prezzoAnnuo() const {
    double sconto=0, surplus=0;
    if(etaCliente >= 18 && etaCliente < 25)
        surplus = 1000;
    else
        surplus = 500;
    if(cavalliFiscali>30)
        surplus= surplus+cavalliFiscali+1000;
    if(classeDiMerito == 1)
        sconto = 50;
    else if(classeDiMerito > 1 && classeDiMerito <= 4)
        sconto = 30;
    else if(classeDiMerito >= 5 && classeDiMerito <= 9)
        sconto = 20;
    else
        sconto = 0;
    double c1 = cavalliFiscali * massimale;
    return c1 * (c1 / etaCliente) + surplus - sconto;
}

RCAuto* RCAuto::clone() const{
    return new RCAuto(*this);
}

bool RCAuto::isEqual(const Assicurazione &ass) const{
    if(typeid(*this) == typeid(ass)){
        const RCAuto& r= dynamic_cast<const RCAuto&>(ass);
        return *this == r;
    }
    else
        return false;
}

void RCAuto::setCv(int c){
    cavalliFiscali = c;
}

void RCAuto::setEtaC(int a){
    etaCliente = a;
}

void RCAuto::setMass(int m){
    massimale = m;
}

void RCAuto::setClasse(int c){
    classeDiMerito = c;
}


