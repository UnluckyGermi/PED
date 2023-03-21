#include "tlistacom.h"

TListaCom::TListaCom()
{
    primero = NULL;
    ultimo = NULL;
}

TListaCom::TListaCom(const TListaCom &l)
{
    TListaNodo *aux = l.ultimo;
    primero = NULL;
    ultimo = NULL;
    while (aux != NULL)
    {
        InsCabeza(aux->e);
        aux = aux->anterior;
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
        this -> ~TListaCom();
        TListaNodo *aux = ultimo;
        while (aux != NULL)
        {
            primero = primero->anterior;
            delete aux;
            aux = primero;
        }
        primero = NULL;
        ultimo = NULL;
        aux = l.ultimo;
        while (aux != NULL)
        {
            InsCabeza(aux->e);
            aux = aux->anterior;
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


TListaCom TListaCom::operator+(const TListaCom &l) const {
    TListaCom nuevaLista;
    TListaNodo *aux2 = ultimo;
    TListaNodo *aux3 = l.ultimo;

    while(aux3 != NULL){
        nuevaLista.InsCabeza(aux3->e);
        aux3 = aux3->anterior;
    }

    while(aux2 != NULL){
        nuevaLista.InsCabeza(aux2->e);
        aux2 = aux2->anterior;
    }

    return nuevaLista;
}

TListaCom TListaCom::operator-(const TListaCom& l) const {
    TListaCom res(*this);
    TListaPos p = res.Primera();
    while(!p.EsVacia()) {
        if(l.Buscar(res.Obtener(p))) {
            res.Borrar(p);
            p = res.Primera();
        }
        else {
            p = p.Siguiente();
        }
    }
    return res;
}


bool TListaCom::EsVacia() const
{
    return primero == NULL;
}

bool TListaCom::InsCabeza(const TComplejo &tc){
    TListaNodo *aux = new TListaNodo;
    if (aux == NULL)
    {
        return false;
    }
    aux->e = tc;
    aux->siguiente = primero;
    aux->anterior = NULL;
    if (primero != NULL)
    {
        primero->anterior = aux;
    }
    else
    {
        ultimo = aux;
    }
    primero = aux;
    return true;
}

bool TListaCom::InsertarI(const TComplejo &c, const TListaPos &p)
{
    if (p.pos == NULL)
    {
        return false;
    }
    TListaNodo *aux = new TListaNodo;
    if (aux == NULL)
    {
        return false;
    }
    aux->e = c;
    aux->siguiente = p.pos;
    aux->anterior = p.pos->anterior;
    if (p.pos->anterior != NULL)
    {
        p.pos->anterior->siguiente = aux;
    }
    else
    {
        primero = aux;
    }
    p.pos->anterior = aux;
    return true;
}

bool TListaCom::InsertarD(const TComplejo &c, const TListaPos &p)
{
    if (p.pos == NULL)
    {
        return false;
    }
    TListaNodo *aux = new TListaNodo;
    if (aux == NULL)
    {
        return false;
    }
    aux->e = c;
    aux->siguiente = p.pos->siguiente;
    aux->anterior = p.pos;
    if (p.pos->siguiente != NULL)
    {
        p.pos->siguiente->anterior = aux;
    }
    else
    {
        ultimo = aux;
    }
    p.pos->siguiente = aux;
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
    TListaPos aux;
    if (primero != NULL)
    {
        aux.pos = primero;
    }
    return aux;
}

TListaPos TListaCom::Ultima() const
{
    TListaPos aux;
    if (ultimo != NULL)
    {
        aux.pos = ultimo;
    }
    return aux;
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


ostream &operator<<(ostream &os, const TListaCom &tl){
    if(tl.Longitud() == 0){
        os << "{}";
    }
    else{
        TListaPos aux = tl.Primera();
        os << "{";
        while(aux != tl.Ultima()){
            os << tl.Obtener(aux) << " ";
            aux = aux.Siguiente();
        }
        os << tl.Obtener(aux) << "}";
    }

    return os;
}