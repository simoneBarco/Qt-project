#ifndef CONTAINER_H
#define CONTAINER_H
#include <QtGlobal>
#include <QList>
template <typename K>
class Container{
    friend class Iterator;
    typedef bool(*findFunc)(const K &, const K &);
private:
    class nodo{
    public:
        K info;
        nodo* next;
        nodo();
        nodo(const K&, nodo*);
        nodo(const nodo&);
        ~nodo();
    };
    nodo* first;
    static nodo* copia(nodo*);
public:
    class C_iterator{
        friend class Container;
    private:
        nodo* punt;
    public:
        C_iterator();
        C_iterator(nodo* n);
        bool operator== (const C_iterator&) const;
        bool operator!= (const C_iterator&) const;
        K& operator*() const;
        C_iterator& operator++();
        C_iterator operator++(int);
    };
    Container();
    Container(const Container&);
    Container& operator= (const Container&);
    K& operator[](int) const;
    bool isEmpty() const;
    int size() const;

    C_iterator begin() const;
    C_iterator end() const;

    void add(const K&);
    void removeOne(const K&);
    Container<K> find(findFunc, K& k);
    QList<int> findIndex(findFunc, Container<K>& k, K& k2);
    void replace(const K&, const K&);
};
//COSTRUTTORI DI NODO
template <typename K>
Container<K>::nodo::nodo(): next(0) {}

template <typename K>
Container<K>::nodo::nodo(const K& k, nodo* n): info(k), next(n) {}

template <typename K>
Container<K>::nodo::nodo(const nodo& n): info(n.info), next(n.next) {}

template <typename K>
Container<K>::nodo::~nodo() {
    if(next != 0)
        delete next;
}
//COSTRUTTORI DI C_iterator
template <typename K>
Container<K>::C_iterator::C_iterator(): punt(0) {}

template <typename K>
Container<K>::C_iterator::C_iterator(nodo *n): punt(n) {}

template <typename K>
bool Container<K>::C_iterator::operator== (const C_iterator& i) const{
    return punt == i.punt;
}

template <typename K>
bool Container<K>::C_iterator::operator!= (const C_iterator& i) const{
    return punt != i.punt;
}

template <typename K>
K& Container<K>::C_iterator::operator* () const{
    return const_cast<K&>(punt->info);
}

template <typename K>
typename Container<K>::C_iterator& Container<K>::C_iterator::operator++() {
    if(punt)
        punt = punt->next;
    return *this;
}

template <typename K>
typename Container<K>::C_iterator Container<K>::C_iterator::operator++(int) {
    C_iterator aux = *this;
    if(punt)
        punt = punt->next;
    return aux;
}
//COSTRUTTORI DI Container
template <typename K>
Container<K>::Container(): first(0) {}

template <typename K>
Container<K>::Container(const Container<K>& c): first(copia(c.first)) {}

template <typename K>
typename Container<K>::nodo* Container<K>::copia(nodo* n){
    if(!n)
        return 0;
    else{
        return new nodo(n->info, copia(n->next));
    }
}

template <typename K>
Container<K>& Container<K>::operator= (const Container<K>& c){
    if(this != &c){
        if(first)
            delete first;
        first = copia(c.first);
    }
    return *this;
}

template <typename K>
K& Container<K>::operator[](int i) const{
    nodo* aux = first;
    while(i != 0){
        aux = aux->next;
        --i;
    }
    return aux->info;
}

template <typename K>
typename Container<K>::C_iterator Container<K>::begin() const{
    C_iterator aux;
    aux.punt = first;
    return aux;
}

template <typename K>
typename Container<K>::C_iterator Container<K>::end() const{
    C_iterator aux;
    aux.punt = 0;
    return aux;
}

template <typename K>
bool Container<K>::isEmpty() const{
    return begin() == end();
}

template <typename K>
int Container<K>::size() const{
    if(isEmpty())
        return 0;
    int cont = 0;
    for(C_iterator it= begin(); it != end(); ++it){
        cont++;
    }
    return cont;
}

template <typename K>
void Container<K>::add(const K& k){
    first = new nodo(k, first);
}

template <typename K>
void Container<K>::removeOne(const K& value){
    nodo* f = first;
    nodo* prev = 0;
    while(f && !(f->info == value)){
        prev = f;
        f = f->next;
    }
    if(f){
        if(!prev){
            first = f->next;
            f->next = 0;
            delete f;
        }
        else{
            prev->next = f->next;
            f->next = 0;
            delete f;
        }
    }
}

//Metodo per la ricerca
template <typename K>
Container<K> Container<K>::find(findFunc cCompare, K& k) {
    Container<K> ret;
    for(C_iterator it=begin(); it != end(); ++it) {
        K& k2 = *it; //k da confrontare
        if (cCompare(k, k2)) {
            ret.add(k2);
        }
    }
    return ret;
}

template <typename K>
QList<int> Container<K>::findIndex(findFunc cCompare, Container<K>& k, K& k2){
    QList<int> indxList;
    int ind=0;
    for(int i=0; i<k.size(); ++i){
        if(cCompare(k[i], k2)){
            indxList.append(i);
            ++ind;
        }
    }
    return indxList;
}

//Metodo di MODIFICA/SOSTITUZIONE di un elemento di un Container
template <typename K>
void Container<K>::replace(const K& k, const K& value) {
    nodo* n = first, *prev = 0;
    while (n && !(n->info == k)) {
        prev = n;
        n = n->next;
    }
    if (n) {
        if (prev) {
            prev->next = new nodo(value, n->next);
            n->next = 0;
            delete n;
        }
        else {
            first = new nodo(value, n->next);
            n->next = 0;
            delete n;
        }
    }
    return;
}

#endif // CONTAINER_H
