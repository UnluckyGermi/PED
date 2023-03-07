#ifndef TLISTANODO_H
#define TLISTANODO_H

#include <iostream>

#include "tcomplejo.h"

class TListaNodo {
    private:
        TComplejo e;
        TListaNodo *anterior;
        TListaNodo *siguiente;
    public:
        TListaNodo();
        TListaNodo(const TListaNodo &);
        ~TListaNodo();
        TListaNodo & operator=(const TListaNodo &);
        friend class TListaPos;
        friend class TListaCom;
};

#endif