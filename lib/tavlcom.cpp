#include "tavlcom.h"

TNodoAVL::TNodoAVL()
{
    fe = 0;
    iz = NULL;
    de = NULL;
}

TNodoAVL::TNodoAVL(const TNodoAVL &n)
{
    item = n.item;
    fe = n.fe;
    if (n.iz != NULL)
    {
        iz = new TNodoAVL(*n.iz);
    }
    else
    {
        iz = NULL;
    }
    if (n.de != NULL)
    {
        de = new TNodoAVL(*n.de);
    }
    else
    {
        de = NULL;
    }
}

TNodoAVL::~TNodoAVL()
{
    item.~TComplejo();
    fe = 0;
    if (iz != NULL)
    {
        delete iz;
        iz = NULL;
    }
    if (de != NULL)
    {
        delete de;
        de = NULL;
    }
}

TNodoAVL & TNodoAVL::operator=(const TNodoAVL &n)
{
    if (this != &n)
    {
        item = n.item;
        fe = n.fe;
        if (iz != NULL)
        {
            delete iz;
            iz = NULL;
        }
        if (de != NULL)
        {
            delete de;
            de = NULL;
        }
        if (n.iz != NULL)
        {
            iz = new TNodoAVL(*n.iz);
        }
        if (n.de != NULL)
        {
            de = new TNodoAVL(*n.de);
        }
    }
    return *this;
}

TAVLCom::TAVLCom()
{
    raiz = NULL;
}

TAVLCom::TAVLCom(const TAVLCom &a)
{
    if (a.raiz != NULL)
    {
        raiz = new TNodoAVL(*a.raiz);
    }
    else
    {
        raiz = NULL;
    }
}

TAVLCom::~TAVLCom()
{
    if (raiz != NULL)
    {
        delete raiz;
        raiz = NULL;
    }
}

TAVLCom & TAVLCom::operator=(const TAVLCom &a)
{
    if (this != &a)
    {
        (*this).~TAVLCom();
        if (a.raiz != NULL)
        {
            raiz = new TNodoAVL(*a.raiz);
        }
        else
        {
            raiz = NULL;
        }
    }
    return *this;
}

// Operador de igualdad (==) para comparar dos objetos TAVLCom
bool TAVLCom::operator==(const TAVLCom &arbol) const
{
    return SonIguales(raiz, arbol.raiz);
}

// Operador de desigualdad (!=) para comparar dos objetos TAVLCom
bool TAVLCom::operator!=(const TAVLCom &arbol) const
{
    return !(*this == arbol);
}

// Función privada para verificar si dos árboles son iguales
bool TAVLCom::SonIguales(const TNodoAVL *nodo1, const TNodoAVL *nodo2) const
{
    if (nodo1 == NULL && nodo2 == NULL)
        return true;

    if (nodo1 != NULL && nodo2 != NULL)
    {
        return (nodo1->item == nodo2->item) &&
               SonIguales(nodo1->iz, nodo2->iz) &&
               SonIguales(nodo1->de, nodo2->de);
    }

    return false;
}


bool TAVLCom::EsVacio() const
{
    return (raiz == NULL);
}

int TAVLCom::Altura() const
{
    return AlturaNodo(raiz);
}


void TAVLCom::RotacionII(TNodoAVL* &nodo)
{
    TNodoAVL* nodoAux = nodo->de;
    nodo->de = nodoAux->iz;
    nodoAux->iz = nodo;
    nodo = nodoAux;

    ActualizarAlturas(nodo->iz);
    ActualizarAlturas(nodo);
}

void TAVLCom::RotacionDD(TNodoAVL* &nodo)
{
    TNodoAVL* nodoAux = nodo->iz;
    nodo->iz = nodoAux->de;
    nodoAux->de = nodo;
    nodo = nodoAux;

    ActualizarAlturas(nodo->de);
    ActualizarAlturas(nodo);
}

void TAVLCom::RotacionID(TNodoAVL* &nodo)
{
    TNodoAVL* nodoAux = nodo->iz;
    TNodoAVL* nodoAux2 = nodoAux->de;
    nodo->iz = nodoAux2->de;
    nodoAux->de = nodoAux2->iz;
    nodoAux2->iz = nodoAux;
    nodoAux2->de = nodo;
    nodo = nodoAux2;

    ActualizarAlturas(nodo->de);
    ActualizarAlturas(nodo->iz);
    ActualizarAlturas(nodo);
}

void TAVLCom::RotacionDI(TNodoAVL* &nodo)
{
    TNodoAVL* nodoAux = nodo->de;
    TNodoAVL* nodoAux2 = nodoAux->iz;
    nodo->de = nodoAux2->iz;
    nodoAux->iz = nodoAux2->de;
    nodoAux2->de = nodoAux;
    nodoAux2->iz = nodo;
    nodo = nodoAux2;

    ActualizarAlturas(nodo->de);
    ActualizarAlturas(nodo->iz);
    ActualizarAlturas(nodo);
}

void TAVLCom::ActualizarAlturas(TNodoAVL* nodo)
{
    if (nodo == nullptr)
        return;

    int alturaIzquierda = AlturaNodo(nodo->iz);
    int alturaDerecha = AlturaNodo(nodo->de);

    nodo->fe = alturaDerecha - alturaIzquierda;
}

int TAVLCom::AlturaNodo(TNodoAVL* nodo) const
{
    if (nodo == nullptr)
        return 0;

    int alturaIzquierda = AlturaNodo(nodo->iz);
    int alturaDerecha = AlturaNodo(nodo->de);

    return 1 + std::max(alturaIzquierda, alturaDerecha);
}


bool TAVLCom::Insertar(const TComplejo& c)
{
    bool crece;
    return InsertarAux(raiz, c, crece);
}

bool TAVLCom::InsertarAux(TNodoAVL*& nodo, const TComplejo& c, bool& crece)
{
    if (nodo == nullptr)
    {
        nodo = new TNodoAVL(c);
        crece = true;
        return true;
    }
    else if (c == nodo->item)
    {
        crece = false;
        return false;
    }
    else if (c.Mod() < nodo->item.Mod())
    {
        bool insertado = InsertarAux(nodo->iz, c, crece);
        if (crece)
        {
            nodo->fe--;
            if (nodo->fe == 0)
                crece = false;
            else if (nodo->fe == -2)
                EquilibrarIzquierda(nodo);
        }
        return insertado;
    }
    else
    {
        bool insertado = InsertarAux(nodo->de, c, crece);
        if (crece)
        {
            nodo->fe++;
            if (nodo->fe == 0)
                crece = false;
            else if (nodo->fe == 2)
                EquilibrarDerecha(nodo);
        }
        return insertado;
    }
}



bool TAVLCom::BuscarNodo(TNodoAVL *nodo, const TComplejo &complejo) const
{
    if (nodo == NULL)
        return false;
    
    if (complejo == nodo->item)
        return true;
    else if (complejo < nodo->item)
        return BuscarNodo(nodo->iz, complejo);
    else
        return BuscarNodo(nodo->de, complejo);
}

bool TAVLCom::Buscar(const TComplejo &complejo) const
{
    return BuscarNodo(raiz, complejo);
}

void TAVLCom::Equilibrar(TNodoAVL* &nodo)
{
    if (nodo == nullptr)
        return;

    // Actualizar el factor de equilibrio del nodo
    nodo->fe = Altura(nodo->de) - Altura(nodo->iz);

    // Caso de desequilibrio hacia la izquierda
    if (nodo->fe < -1)
    {
        if (nodo->iz->fe <= 0)
        {
            // Desequilibrio simple izquierda-izquierda
            RotacionDD(nodo);
        }
        else
        {
            // Desequilibrio doble izquierda-derecha
            RotacionDI(nodo);
        }
    }
    // Caso de desequilibrio hacia la derecha
    else if (nodo->fe > 1)
    {
        if (nodo->de->fe >= 0)
        {
            // Desequilibrio simple derecha-derecha
            RotacionII(nodo);
        }
        else
        {
            // Desequilibrio doble derecha-izquierda
            RotacionID(nodo);
        }
    }
}

bool TAVLCom::Borrar(const TComplejo& c)
{
    if (raiz == nullptr)
        return false;

    bool borrado = false;
    raiz = BorrarAux(raiz, c, borrado);
    return borrado;
}

TNodoAVL* TAVLCom::BorrarAux(TNodoAVL* nodo, const TComplejo& c, bool& borrado)
{
    if (nodo == nullptr)
        return nullptr;

    if (c == nodo->item)
    {
        TNodoAVL* izq = nodo->iz;
        TNodoAVL* der = nodo->de;

        delete nodo;
        borrado = true;

        if (der == nullptr)
            return izq;

        TNodoAVL* min = nullptr;
        TNodoAVL* sig = der;
        while (sig->iz != nullptr)
        {
            min = sig;
            sig = sig->iz;
        }

        sig->iz = izq;
        if (min != nullptr)
            min->iz = sig->de;
        sig->de = der;

        ActualizarAlturas(sig);
        return Equilibrar(sig);
    }
    else if (c.Mod() < nodo->item.Mod())
    {
        nodo->iz = BorrarAux(nodo->iz, c, borrado);
    }
    else
    {
        nodo->de = BorrarAux(nodo->de, c, borrado);
    }

    ActualizarAlturas(nodo);
    return Equilibrar(nodo);
}


TNodoAVL *TAVLCom::BuscarMenorDeLosMayores(TNodoAVL *nodo) const
{
    if (nodo->iz != NULL)
        return BuscarMenorDeLosMayores(nodo->iz);
    return nodo;
}




TComplejo TAVLCom::Raiz() const
{
    TComplejo c;
    if (raiz != NULL)
    {
        c = raiz->item;
    }
    return c;
}

// Método público para obtener el número de nodos en el árbol AVL
int TAVLCom::Nodos() const
{
    return ContarNodos(raiz);
}

// Método privado para contar el número de nodos en el árbol AVL
int TAVLCom::ContarNodos(TNodoAVL *nodo) const
{
    if (nodo == NULL)
        return 0;

    int nodosIzq = ContarNodos(nodo->iz);
    int nodosDer = ContarNodos(nodo->de);

    return nodosIzq + nodosDer + 1;
}

// Método público para obtener el número de nodos hoja en el árbol AVL
int TAVLCom::NodosHoja() const
{
    return ContarNodosHoja(raiz);
}

// Método privado para contar el número de nodos hoja en el árbol AVL
int TAVLCom::ContarNodosHoja(TNodoAVL *nodo) const
{
    if (nodo == NULL)
        return 0;

    if (nodo->iz == NULL && nodo->de == NULL)
        return 1;

    int nodosHojaIzq = ContarNodosHoja(nodo->iz);
    int nodosHojaDer = ContarNodosHoja(nodo->de);

    return nodosHojaIzq + nodosHojaDer;
}


void TAVLCom::InordenAux(TNodoAVL *nodo, TVectorCom &vector, int &posicion) const
{
    if (nodo != NULL)
    {
        InordenAux(nodo->iz, vector, posicion);
        vector[posicion] = nodo->item;
        posicion++;
        InordenAux(nodo->de, vector, posicion);
    }
}

TVectorCom TAVLCom::Inorden() const
{
    int posicion = 1;
    TVectorCom vector(Nodos());

    InordenAux(raiz, vector, posicion);

    return vector;
}

void TAVLCom::PreordenAux(TNodoAVL *nodo, TVectorCom &vector, int &posicion) const
{
    if (nodo != NULL)
    {
        vector[posicion] = nodo->item;
        posicion++;
        PreordenAux(nodo->iz, vector, posicion);
        PreordenAux(nodo->de, vector, posicion);
    }
}

TVectorCom TAVLCom::Preorden() const
{
    int posicion = 1;
    TVectorCom vector(Nodos());

    PreordenAux(raiz, vector, posicion);

    return vector;
}

void TAVLCom::PostordenAux(TNodoAVL *nodo, TVectorCom &vector, int &posicion) const
{
    if (nodo != NULL)
    {
        PostordenAux(nodo->iz, vector, posicion);
        PostordenAux(nodo->de, vector, posicion);
        vector[posicion] = nodo->item;
        posicion++;
    }
}

TVectorCom TAVLCom::Postorden() const
{
    int posicion = 1;
    TVectorCom vector(Nodos());

    PostordenAux(raiz, vector, posicion);

    return vector;
}

ostream &operator<<(ostream &salida, const TAVLCom &arbol)
{
    TVectorCom vector = arbol.Inorden();
    salida << vector;
    return salida;
}
