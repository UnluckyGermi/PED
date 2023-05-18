#include "tavlcom.h"

TNodoAVL::TNodoAVL() {
    fe = 0;
}

TNodoAVL::TNodoAVL(const TNodoAVL& nodo) {
    Copiar(nodo);
}

TNodoAVL::~TNodoAVL() {}

TNodoAVL& TNodoAVL::operator=(const TNodoAVL& nodo) {
    if (this != &nodo) {
        Copiar(nodo);
    }
    return *this;
}

void TNodoAVL::Copiar(const TNodoAVL& nodo) {
    item = nodo.item;
    iz = nodo.iz;
    de = nodo.de;
    fe = nodo.fe;
}

bool TNodoAVL::EsHoja() const {
    return (iz.EsVacio() && de.EsVacio());
}

TAVLCom::TAVLCom() {
    raiz = nullptr;
}

TAVLCom::TAVLCom(const TAVLCom& avl) {
    Copiar(avl);
}

TAVLCom::~TAVLCom() {
    delete raiz;
}

void TAVLCom::Copiar(const TAVLCom& avl) {
    if (!avl.EsVacio()) {
        raiz = new TNodoAVL();
        raiz->item = avl.raiz->item;
        raiz->fe = avl.raiz->fe;
        raiz->iz.Copiar(avl.raiz->iz);
        raiz->de.Copiar(avl.raiz->de);
    } else {
        raiz = nullptr;
    }
}

TAVLCom& TAVLCom::operator=(const TAVLCom& avl) {
    if (this != &avl) {
        delete raiz;
        Copiar(avl);
    }
    return *this;
}

bool TAVLCom::operator==(const TAVLCom& avl) const {
    return (Inorden() == avl.Inorden());
}

bool TAVLCom::operator!=(const TAVLCom& avl) const {
    return !(*this == avl);
}

bool TAVLCom::EsVacio() const {
    return (raiz == nullptr);
}

bool TAVLCom::Insertar(const TComplejo& complejo) {
    if (EsVacio()) {
        raiz = new TNodoAVL();
        raiz->item = complejo;
        return true;
    } else if (raiz->item == complejo) {
        return false;
    } else if (complejo < raiz->item) {
        bool insercion = raiz->iz.Insertar(complejo);
        Equilibrar();
        return insercion;
    } else {
        bool insercion = raiz->de.Insertar(complejo);
        Equilibrar();
        return insercion;
    }
}

bool TAVLCom::Buscar(const TComplejo& complejo) {
    if (EsVacio()) {
        return false;
    } else if (raiz->item == complejo) {
        return true;
    } else if (complejo < raiz->item) {
        return raiz->iz.Buscar(complejo);
    } else {
        return raiz->de.Buscar(complejo);
    }
}

TComplejo TAVLCom::MayorIzquierda(const TAVLCom &tarbol) const {
    TComplejo auxCal;

    if (!tarbol.EsVacio()) {
        if (tarbol.raiz->de.EsVacio()) {
            auxCal = tarbol.Raiz();
        } else {
            auxCal = MayorIzquierda(tarbol.raiz->de);
        }
    }
    return auxCal;
}

bool TAVLCom::Borrar(const TComplejo& complejo) {
    if (EsVacio()) {
        return false;
    } else if (raiz->item == complejo) {
        if (raiz->EsHoja()) {
            delete raiz;
            raiz = nullptr;
            return true;
        } else if (raiz->iz.EsVacio()) {
            TNodoAVL* nodo = raiz;
            raiz = raiz->de.raiz;
            nodo->de.raiz = nullptr;
            delete nodo;
            return true;
        } else if (raiz->de.EsVacio()) {
            TNodoAVL* nodo = raiz;
            raiz = raiz->iz.raiz;
            nodo->iz.raiz = nullptr;
            delete nodo;
            return true;
        } else {
            TComplejo mayorIzq = MayorIzquierda(raiz->iz);
            raiz->item = mayorIzq;
            return raiz->iz.Borrar(mayorIzq);
        }
    } else if (complejo < raiz->item) {
        bool borrado = raiz->iz.Borrar(complejo);
        Equilibrar();
        return borrado;
    } else {
        bool borrado = raiz->de.Borrar(complejo);
        Equilibrar();
        return borrado;
    }
}

int TAVLCom::Nodos() const {
    if (EsVacio()) {
        return 0;
    } else {
        return 1 + raiz->iz.Nodos() + raiz->de.Nodos();
    }
}

int TAVLCom::NodosHoja() const {
    if (EsVacio()) {
        return 0;
    } else if (raiz->EsHoja()) {
        return 1;
    } else {
        return raiz->iz.NodosHoja() + raiz->de.NodosHoja();
    }
}

int TAVLCom::Altura() const {
    if (EsVacio()) {
        return 0;
    } else {
        return 1 + std::max(raiz->iz.Altura(), raiz->de.Altura());
    }
}

TComplejo TAVLCom::Raiz() const {
    if (EsVacio()) {
        return TComplejo();
    } else {
        return raiz->item;
    }
}

void TAVLCom::InordenAux(TVectorCom& v, int& pos) const {
    if (!EsVacio()) {
        raiz->iz.InordenAux(v, pos);
        v[pos++] = raiz->item;
        raiz->de.InordenAux(v, pos);
    }
}

TVectorCom TAVLCom::Inorden() const {
    int pos = 1;
    TVectorCom v(Nodos());
    InordenAux(v, pos);
    return v;
}

void TAVLCom::PreordenAux(TVectorCom& v, int& pos) const {
    if (!EsVacio()) {
        v[pos++] = raiz->item;
        raiz->iz.PreordenAux(v, pos);
        raiz->de.PreordenAux(v, pos);
    }
}

TVectorCom TAVLCom::Preorden() const {
    int pos = 1;
    TVectorCom v(Nodos());
    PreordenAux(v, pos);
    return v;
}

void TAVLCom::PostordenAux(TVectorCom& v, int& pos) const {
    if (!EsVacio()) {
        raiz->iz.PostordenAux(v, pos);
        raiz->de.PostordenAux(v, pos);
        v[pos++] = raiz->item;
    }
}

TVectorCom TAVLCom::Postorden() const {
    int pos = 1;
    TVectorCom v(Nodos());
    PostordenAux(v, pos);
    return v;
}


void TAVLCom::Equilibrar() {
    raiz->fe = raiz->de.Altura() - raiz->iz.Altura();

    if (raiz->fe == 2) {
        if (raiz->de.raiz->fe == -1) {
            raiz->de.RD();
        }
        RI();
    } else if (raiz->fe == -2) {
        if (raiz->iz.raiz->fe == 1) {
            raiz->iz.RI();
        }
        RD();
    }
}

void TAVLCom::RI() {
    TNodoAVL* nodo = raiz->de.raiz;
    raiz->de.raiz = nodo->iz.raiz;
    nodo->iz.raiz = raiz;
    raiz = nodo;

    if (raiz->iz.raiz != nullptr) {
        raiz->iz.Equilibrar();
    }
    Equilibrar();
}

void TAVLCom::RD() {
    TNodoAVL* nodo = raiz->iz.raiz;
    raiz->iz.raiz = nodo->de.raiz;
    nodo->de.raiz = raiz;
    raiz = nodo;

    if (raiz->de.raiz != nullptr) {
        raiz->de.Equilibrar();
    }
    Equilibrar();
}


ostream& operator<<(ostream& os, const TAVLCom& avl) {
    os << avl.Inorden();
    return os;
}
