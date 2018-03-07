#include "staticcont.h"
#include "QDebug"
Container<SmartP> StaticCont::database;

Container<SmartP>& StaticCont::getDb() {
    return database;
}

//ritorna l'assicurazione di indice riga
SmartP& StaticCont::get_Ass(int riga) {
    return database[riga];
}

//ritorna l'indice in cui è presente lo SmartP s
int StaticCont::getRig(SmartP& s){
    int indx=0;
    for(int i=0; i<StaticCont::getDb().size(); ++i){
        if(StaticCont::get_Ass(i) == s)
            indx= i;
    }
    return indx;
}

int StaticCont::getIndC(int ind, int dim){
    int indC=0;
    while(indC<dim){
        for(int i=0; i<StaticCont::getDb().size(); ++i){
            SmartP& smartI= StaticCont::get_Ass(i);
            Casa* row= dynamic_cast<Casa*>(&(*smartI));
            if(row){
                if(ind == i)
                    return indC;
                else
                    ++indC;
            }
        }
    }
}

int StaticCont::getIndR(int ind, int dim){
    int indC=0;
    while(indC<dim){
        for(int i=0; i<StaticCont::getDb().size(); ++i){
            SmartP& smartI= StaticCont::get_Ass(i);
            RCAuto* row= dynamic_cast<RCAuto*>(&(*smartI));
            if(row){
                if(ind == i)
                    return indC;
                else
                    ++indC;
            }
        }
    }
}

int StaticCont::getIndS(int ind, int dim){
    int indC=0;
    while(indC<dim){
        for(int i=0; i<StaticCont::getDb().size(); ++i){
            SmartP& smartI= StaticCont::get_Ass(i);
            Sanitaria* row= dynamic_cast<Sanitaria*>(&(*smartI));
            if(row){
                if(ind == i)
                    return indC;
                else
                    ++indC;
            }
        }
    }
}

//restituisce il numero di oggetti di tipo Casa
int StaticCont::countC(){
    int count=0;
    for(int i=0; i<StaticCont::getDb().size(); ++i){
        SmartP& smartI= StaticCont::get_Ass(i);
        Casa* row= dynamic_cast<Casa*>(&(*smartI));
        if(row)
            ++count;
    }
    return count;
}

//restituisce il numero di oggetti di tipo RCAuto
int StaticCont::countR(){
    int count=0;
    for(int i=0; i<StaticCont::getDb().size(); ++i){
        SmartP& smartI= StaticCont::get_Ass(i);
        RCAuto* row= dynamic_cast<RCAuto*>(&(*smartI));
        if(row)
            ++count;
    }
    return count;
}

//restituisce il numero di oggetti di tipo Sanitaria
int StaticCont::countS(){
    int count=0;
    for(int i=0; i<StaticCont::getDb().size(); ++i){
        SmartP& smartI= StaticCont::get_Ass(i);
        Sanitaria* row= dynamic_cast<Sanitaria*>(&(*smartI));
        if(row)
            ++count;
    }
    return count;
}

//per ritornare l'indice reale nel contenitore dell'elemento k-esimo di tipo Casa
int StaticCont::indexC(int k){
    int dimC= StaticCont::getDb().size();
    int* indC= new int[dimC];
    int j=0;
    for(int i=0; i<StaticCont::getDb().size(); ++i){
        SmartP& smartI= StaticCont::get_Ass(i);
        Casa* row= dynamic_cast<Casa*>(&(*smartI));
        if(row){
            indC[j]= i;
            ++j;
        }
    }
    return indC[k];
}

//per ritornare l'indice reale nel contenitore dell'elemento k-esimo di tipo RCAuto
int StaticCont::indexR(int k){
    int dimR= StaticCont::getDb().size();
    int* indR= new int[dimR];
    int j=0;
    for(int i=0; i<StaticCont::getDb().size(); ++i){
        SmartP& smartI= StaticCont::get_Ass(i);
        RCAuto* row= dynamic_cast<RCAuto*>(&(*smartI));
        if(row){
            indR[j]= i;
            ++j;
        }
    }
    return indR[k];
}

//per ritornare l'indice reale nel contenitore dell'elemento k-esimo di tipo Sanitaria
int StaticCont::indexS(int k){
    int dimS= StaticCont::getDb().size();
    int* indS= new int[dimS];
    int j=0;
    for(int i=0; i<StaticCont::getDb().size(); ++i){
        SmartP& smartI= StaticCont::get_Ass(i);
        Sanitaria* row= dynamic_cast<Sanitaria*>(&(*smartI));
        if(row){
            indS[j]= i;
            ++j;
        }
    }
    return indS[k];
}











