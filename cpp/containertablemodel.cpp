#include "containertablemodel.h"

#include <QString>
#include <QDebug>

ContainerTableModel::ContainerTableModel(QObject* parent):
    QAbstractTableModel(parent) {}

//ritorna il numero di righe per ogni tabella
int ContainerTableModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    if(this->objectName()==QString("tabModelC"))
        return StaticCont::countC();
    if(this->objectName()==QString("tabModelR"))
        return StaticCont::countR();
    if(this->objectName()==QString("tabModelS"))
        return StaticCont::countS();
    else
        return StaticCont::getDb().size();

}

//ritorna il numero di colonne per ogni tabella
int ContainerTableModel::columnCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    if(this->objectName() == QString("tabModelRis"))
        return 5;
    else
        return 4;
}

//metodo per visualizzare i dati corretti per ogni riga
QVariant ContainerTableModel::data(const QModelIndex &index, int role) const{
    int dim = 0;
    if(this->objectName() == QString("tabModelC")){
        dim = StaticCont::countC();
    }
    if(this->objectName() == QString("tabModelR")){
        dim = StaticCont::countR();
    }
    if(this->objectName() == QString("tabModelS")){
        dim = StaticCont::countS();
    }
    if(this->objectName() == QString("tabModelRis")){
        dim = StaticCont::getDb().size();
    }

    if(!index.isValid()){
        return QVariant();
    }
    if(index.row() >= dim || index.row() < 0){
        return QVariant();
    }
    if(role == Qt::DisplayRole){
        if(this->objectName() == QString("tabModelRis")){
            int row2= index.row();
            SmartP& punt = StaticCont::get_Ass(row2);
            if(index.column() == 0)
                return punt->getNome();
            else if(index.column() == 1)
                return QString::fromStdString(punt->getDataSt().toString("dd/MM/yyyy").toStdString());
            else if(index.column() == 2)
                return QString::fromStdString(punt->getDataSc().toString("dd/MM/yyyy").toStdString());
            else if(index.column() == 3){
                if(dynamic_cast<Casa*>(&(*punt)))
                    return "Casa";
                if(dynamic_cast<RCAuto*>(&(*punt)))
                    return "RCAuto";
                if(dynamic_cast<Sanitaria*>(&(*punt)))
                    return "Sanitaria";
            }
            else if(index.column() == 4){
                if(dynamic_cast<Casa*>(&(*punt)))
                    return StaticCont::get_Ass(row2)->prezzoAnnuo();
                if(dynamic_cast<RCAuto*>(&(*punt)))
                    return StaticCont::get_Ass(row2)->prezzoAnnuo();
                if(dynamic_cast<Sanitaria*>(&(*punt)))
                    return StaticCont::get_Ass(row2)->prezzoAnnuo();
            }
        }
        else{
            int row2= 0;
            if(this->objectName() == QString("tabModelC"))
                row2= StaticCont::indexC(index.row());
            if(this->objectName() == QString("tabModelR"))
                row2= StaticCont::indexR(index.row());
            if(this->objectName() == QString("tabModelS"))
                row2= StaticCont::indexS(index.row());
            SmartP& punt = StaticCont::get_Ass(row2);
            if(index.column() == 0)
                return punt->getNome();
            else if(index.column() == 1)
                return QString::fromStdString(punt->getDataSt().toString("dd/MM/yyyy").toStdString());
            else if(index.column() == 2)
                return QString::fromStdString(punt->getDataSc().toString("dd/MM/yyyy").toStdString());
            else if(index.column() == 3){
                if(dynamic_cast<Casa*>(&(*punt)))
                    return StaticCont::get_Ass(row2)->prezzoAnnuo();
                if(dynamic_cast<RCAuto*>(&(*punt)))
                    return StaticCont::get_Ass(row2)->prezzoAnnuo();
                if(dynamic_cast<Sanitaria*>(&(*punt)))
                    return StaticCont::get_Ass(row2)->prezzoAnnuo();
            }
        }
    }
    return QVariant();
}

Qt::ItemFlags ContainerTableModel::flags(const QModelIndex &index) const{
    if(!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractTableModel::flags(index) | Qt::ItemIsSelectable;

}

//per assegnare un intestazione ad ogni colonna
QVariant ContainerTableModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            if(this->objectName() == QString("tabModelRis")){
                switch(section){
                case 0:
                    return QString("Nome");
                case 1:
                    return QString("Data Stipula");
                case 2:
                    return QString("Data Scadenza");
                case 3:
                    return QString("Tipo Assicurazione");
                case 4:
                    return QString("Prezzo Annuo");
                }
            }
            else{
                switch(section){
                case 0:
                    return QString("Nome");
                case 1:
                    return QString("Data Stipula");
                case 2:
                    return QString("Data Scadenza");
                case 3:
                    return QString("Prezzo Annuo");
                }
            }
        }
    }
    return QVariant();
}

//viene chiamato ogni volta che viene modificata una riga all'interno del container e permette l'aggiornamento dei dati
bool ContainerTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(index.isValid() && role == Qt::EditRole){
        int rig = 0;
        if(this->objectName() == QString("tabModelC"))
            rig= StaticCont::indexC(index.row());
        if(this->objectName() == QString("tabModelR"))
            rig= StaticCont::indexR(index.row());
        if(this->objectName() == QString("tabModelS"))
            rig= StaticCont::indexS(index.row());
        if(index.column() == 0){
            if(value.toString().isEmpty())
                StaticCont::get_Ass(rig)->setNome("NoName");
            else
                StaticCont::get_Ass(rig)->setNome(value.toString());
        }
        if(index.column() == 1){
            if(value.toString().isEmpty())
                StaticCont::get_Ass(rig)->setDataSt(QDate(1970,1,1));
            else
                StaticCont::get_Ass(rig)->setDataSt(value.toDate());
        }
        if(index.column() == 2){
            if(value.toString().isEmpty())
                StaticCont::get_Ass(rig)->setDataSc(QDate(1971,1,1));
            else
                StaticCont::get_Ass(rig)->setDataSc(value.toDate());
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

//per inserire una nuova voce nella tabella
bool ContainerTableModel::insertAssicurazione(Assicurazione *ass){
    beginInsertRows(QModelIndex(), 0, 0);

    Assicurazione* a(ass);
    StaticCont::getDb().add(a);

    endInsertRows();
    return true;
}

bool ContainerTableModel::insertCasa(){
    return insertAssicurazione(new Casa);
}

bool ContainerTableModel::insertRCAuto(){
    return insertAssicurazione(new RCAuto);
}

bool ContainerTableModel::insertSanit(){
    return insertAssicurazione(new Sanitaria);
}

bool ContainerTableModel::removeRows(int pos, int rig, const QModelIndex &index){//SISTEMARE
    Q_UNUSED(index);
    int pos2;
    if(this->objectName() == QString("tabModelC")){
        pos2= StaticCont::indexC(pos);
    }
    if(this->objectName() == QString("tabModelR")){
        pos2= StaticCont::indexR(pos);
    }
    if(this->objectName() == QString("tabModelS")){
        pos2= StaticCont::indexS(pos);
    }
    beginRemoveRows(QModelIndex(), pos2, pos2 + rig -1);

    for(int r = 0; r < rig; ++r){
        SmartP& a = StaticCont::get_Ass(pos2);
        StaticCont::getDb().removeOne(a);
    }
    endRemoveRows();
    emit layoutChanged();
    return true;
}

void ContainerTableModel::updateView(const QModelIndex &ind1, const QModelIndex &ind2){
    emit dataChanged(ind1, ind2);
}

















