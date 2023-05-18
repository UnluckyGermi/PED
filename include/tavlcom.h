#ifndef TAVLCOM_H
#define TAVLCOM_H

#include "tcomplejo.h"
#include "tvectorcom.h"

class TNodoAVL
{
    private:
        TComplejo item;
        TNodoAVL *iz, *de;
        int fe;

    public:
        TNodoAVL();
        TNodoAVL(const TNodoAVL &);
        ~TNodoAVL();
        TNodoAVL & operator=(const TNodoAVL &);

        friend class TAVLCom;
};

class TAVLCom
{
    private:
        TNodoAVL *raiz;
        void InordenAux(TNodoAVL *, TVectorCom &, int &) const;
        void PreordenAux(TNodoAVL *, TVectorCom &, int &) const;
        void PostordenAux(TNodoAVL *, TVectorCom &, int &) const;
        void RotacionII(TNodoAVL *&);
        void RotacionDD(TNodoAVL *&);
        void RotacionID(TNodoAVL *&);
        void RotacionDI(TNodoAVL *&);
        int AlturaNodo(TNodoAVL *) const;
        bool InsertarAux(TNodoAVL *&, const TComplejo &, bool &);
        bool BuscarNodo(TNodoAVL *, const TComplejo &) const;
        void BorrarAux(TNodoAVL *&, const TComplejo &, bool &);
        int ContarNodos(TNodoAVL *) const;
        int ContarNodosHoja(TNodoAVL *) const;
        bool SonIguales(const TNodoAVL *, const TNodoAVL *) const;
        TNodoAVL *BuscarMenorDeLosMayores(TNodoAVL *);
        void Equilibrar(TNodoAVL *&);
        void ActualizarAlturas(TNodoAVL *);

    public:
        TAVLCom();
        TAVLCom(const TAVLCom &);
        ~TAVLCom();
        TAVLCom & operator=(const TAVLCom &);

        bool operator==(const TAVLCom &) const;
        bool operator!=(const TAVLCom &) const;
        bool EsVacio() const;
        bool Insertar(const TComplejo &);
        bool Buscar(const TComplejo &) const;
        bool Borrar(const TComplejo &);
        int Altura() const;
        TComplejo Raiz() const;
        int Nodos() const;
        int NodosHoja() const;
        TVectorCom Inorden() const;
        TVectorCom Preorden() const;
        TVectorCom Postorden() const;

        friend ostream & operator<<(ostream &, const TAVLCom &);
};

#endif