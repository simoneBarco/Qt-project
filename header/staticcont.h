#ifndef STATICCONT_H
#define STATICCONT_H

#include "Container.h"
#include "smartp.h"
//#include "assicurazione.h"
#include "casa.h"
#include "rcauto.h"
#include "sanitaria.h"
class StaticCont{
private:
    static Container<SmartP> database;
public:
    StaticCont(){}
    static Container<SmartP>& getDb();
    static SmartP& get_Ass(int riga);
    static int getRig(SmartP&);
    static int getIndC(int, int);
    static int getIndR(int, int);
    static int getIndS(int, int);
    static int countC();
    static int countR();
    static int countS();
    static int indexC(int k);
    static int indexR(int k);
    static int indexS(int k);
};

#endif // STATICCONT_H
