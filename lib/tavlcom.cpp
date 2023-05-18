#include "tavlcom.h"

// Implementación de la clase TNodoAVL

TNodoAVL::TNodoAVL()
{
    fe = 0;
}

TNodoAVL::TNodoAVL(const TNodoAVL& nodo)
{
    copia(nodo);
}

TNodoAVL::~TNodoAVL()
{
    // No se requiere liberar memoria aquí ya que los nodos se liberarán en la clase TAVLCom
}

TNodoAVL& TNodoAVL::operator=(const TNodoAVL& nodo)
{
    if (this != &nodo)
    {
        copia(nodo);
    }
    return *this;
}

void TNodoAVL::copia(const TNodoAVL& nodo)
{
    item = nodo.item;
    iz = nodo.iz;
    de = nodo.de;
    fe = nodo.fe;
}

bool TNodoAVL::EsHoja() const
{
    return (iz.EsVacio() && de.EsVacio());
}

// Implementación de la clase TAVLCom

TAVLCom::TAVLCom()
{
    raiz = nullptr;
}

TAVLCom::TAVLCom(const TAVLCom& avl)
{
    copia(avl);
}

TAVLCom::~TAVLCom()
{
    delete raiz;
}

TAVLCom& TAVLCom::operator=(const TAVLCom& avl)
{
    if (this != &avl)
    {
        delete raiz;
        copia(avl);
    }
    return *this;
}

bool TAVLCom::operator==(const TAVLCom& avl) const
{
    return (Inorden() == avl.Inorden());
}

bool TAVLCom::operator!=(const TAVLCom& avl) const
{
    return !(*this == avl);
}

bool TAVLCom::EsVacio() const
{
    return (raiz == nullptr);
}

bool TAVLCom::Insertar(const TComplejo& complejo)
{
    if (EsVacio())
    {
        raiz = new TNodoAVL();
        raiz->item = complejo;
        return true;
    }
    else if (raiz->item == complejo)
    {
        return false; // No se permite elementos duplicados en el árbol
    }
    else if (EsMenor(complejo, raiz->item))
    {
        bool insercion = raiz->iz.Insertar(complejo);
        Equilibrar();
        return insercion;
    }
    else
    {
        bool insercion = raiz->de.Insertar(complejo);
        Equilibrar();
        return insercion;
    }
}

bool TAVLCom::Buscar(const TComplejo& complejo)
{
    if (EsVacio())
    {
        return false;
    }
    else if (raiz->item == complejo)
    {
        return true;
    }
    else if (EsMenor(complejo, raiz->item))
    {
        return raiz->iz.Buscar(complejo);
    }
    else
    {
        return raiz->de.Buscar(complejo);
    }
}

TComplejo TAVLCom::MayorIzquierda(const TAVLCom &tarbol) const
{

    TComplejo auxCal;

    if (!tarbol.EsVacio())
    {
        if (tarbol.raiz->de.EsVacio())
        {
            auxCal = tarbol.Raiz();
        }
        else
        {
            auxCal = MayorIzquierda(tarbol.raiz->de);
        }
    }

    return auxCal;
}

bool TAVLCom::Borrar(const TComplejo &tc)
{
    bool dev = false;
    TNodoAVL *nodoAux = new TNodoAVL();
    TComplejo auxCal;

    // Si no está en el árbol, tampoco hay que borrar
    if (!Buscar(tc))
    {
        return false;
    }

    // Si está vacío, no hay que borrar
    if (EsVacio())
    {
        return false;
    }

    if (Raiz() == tc)
    {
        if (raiz->EsHoja())
        {
            delete raiz;
            raiz = NULL;
            dev = true;
        }
        else
        {
            if (!raiz->iz.EsVacio())
            {
                auxCal = MayorIzquierda(raiz->iz);
                raiz->item = auxCal;
                dev = raiz->iz.Borrar(auxCal);
            }

            else if (!raiz->de.EsVacio())
            {
                raiz = raiz->de.raiz;
                dev = true;
            }
            else
            {
                raiz = NULL;
            }
        }
    }

    else if (EsMenor(tc, Raiz()))
    {
        dev = raiz->iz.Borrar(tc);
    }

    else
    {
        dev = raiz->de.Borrar(tc);
    }

    Equilibrar();

    return dev;
}

void TAVLCom::Equilibrar()
{
    int aux = 0;

    if (!EsVacio())
    {
        if (raiz->EsHoja())
        {
            raiz->fe = 0;
        }

        else if (!raiz->EsHoja())
        {
            if (raiz->iz.EsVacio())
            {
                aux = raiz->de.Altura();
            }

            if (raiz->de.EsVacio())
            {
                aux = 0 - raiz->iz.Altura();
            }

            if (!raiz->iz.EsVacio() && !raiz->de.EsVacio())
            {
                aux = raiz->de.Altura() - raiz->iz.Altura();
            }
        }

        if (aux == 0 || aux == -1 || aux == 1)
        {
            raiz->fe = aux;
        }
        else
        {
            if (aux == -2)
            {
                EquilibrarIzquierda();
            }
            else if (aux == 2)
            {
                EquilibrarDerecha();
            }
        }
    }
}

bool TAVLCom::EquilibrarIzquierda()
{

    if (!EsVacio())
    {
        TAVLCom J, K;
        TAVLCom *I(this);
        int E2 = 0;

        if (!EsVacio())
        {
            if (raiz->iz.raiz->fe == -1)
            {
                // Rotación II
                Mover(J, raiz->iz);
                Mover(raiz->iz, J.raiz->de);
                Mover(J.raiz->de, I);

                J.raiz->fe = J.raiz->de.Altura() - J.raiz->iz.Altura();
                J.raiz->de.raiz->fe = J.raiz->de.Altura() - J.raiz->iz.Altura();
                Mover(*this, J);
            }
            else
            {
                // Rotación ID
                Mover(J, raiz->iz);
                Mover(K, J.raiz->de);
                E2 = K.raiz->fe;
                Mover(raiz->iz, K.raiz->de);
                Mover(J.raiz->de, K.raiz->iz);
                Mover(K.raiz->iz, J);
                Mover(K.raiz->de, I);
                K.raiz->fe = 0;

                switch (E2)
                {
                case -1:
                    K.raiz->iz.raiz->fe = 0;
                    K.raiz->de.raiz->fe = 1;
                    break;

                case 1:
                    K.raiz->iz.raiz->fe = -1;
                    K.raiz->de.raiz->fe = 0;
                    break;

                case 0:
                    K.raiz->iz.raiz->fe = 0;
                    K.raiz->de.raiz->fe = 0;
                    break;
                }

                Mover(*this, K);
            }
        }
    }

    return false;
}

bool TAVLCom::EquilibrarDerecha()
{

    if (!EsVacio())
    {
        TAVLCom J, K;
        TAVLCom *I(this);
        int E2 = 0;

        if (raiz->de.raiz->fe == 1 || raiz->de.raiz->fe == 0)
        {
            // Rotación DD
            Mover(J, raiz->de);
            Mover(raiz->de, J.raiz->iz);
            Mover(J.raiz->iz, I);

            J.raiz->fe = J.raiz->de.Altura() - J.raiz->iz.Altura();
            J.raiz->iz.raiz->fe = J.raiz->iz.raiz->de.Altura() - J.raiz->iz.raiz->iz.Altura();
            Mover(*this, J);
        }
        else
        {
            // Rotación DI
            Mover(J, raiz->de);
            Mover(K, J.raiz->iz);
            E2 = K.raiz->fe;
            Mover(raiz->de, K.raiz->iz);
            Mover(J.raiz->iz, K.raiz->de);
            Mover(K.raiz->de, J);
            Mover(K.raiz->iz, I);
            K.raiz->fe = K.raiz->de.Altura() - K.raiz->iz.Altura();
            switch (E2)
            {
            case 1:
                K.raiz->de.raiz->fe = 1;
                K.raiz->iz.raiz->fe = 0;
                break;
            case -1:
                K.raiz->de.raiz->fe = 0;
                K.raiz->iz.raiz->fe = -1;
                break;
            case 0:
                K.raiz->de.raiz->fe = 0;
                K.raiz->iz.raiz->fe = 0;
                break;
            }

            Mover(*this, K);
        }
    }

    return false;
}

void TAVLCom::Mover(TAVLCom &arbolI, TAVLCom *&arbolD)
{
    arbolI.~TAVLCom();
    arbolI.raiz = arbolD->raiz;
    arbolD->raiz = NULL;
}

void TAVLCom::Mover(TAVLCom &arbolI, TAVLCom &arbolD)
{
    arbolI.~TAVLCom();
    arbolI.raiz = arbolD.raiz;
    arbolD.raiz = NULL;
}

void TAVLCom::Mover(TAVLCom *&arbolI, TAVLCom *&arbolD)
{
    arbolI->raiz = arbolD->raiz;
    arbolD->raiz = NULL;
}

void TAVLCom::Mover(TAVLCom *&arbolI, TAVLCom &arbolD)
{
    arbolI->raiz = arbolD.raiz;
}

TComplejo TAVLCom::Raiz() const
{
    if (EsVacio())
    {
        return TComplejo();
    }
    else
    {
        return raiz->item;
    }
}

int TAVLCom::Altura() const
{
    if (EsVacio())
    {
        return 0;
    }
    else
    {
        return 1 + std::max(raiz->iz.Altura(), raiz->de.Altura());
    }
}

int TAVLCom::Nodos() const
{
    if (EsVacio())
    {
        return 0;
    }
    else
    {
        return 1 + raiz->iz.Nodos() + raiz->de.Nodos();
    }
}

int TAVLCom::NodosHoja() const
{
    if (EsVacio())
    {
        return 0;
    }
    else if (raiz->EsHoja())
    {
        return 1;
    }
    else
    {
        return raiz->iz.NodosHoja() + raiz->de.NodosHoja();
    }
}

TVectorCom TAVLCom::Inorden() const
{
    int posicion = 1;
    TVectorCom v(Nodos());
    InordenAux(v, posicion);
    return v;
}

TVectorCom TAVLCom::Preorden() const
{
    int posicion = 1;
    TVectorCom v(Nodos());
    PreordenAux(v, posicion);
    return v;
}

TVectorCom TAVLCom::Postorden() const
{
    int posicion = 1;
    TVectorCom v(Nodos());
    PostordenAux(v, posicion);
    return v;
}

void TAVLCom::copia(const TAVLCom& avl)
{
    if (!avl.EsVacio())
    {
        raiz = new TNodoAVL();
        *raiz = *avl.raiz;
    }
    else
    {
        raiz = nullptr;
    }
}


bool TAVLCom::EsMenor(const TComplejo& c1, const TComplejo& c2) const
{
    if (c1.Mod() < c2.Mod())
    {
        return true;
    }
    else if (c1.Mod() > c2.Mod())
    {
        return false;
    }
    else if (c1.Re() < c2.Re())
    {
        return true;
    }
    else if (c1.Re() > c2.Re())
    {
        return false;
    }
    else
    {
        return (c1.Im() < c2.Im());
    }
}

TVectorCom TAVLCom::Niveles() const
{
    int pos = 1;
    TVectorCom v(Nodos());
    queue<TNodoAVL *> cola;
    NivelesAux(v, cola, pos);
    return v;
}

void TAVLCom::NivelesAux(TVectorCom &tv, queue<TNodoAVL *> &cola, int &pos) const
{
    if (!EsVacio())
    {
        cola.push(raiz);

        while (!cola.empty())
        {
            TNodoAVL *aux = cola.front();
            tv[pos] = aux->item;
            pos++;

            cola.pop();
            if (!aux->iz.EsVacio())
            {
                cola.push(aux->iz.raiz);
            }
            if (!aux->de.EsVacio())
            {
                cola.push(aux->de.raiz);
            }
        }
    }
}


void TAVLCom::RotacionIzquierda()
{
    TNodoAVL* nodoAux = raiz->de.raiz;
    raiz->de.raiz = nodoAux->iz.raiz;
    nodoAux->iz.raiz = raiz;
    raiz = nodoAux;
}

void TAVLCom::RotacionDerecha()
{
    TNodoAVL* nodoAux = raiz->iz.raiz;
    raiz->iz.raiz = nodoAux->de.raiz;
    nodoAux->de.raiz = raiz;
    raiz = nodoAux;
}

void TAVLCom::InordenAux(TVectorCom& v, int& posicion) const
{
    if (!EsVacio())
    {
        raiz->iz.InordenAux(v, posicion);
        v[posicion] = raiz->item;
        posicion++;
        raiz->de.InordenAux(v, posicion);
    }
}

void TAVLCom::PreordenAux(TVectorCom& v, int& posicion) const
{
    if (!EsVacio())
    {
        v[posicion] = raiz->item;
        posicion++;
        raiz->iz.PreordenAux(v, posicion);
        raiz->de.PreordenAux(v, posicion);
    }
}

void TAVLCom::PostordenAux(TVectorCom& v, int& posicion) const
{
    if (!EsVacio())
    {
        raiz->iz.PostordenAux(v, posicion);
        raiz->de.PostordenAux(v, posicion);
        v[posicion] = raiz->item;
        posicion++;
    }
}

ostream& operator<<(ostream& os, const TAVLCom& avl)
{
    os << avl.Inorden();
    return os;
}
