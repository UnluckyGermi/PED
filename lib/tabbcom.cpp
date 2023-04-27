#include "tabbcom.h"
#include "tvectorcom.h"
#include "tcomplejo.h"
#include <iostream>
#include <queue>

TNodoABB::TNodoABB(TNodoABB &n)
{
    item = n.item;
    iz = n.iz;
    de = n.de;
}

TNodoABB::~TNodoABB()
{
    item.~TComplejo();
    iz.~TABBCom();
    de.~TABBCom();
}

TNodoABB & TNodoABB::operator=(TNodoABB &n)
{
    if (this != &n) {
        item = n.item;
        iz = n.iz;
        de = n.de;
    }
    return *this;
}

TABBCom::TABBCom()
{
    nodo = NULL;
}

TABBCom::TABBCom(TABBCom &abb)
{
    if (abb.nodo != NULL)
    {
        nodo = new TNodoABB();
        nodo->item = abb.nodo->item;
        nodo->iz = abb.nodo->iz;
        nodo->de = abb.nodo->de;
    }
    else
    {
        nodo = NULL;
    }
}

TABBCom::~TABBCom()
{
    if (nodo != NULL)
    {
        delete nodo;
        nodo = NULL;
    }
}

TABBCom & TABBCom::operator=(TABBCom &abb)
{
    if (this != &abb)
    {
        if (nodo != NULL)
        {
            delete nodo;
            nodo = NULL;
        }
        if (abb.nodo != NULL)
        {
            nodo = new TNodoABB();
            nodo->item = abb.nodo->item;
            nodo->iz = abb.nodo->iz;
            nodo->de = abb.nodo->de;
        }
    }
    return *this;
}

bool TABBCom::operator==(const TABBCom &abb) const
{
    if (Nodos() != abb.Nodos())
    {
        return false;
    }
    else
    {
        TVectorCom v1 = Inorden();
        TVectorCom v2 = abb.Inorden();
        for (int i = 1; i <= Nodos(); i++)
        {
            if (v1[i] != v2[i])
            {
                return false;
            }
        }
    }
    return true;
}

bool TABBCom::EsVacio() const
{
    return nodo == NULL;
}

bool TABBCom::Insertar(const TComplejo &c)
{
    if (EsVacio())
    {
        nodo = new TNodoABB();
        nodo->item = c;
        return true;
    }

    if (c < nodo->item)
    {
        return nodo->iz.Insertar(c);
    }
    if (c > nodo->item)
    {
        return nodo->de.Insertar(c);
    }
    
    return false;

}

TComplejo TABBCom::BuscarMinimo() const
{
    if (EsVacio())
    {
        return TComplejo();
    }
    else if (nodo->de.EsVacio())
    {
        return nodo->item;
    }
    else
    {
        return nodo->de.BuscarMinimo();
    }
}

bool TABBCom::Borrar(const TComplejo &c)
{
    if (EsVacio())
    {
        return false;
    }
    if (c < nodo->item)
    {
        return nodo->iz.Borrar(c);
    }
    if (c > nodo->item)
    {
        return nodo->de.Borrar(c);
    }

    TNodoABB *nodoAux = nodo;

    // Caso 1: el nodo a borrar es una hoja
    if (nodoAux->iz.EsVacio() && nodoAux->de.EsVacio())
    {
        delete nodoAux;
        nodo = NULL;
        return true;
    }
    // Caso 2: el nodo a borrar tiene un solo hijo
    if (nodoAux->iz.EsVacio())
    {
        nodo = nodoAux->de.nodo;
        nodoAux->de.nodo = NULL;
        delete nodoAux;
        return true;
    }
    if (nodoAux->de.EsVacio())
    {
        nodo = nodoAux->iz.nodo;
        nodoAux->iz.nodo = NULL;
        delete nodoAux;
        return true;
    }

    // Caso 3: el nodo a borrar tiene dos hijos
    TComplejo minimo = nodoAux->iz.BuscarMinimo();
    nodoAux->item = minimo;
    return nodoAux->iz.Borrar(minimo);
}

bool TABBCom::Buscar(const TComplejo &c) const
{
    if (EsVacio())
    {
        return false;
    }
    else if (c == nodo->item)
    {
        return true;
    }
    else if (c < nodo->item)
    {
        return nodo->iz.Buscar(c);
    }
    else // c > nodo->item
    {
        return nodo->de.Buscar(c);
    }
}

TComplejo TABBCom::Raiz() const
{
    if (nodo == NULL)
    {
        return TComplejo();
    }
    else
    {
        return nodo->item;
    }
}

int TABBCom::Altura() const
{
    if (EsVacio())
    {
        return 0;
    }
    else
    {
        int izquierda = nodo->iz.Altura();
        int derecha = nodo->de.Altura();
        return 1 + (izquierda > derecha ? izquierda : derecha);
    }
}

int TABBCom::Nodos() const
{
    if (EsVacio()) {
        return 0;
    }
    else {
        return 1 + nodo->iz.Nodos() + nodo->de.Nodos();
    }
}

int TABBCom::NodosHoja() const
{
    if (EsVacio()) {
        return 0;
    }
    if (nodo->iz.EsVacio() && nodo->de.EsVacio()) {
        return 1;
    }
    return nodo->iz.NodosHoja() + nodo->de.NodosHoja();
}

void TABBCom::InordenAux(TVectorCom &v, int &p) const
{
    if (!EsVacio()) {
        nodo->iz.InordenAux(v, p);
        v[p++] = nodo->item;
        nodo->de.InordenAux(v, p);
    }
}

void TABBCom::PreordenAux(TVectorCom &v, int &pos) const
{
    if (!EsVacio())
    {
        v[pos] = Raiz();
        pos++;
        nodo->iz.PreordenAux(v, pos);
        nodo->de.PreordenAux(v, pos);
    }
}

void TABBCom::PostordenAux(TVectorCom &vec, int &pos) const
{
    if (nodo != NULL)
    {
        nodo->iz.PostordenAux(vec, pos);
        nodo->de.PostordenAux(vec, pos);
        vec[pos] = nodo->item;
        pos++;
    }
}



TVectorCom TABBCom::Inorden() const {
    TVectorCom v(Nodos());
    int pos = 1;
    InordenAux(v, pos);
    return v;
}

TVectorCom TABBCom::Preorden() const {
    TVectorCom vec(Nodos());
    int pos = 1;
    PreordenAux(vec, pos);
    return vec;
}

TVectorCom TABBCom::Postorden() const {
    TVectorCom vec(Nodos());
    int pos = 1;
    PostordenAux(vec, pos);
    return vec;
}

TVectorCom TABBCom::Niveles() const
{
    TVectorCom v(Nodos());
    int pos = 1;
    
    if (EsVacio()) {
        return v;
    }
    
    queue<TNodoABB*> q;
    q.push(nodo);

    while (!q.empty()) {
        TNodoABB* n = q.front();
        q.pop();

        v[pos] = n->item;
        pos++;

        if (!n->iz.EsVacio()) {
            q.push(n->iz.nodo);
        }
        if (!n->de.EsVacio()) {
            q.push(n->de.nodo);
        }
    }

    return v;
}


ostream& operator<<(ostream& os, const TABBCom& arbol) {
    os << arbol.Niveles();
    return os;
}





