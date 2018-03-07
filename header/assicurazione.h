#ifndef ASSICURAZIONE_H
#define ASSICURAZIONE_H
#include <QDate>
#include <QString>
#include <typeinfo>

class Assicurazione{
private:
    QString nome;
    QDate dataStipula;
    QDate dataScadenza;
public:
    Assicurazione(QString n= "NoName", QDate dSt= QDate(1970, 1, 1),
                  QDate dSc= QDate(1971, 1, 1));
    Assicurazione(const Assicurazione &);
    virtual ~Assicurazione(){}
    virtual double prezzoAnnuo() const =0;
    virtual Assicurazione* clone() const = 0;
    virtual bool isEqual(const Assicurazione&) const =0;

    bool operator== (const Assicurazione&) const;
    QString getNome() const;
    QDate getDataSt() const;
    QDate getDataSc() const;
    void setNome(QString);
    void setDataSt(QDate);
    void setDataSc(QDate);

};

#endif // ASSICURAZIONE_H
