#ifndef RCAUTO_H
#define RCAUTO_H
#include "assicurazione.h"
#include <iostream>
using std::ostream;
class RCAuto: public Assicurazione{
private:
    int cavalliFiscali;
    int etaCliente;
    int massimale; //espressa in milioni di euro
    int classeDiMerito;
public:
    RCAuto(QString n="NoNameR", QDate dSt=QDate(1970, 1, 1), QDate dSc=QDate(1971, 1, 1),
            int c=1 ,int eC=20, int m=5, int cDm=14);
    RCAuto(const RCAuto &);
    virtual double prezzoAnnuo() const;
    virtual RCAuto* clone() const;
    virtual bool isEqual(const Assicurazione&) const;

    bool operator== (const RCAuto&) const;
    int getCv() const;
    int getEtaC() const;
    int getMass() const;
    int getClasse() const;
    void setCv(int);
    void setEtaC(int);
    void setMass(int);
    void setClasse(int);
};

#endif // RCAUTO_H
