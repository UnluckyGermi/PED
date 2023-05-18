#ifndef TAVLCOM_H
#define TAVLCOM_H

#include "tcomplejo.h"
#include "tvectorcom.h"

class TNodoAVL;

class TAVLCom
{
public:
    TAVLCom();
    TAVLCom(const TAVLCom&);
    ~TAVLCom();
    TAVLCom& operator=(const TAVLCom&);

    bool operator==(const TAVLCom&) const;
    bool operator!=(const TAVLCom&) const;
    bool EsVacio() const;
    bool Insertar(const TComplejo&);
    bool Buscar(const TComplejo&);
    bool Borrar(const TComplejo&);
    TComplejo Raiz() const;
    int Altura() const;
    int Nodos() const;
    int NodosHoja() const;
    TVectorCom Inorden() const;
    TVectorCom Preorden() const;
    TVectorCom Postorden() const;

    friend ostream& operator<<(ostream&, const TAVLCom&);

private:
    TNodoAVL* raiz;
    void Copiar(const TAVLCom&);
    void Equilibrar();
    TComplejo MayorIzquierda(const TAVLCom&) const;
    void InordenAux(TVectorCom&, int&) const;
    void PreordenAux(TVectorCom&, int&) const;
    void PostordenAux(TVectorCom&, int&) const;
    void RD();
    void RI();
};

class TNodoAVL
{
private:
    TComplejo item;
    TAVLCom iz, de;
    int fe;

public:
    TNodoAVL();
    TNodoAVL(const TNodoAVL&);
    ~TNodoAVL();
    TNodoAVL& operator=(const TNodoAVL&);

private:
    void Copiar(const TNodoAVL&);
    bool EsHoja() const;

    friend class TAVLCom;
};



#endif
