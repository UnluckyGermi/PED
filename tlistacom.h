#ifndef TLISTACOM_H
#define TLISTACOM_H

#include <iostream>

#include "tlistanodo.h"
#include "tlistapos.h"

using namespace std;

class TListaCom {
    private:
        TListaNodo *primero;
        TListaNodo *ultimo;
    public:
        TListaCom();
        TListaCom(const TListaCom &);
        ~TListaCom();
        TListaCom & operator=(const TListaCom &);
        bool operator==(const TListaCom &) const;
        bool operator!=(const TListaCom &) const;
        TListaCom operator+(const TListaCom &) const;
        TListaCom operator-(const TListaCom &) const;
        bool EsVacia() const;
        bool InsCabeza(const TComplejo &);
        bool InsertarI(const TComplejo &);
        bool InsertarD(const TComplejo &);
        bool Borrar(const TComplejo &);
        bool BorrarTodos(const TComplejo &);
        bool Borrar(const TListaPos &);
        TComplejo Obtener(const TListaPos &) const;
        bool Buscar(const TComplejo &) const;
        int Longitud() const;
        TListaPos Primera() const;
        TListaPos Ultima() const;

        friend ostream & operator<<(ostream &, const TListaCom &);
};

#endif