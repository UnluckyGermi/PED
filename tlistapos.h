#ifndef TLISTAPOS_H
#define TLISTAPOS_H

#include <iostream>

#include "tlistanodo.h"

using namespace std;

class TListaPos {
    private:
        TListaNodo *pos;
    public:
        TListaPos();
        TListaPos(const TListaPos &);
        ~TListaPos();
        TListaPos & operator=(const TListaPos &);
        bool operator==(const TListaPos &) const;
        bool operator!=(const TListaPos &) const;
        TListaPos Anterior() const;
        TListaPos Siguiente() const;
        bool EsVacia() const;
        friend class TListaCom;
};

#endif