#ifndef CASA_H
#define CASA_H
#include "assicurazione.h"
#include <iostream>
#include <QString>
using std::ostream;
class Casa: public Assicurazione{
private:
    int annoCostruzione;
    int annoRistrutturazione;
    double speseLegali;
    QString provinciaResidenza;
    bool furto;
    bool incendio;
    bool calamita;
public:
    Casa(QString n="NoNameC", QDate dSt=QDate(1970, 1, 1), QDate dSc=QDate(1971, 1, 1),
         int aC=1980, int aR=0, double sL=1200.0, QString pR="PD",
         bool f=false, bool i=false, bool c=false);
    Casa(const Casa &);
    virtual double prezzoAnnuo() const;
    virtual Casa* clone() const;
    virtual bool isEqual(const Assicurazione&) const;

    bool operator== (const Casa&) const;
    int getAnnoCostr() const;
    int getAnnoRist() const;
    double getSpese() const;
    QString getProv() const;
    bool getFurto() const;
    bool getIncendio() const;
    bool getCalam() const;
    void setAnnoCost(int);
    void setAnnoRist(int);
    void setSpese(double);
    void setProv(QString);
    void setFurto(bool);
    void setIncendio(bool);
    void setCalam(bool);
};

#endif // CASA_H
