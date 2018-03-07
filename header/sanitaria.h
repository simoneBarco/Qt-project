#ifndef SANITARIA_H
#define SANITARIA_H
#include "assicurazione.h"
#include <iostream>
using std::ostream;
class Sanitaria: public Assicurazione{
private:
    int massimale; //espresso in milioni di euro
    bool individuale; //tipologia (1=individuale 0=nucleo familiare)
    bool ambulanza; //copertura trasporto in ambulanza
    bool domicilio; //copertura assistenza domiciliare

public:
    Sanitaria(QString n="NoNameS", QDate dSt=QDate(1970, 1, 1), QDate dSc=QDate(1971, 1, 1), int m=2,
              bool i=true, bool a=true, bool dm=false);
    Sanitaria(const Sanitaria&);
    virtual double prezzoAnnuo() const;
    virtual Sanitaria* clone() const;
    virtual bool isEqual(const Assicurazione&) const;

    bool operator== (const Sanitaria&) const;
    int getMass() const;
    bool getInd() const;
    bool getAmb() const;
    bool getDom() const;

    void setMass(int);
    void setInd(bool);
    void setAmb(bool);
    void setDom(bool);
};

#endif // SANITARIA_H
