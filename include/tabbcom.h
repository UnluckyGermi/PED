#ifndef TABBCOM_H
#define TABBCOM_H

#include "tcomplejo.h"
#include "tvectorcom.h"

class TNodoABB;

class TABBCom {
private:
    TNodoABB *nodo;
    void InordenAux(TVectorCom &, int &) const;
    void PreordenAux(TVectorCom &, int &) const;
    void PostordenAux(TVectorCom &, int &) const;
    TComplejo BuscarMinimo() const;

public:
    TABBCom();
    TABBCom(TABBCom &);
    ~TABBCom();
    TABBCom & operator=(TABBCom &);

    bool operator==(const TABBCom &) const;
    bool EsVacio() const;
    bool Insertar(const TComplejo &);
    bool Borrar(const TComplejo &);
    bool Buscar(const TComplejo &) const;
    TComplejo Raiz() const;
    int Altura() const;
    int Nodos() const;
    int NodosHoja() const;
    TVectorCom Inorden() const;
    TVectorCom Preorden() const;
    TVectorCom Postorden() const;
    TVectorCom Niveles() const;

    friend ostream & operator<<(ostream &, const TABBCom &);
};

class TNodoABB {
private:
    TComplejo item;
    TABBCom iz, de;
    

public:
    TNodoABB() : item(), iz(TABBCom()), de(TABBCom()) {}
    TNodoABB(TNodoABB &);
    ~TNodoABB();
    TNodoABB & operator=(TNodoABB &);
    
    friend class TABBCom;
};

#endif
