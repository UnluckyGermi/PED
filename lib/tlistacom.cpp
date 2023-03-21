#include "tlistacom.h"

TListaCom::TListaCom()
{
    primero = NULL;
    ultimo = NULL;
}

TListaCom::TListaCom(const TListaCom &l)
{
    TListaNodo *aux = l.primero;
    primero = NULL;
    ultimo = NULL;
    while (aux != NULL)
    {
        InsertarD(aux->e);
        aux = aux->siguiente;
    }
}

TListaCom::~TListaCom()
{
    TListaNodo *aux = primero;
    while (aux != NULL)
    {
        primero = primero->siguiente;
        delete aux;
        aux = primero;
    }
    primero = NULL;
    ultimo = NULL;
}

TListaCom & TListaCom::operator=(const TListaCom &l)
{
    if (this != &l)
    {
        TListaNodo *aux = primero;
        while (aux != NULL)
        {
            primero = primero->siguiente;
            delete aux;
            aux = primero;
        }
        primero = NULL;
        ultimo = NULL;
        aux = l.primero;
        while (aux != NULL)
        {
            InsertarD(aux->e);
            aux = aux->siguiente;
        }
    }
    return *this;
}

bool TListaCom::operator==(const TListaCom &l) const
{
    TListaNodo *aux1 = primero;
    TListaNodo *aux2 = l.primero;
    while (aux1 != NULL && aux2 != NULL)
    {
        if (aux1->e != aux2->e)
        {
            return false;
        }
        aux1 = aux1->siguiente;
        aux2 = aux2->siguiente;
    }
    return aux1 == aux2;
}

bool TListaCom::operator!=(const TListaCom &l) const
{
    return !(*this == l);
}


TListaCom TListaCom::operator+(const TListaCom &l) const
{
    TListaCom aux(*this);
    TListaNodo *aux2 = l.primero;
    while (aux2 != NULL)
    {
        aux.InsertarD(aux2->e);
        aux2 = aux2->siguiente;
    }
    return aux;
}

TListaCom TListaCom::operator-(const TListaCom &l) const
{
    TListaCom aux(*this);
    TListaNodo *aux2 = l.primero;
    while (aux2 != NULL)
    {
        aux.Borrar(aux2->e);
        aux2 = aux2->siguiente;
    }
    return aux;
}

bool TListaCom::EsVacia() const
{
    return primero == NULL;
}

bool TListaCom::InsCabeza(const TComplejo &c)
{
    TListaNodo *aux = new TListaNodo;
    if (aux == NULL)
    {
        return false;
    }
    aux->e = c;
    aux->siguiente = primero;
    aux->anterior = NULL;
    if (primero != NULL)
    {
        primero->anterior = aux;
    }
    primero = aux;
    if (ultimo == NULL)
    {
        ultimo = aux;
    }
    return true;
}

bool TListaCom::InsertarI(const TComplejo &c)
{
    TListaNodo *aux = new TListaNodo;
    if (aux == NULL)
    {
        return false;
    }
    aux->e = c;
    aux->siguiente = primero;
    aux->anterior = NULL;
    if (primero != NULL)
    {
        primero->anterior = aux;
    }
    primero = aux;
    if (ultimo == NULL)
    {
        ultimo = aux;
    }
    return true;
}

bool TListaCom::InsertarD(const TComplejo &c)
{
    TListaNodo *aux = new TListaNodo;
    if (aux == NULL)
    {
        return false;
    }
    aux->e = c;
    aux->siguiente = NULL;
    aux->anterior = ultimo;
    if (ultimo != NULL)
    {
        ultimo->siguiente = aux;
    }
    ultimo = aux;
    if (primero == NULL)
    {
        primero = aux;
    }
    return true;
}

bool TListaCom::Borrar(const TComplejo &c)
{
    TListaNodo *aux = primero;
    while (aux != NULL && aux->e != c)
    {
        aux = aux->siguiente;
    }
    if (aux == NULL)
    {
        return false;
    }
    if (aux->anterior != NULL)
    {
        aux->anterior->siguiente = aux->siguiente;
    }
    else
    {
        primero = aux->siguiente;
    }
    if (aux->siguiente != NULL)
    {
        aux->siguiente->anterior = aux->anterior;
    }
    else
    {
        ultimo = aux->anterior;
    }
    delete aux;
    return true;
}

bool TListaCom::BorrarTodos(const TComplejo &c)
{
    TListaNodo *aux = primero;
    while (aux != NULL)
    {
        if (aux->e == c)
        {
            if (aux->anterior != NULL)
            {
                aux->anterior->siguiente = aux->siguiente;
            }
            else
            {
                primero = aux->siguiente;
            }
            if (aux->siguiente != NULL)
            {
                aux->siguiente->anterior = aux->anterior;
            }
            else
            {
                ultimo = aux->anterior;
            }
            TListaNodo *aux2 = aux;
            aux = aux->siguiente;
            delete aux2;
        }
        else
        {
            aux = aux->siguiente;
        }
    }
    return true;
}

bool TListaCom::Borrar(const TListaPos &p)
{
    TListaNodo *aux = p.pos;
    if (aux == NULL)
    {
        return false;
    }
    if (aux->anterior != NULL)
    {
        aux->anterior->siguiente = aux->siguiente;
    }
    else
    {
        primero = aux->siguiente;
    }
    if (aux->siguiente != NULL)
    {
        aux->siguiente->anterior = aux->anterior;
    }
    else
    {
        ultimo = aux->anterior;
    }
    delete aux;
    return true;
}

TComplejo TListaCom::Obtener(const TListaPos &p) const
{
    if (p.pos == NULL)
    {
        return TComplejo();
    }
    return p.pos->e;
}

bool TListaCom::Buscar(const TComplejo &c) const
{
    TListaNodo *aux = primero;
    while (aux != NULL && aux->e != c)
    {
        aux = aux->siguiente;
    }
    return aux != NULL;
}

int TListaCom::Longitud() const
{
    int cont = 0;
    TListaNodo *aux = primero;
    while (aux != NULL)
    {
        cont++;
        aux = aux->siguiente;
    }
    return cont;
}

TListaPos TListaCom::Primera() const
{
    // Return the first position of the list
    return TListaPos(primero);
}

TListaPos TListaCom::Ultima() const
{
    return TListaPos(ultimo);
}



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



