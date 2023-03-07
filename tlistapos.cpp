#include "tlistapos.h"

TListaPos::TListaPos()
{
    pos = NULL;
}

TListaPos::TListaPos(const TListaPos &l)
{
    pos = l.pos;
}

TListaPos::~TListaPos()
{
    pos = NULL;
}

TListaPos & TListaPos::operator=(const TListaPos &l)
{
    if (this != &l)
    {
        pos = l.pos;
    }
    return *this;
}

bool TListaPos::operator==(const TListaPos &l) const
{
    return pos == l.pos;
}

bool TListaPos::operator!=(const TListaPos &l) const
{
    return pos != l.pos;
}

TListaPos TListaPos::Anterior() const
{
    TListaPos aux;
    if (pos != NULL)
    {
        aux.pos = pos->anterior;
    }
    return aux;
}

TListaPos TListaPos::Siguiente() const
{
    TListaPos aux;
    if (pos != NULL)
    {
        aux.pos = pos->siguiente;
    }
    return aux;
}

bool TListaPos::EsVacia() const
{
    return pos == NULL;
}

