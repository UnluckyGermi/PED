#ifndef TAVLCOM_H
#define TAVLCOM_H

#include "tcomplejo.h"
#include "tvectorcom.h"
#include <queue>

class TNodoAVL;

class TAVLCom
{
private:
    TNodoAVL* raiz;

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
    TVectorCom Niveles() const;

    friend ostream& operator<<(ostream&, const TAVLCom&);

private:
    void copia(const TAVLCom&);
    bool EsMenor(const TComplejo&, const TComplejo&) const;
    void Mover(TAVLCom&, TAVLCom&);
    void Mover(TAVLCom&, TAVLCom*&);
    void Mover(TAVLCom*&, TAVLCom&);
    void Mover(TAVLCom*&, TAVLCom*&);
    void NivelesAux(TVectorCom &, queue<TNodoAVL *> &, int &) const;
    void Equilibrar();
    bool EquilibrarIzquierda();
    bool EquilibrarDerecha();
    void RotacionIzquierda();
    void RotacionDerecha();
    TComplejo MayorIzquierda(const TAVLCom&) const;
    void InordenAux(TVectorCom&, int&) const;
    void PreordenAux(TVectorCom&, int&) const;
    void PostordenAux(TVectorCom&, int&) const;
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
    void copia(const TNodoAVL&);
    bool EsHoja() const;

    friend class TAVLCom;
};



#endif /* TAVLCOM_H_ */
