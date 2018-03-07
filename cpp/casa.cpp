#include <iostream>
#include "casa.h"

using std::cout;
using std::endl;

Casa::Casa(QString n, QDate dSt, QDate dSc, int aC, int aR,
           double sL, QString pR, bool f, bool i, bool c):
    Assicurazione(n, dSt, dSc), annoCostruzione(aC), annoRistrutturazione(aR),
    speseLegali(sL), provinciaResidenza(pR), furto(f), incendio(i), calamita(c) {}

Casa::Casa(const Casa &ca): Assicurazione(ca){
    annoCostruzione = ca.annoCostruzione;
    annoRistrutturazione = ca.annoRistrutturazione;
    speseLegali = ca.speseLegali;
    provinciaResidenza = ca.provinciaResidenza;
    furto = ca.furto;
    incendio = ca.incendio;
    calamita = ca.calamita;
}

bool Casa::operator== (const Casa& c) const{
    return Assicurazione::operator==(c) && annoCostruzione == c.annoCostruzione
            && annoRistrutturazione == c.annoRistrutturazione &&
            speseLegali == c.speseLegali && provinciaResidenza == c.provinciaResidenza &&
            furto == c.furto && incendio == c.incendio && calamita == c.calamita;
}

int Casa::getAnnoCostr() const{
    return annoCostruzione;
}

int Casa::getAnnoRist() const{
    return annoRistrutturazione;
}

double Casa::getSpese() const{
    return speseLegali;
}

QString Casa::getProv() const{
    return provinciaResidenza;
}

bool Casa::getFurto() const{
    return furto;
}

bool Casa::getIncendio() const{
    return incendio;
}

bool Casa::getCalam() const{
    return calamita;
}

double Casa::prezzoAnnuo() const{
    double base = 400;
    bool sconto;
    if(provinciaResidenza=="PD")
        base=base+100.0;
    if(provinciaResidenza=="BL")
        base=base+110.0;
    if(provinciaResidenza=="RO")
        base=base+120.0;
    if(provinciaResidenza=="TV")
        base=base+130.0;
    if(provinciaResidenza=="VE")
        base=base+140.0;
    if(provinciaResidenza=="VR")
        base=base+150.0;
    if(provinciaResidenza=="VI")
        base=base+160.0;
    if((furto && incendio || incendio && calamita)){
        sconto= true;
    }
    else
        sconto= false;

    return base+ (sconto ? -20 : 0);
}

Casa* Casa::clone() const{
    return new Casa(*this);
}

bool Casa::isEqual(const Assicurazione &ass) const{
    if(typeid(*this) == typeid(ass)){
        const Casa& c= dynamic_cast<const Casa&>(ass);
        return *this == c;
    }
    else
        return false;
}

void Casa::setAnnoCost(int aC){
    annoCostruzione = aC;
}

void Casa::setAnnoRist(int aR){
    annoRistrutturazione = aR;
}

void Casa::setSpese(double s){
    speseLegali = s;
}

void Casa::setProv(QString p){
    provinciaResidenza = p;
}

void Casa::setFurto(bool f){
    furto = f;
}

void Casa::setIncendio(bool i){
    incendio = i;
}

void Casa::setCalam(bool c){
    calamita = c;
}



