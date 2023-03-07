#include "tlistanodo.h"

TListaNodo::TListaNodo()
{
    anterior = NULL;
    siguiente = NULL;
}

TListaNodo::TListaNodo(const TListaNodo &l)
{
    e = l.e;
    anterior = l.anterior;
    siguiente = l.siguiente;
}

TListaNodo::~TListaNodo()
{
    anterior = NULL;
    siguiente = NULL;
}

TListaNodo & TListaNodo::operator=(const TListaNodo &l)
{
    if (this != &l)
    {
        e = l.e;
        anterior = l.anterior;
        siguiente = l.siguiente;
    }
    return *this;
}