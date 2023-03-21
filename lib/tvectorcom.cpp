#include "tvectorcom.h"

TVectorCom::TVectorCom()
{
    c = NULL;
    tamano = 0;
}

TVectorCom::TVectorCom(int tam)
{
    if (tam > 0)
    {
        c = new TComplejo[tam];
        tamano = tam;
        return;
    }

    c = NULL;
    tamano = 0;

}

TVectorCom::~TVectorCom(){
    if (c != NULL)
    {
        delete [] c;
        c = NULL;
    }

    tamano = 0;
}

TVectorCom::TVectorCom(const TVectorCom &v)
{
    c = new TComplejo[v.tamano];
    tamano = v.tamano;

    for (int i = 0; i < tamano; i++)
    {
        c[i] = v.c[i];
    }
    
}


TVectorCom& TVectorCom::operator=(const TVectorCom& v)
{
    if (this != &v)
    {
        // Liberar la memoria ocupada por el objeto actual
        delete[] c;
        tamano = 0;

        // Copiar el tamaño y crear un nuevo array de TComplejo
        tamano = v.tamano;
        c = new TComplejo[tamano];

        // Copiar los elementos de TComplejo
        for (int i = 0; i < tamano; i++)
        {
            c[i] = v.c[i];
        }
    }

    return *this;
}

bool TVectorCom::operator==(const TVectorCom &v) const
{
    if (tamano != v.tamano)
    {
        return false;
    }

    for (int i = 0; i < tamano; i++)
    {
        if (c[i] != v.c[i])
        {
            return false;
        }
    }

    return true;
}

bool TVectorCom::operator!=(const TVectorCom &v) const
{
    return !(*this == v);
}

TComplejo& TVectorCom::operator[](int pos)
{
    if (pos >= 1 && pos <= tamano)
    {
        return c[pos - 1];
    }

    return error;
}

TComplejo TVectorCom::operator[](int pos) const
{
    if (pos >= 1 && pos <= tamano)
    {
        return c[pos - 1];
    }

    return error;
}

int TVectorCom::Tamano() const
{
    return tamano;
}

int TVectorCom::Ocupadas() const
{
    int ocupadas = 0;
    for (int i = 0; i < tamano; i++)
    {   
        if (c[i].Re() != 0 || c[i].Im() != 0)
        {
            ocupadas++;
        }
    }

    return ocupadas;
}

bool TVectorCom::ExisteCom(const TComplejo &c) const
{
    for (int i = 0; i < tamano; i++)
    {
        if (this -> c[i] == c)
        {
            return true;
        }
    }

    return false;
}

void TVectorCom::MostrarComplejos(double x) const
{
    cout << "[";
    bool found = false;
    for (int i = 0; i < tamano; i++)
    {
        if (c[i].Re() >= x)
        {
            if (found)
            {
                cout << ", ";
            }
            found = true;
            cout << c[i];
            
        }
    }
    cout << "]";
}

bool TVectorCom::Redimensionar(int tam)
{
    if (tam <= 0 || tam == tamano) {
        return false;
    }

    if (tam > tamano) {
        // Crear nuevo vector con el nuevo tamaño
        TComplejo* nuevo = new TComplejo[tam];

        // Copiar los elementos del vector original al nuevo
        for (int i = 0; i < tamano; i++) {
            nuevo[i] = c[i];
        }

        // Inicializar los nuevos elementos con el constructor por defecto de TComplejo
        for (int i = tamano; i < tam; i++) {
            nuevo[i] = TComplejo();
        }

        // Liberar la memoria del vector original y actualizar el puntero y el tamaño
        delete[] c;
        c = nuevo;
        tamano = tam;

        return true;
    } else {
        // Actualizar el tamaño del vector y eliminar los TComplejo que sobran
        tamano = tam;
        return true;
    }
}



ostream &operator<<(ostream &os, const TVectorCom &tv){
    if(tv.tamano == 0 || tv.c == NULL){
        os << "[]";
    }
    else{
        os << "[";
        for(int i = 0; i < tv.tamano; i++){
            os << "(" << i + 1 << ") ";
            os << tv[i + 1];

            if(i != tv.tamano - 1){
                os << ", ";
            }
        }
        os << "]";
    }

    return os;
}





