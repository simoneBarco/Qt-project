#include "assicurazione.h"

Assicurazione::Assicurazione(QString n, QDate dSt, QDate dSc):
    nome(n), dataStipula(dSt), dataScadenza(dSc) {}

Assicurazione::Assicurazione(const Assicurazione & ass){
    nome = ass.nome;
    dataStipula = ass.dataStipula;
    dataScadenza = ass.dataScadenza;
}

bool Assicurazione::operator== (const Assicurazione& ass) const{
    return nome == ass.nome && dataStipula == ass.dataStipula && dataScadenza == ass.dataScadenza;
}

QString Assicurazione::getNome() const{
    return nome;
}

QDate Assicurazione::getDataSt() const{
    return dataStipula;
}

QDate Assicurazione::getDataSc() const{
    return dataScadenza;
}

void Assicurazione::setNome(QString n){
    nome = n;
}

void Assicurazione::setDataSt(QDate dSt){
    dataStipula = dSt;
}

void Assicurazione::setDataSc(QDate dSc){
    dataScadenza = dSc;
}
