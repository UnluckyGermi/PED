#include "tvectorcom.h"

TVectorCom::TVectorCom()
{
    error = new TComplejo();
    c = NULL;
    tamano = 0;
}

TVectorCom::TVectorCom(int tam)
{
    error = new TComplejo();
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

    if (error != NULL)
    {
        delete error;
        error = NULL;
    }
}

TVectorCom::TVectorCom(const TVectorCom &v)
{
    if (v.c != NULL)
    {
        c = new TComplejo[v.tamano];
        tamano = v.tamano;
        for (int i = 0; i < tamano; i++)
        {
            c[i] = v.c[i];
        }
    }
    else
    {
        c = NULL;
        tamano = 0;
    }
}

TVectorCom& TVectorCom::operator=(const TVectorCom &v)
{
    if (this != &v)
    {
        if (c != NULL)
        {
            delete [] c;
            c = NULL;
        }

        if (v.c != NULL)
        {
            c = new TComplejo[v.tamano];
            tamano = v.tamano;
            for (int i = 0; i < tamano; i++)
            {
                c[i] = v.c[i];
            }
        }
        else
        {
            c = NULL;
            tamano = 0;
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

TComplejo& TVectorCom::operator[](int pos)
{
    if (pos >= 1 && pos <= tamano)
    {
        return c[pos - 1];
    }

    return *error;
}

TComplejo TVectorCom::operator[](int pos) const
{
    if (pos >= 1 && pos <= tamano)
    {
        return c[pos - 1];
    }

    return *error;
}

int TVectorCom::Tamano() const
{
    return tamano;
}

int TVectorCom::Ocupadas() const
{
    int ocupadas = 0;
    for (int i = 1; i <= tamano; i++)
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
    for (int i = 1; i <= tamano; i++)
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
    for (int i = 1; i <= tamano; i++)
    {
        if (c[i].Re() >= x)
        {
            if (i != 1)
            {
                cout << ", ";
            }
            cout << c[i] << endl;
        }
    }
    cout << "]" << endl;
}

bool TVectorCom::Redimensionar(int tam)
{
    if (tam <= 0 || tam == tamano) {
        return false;
    }

    TComplejo *aux = new TComplejo[tam];

    if (tam > tamano)
    {
        for (int i = 1; i <= tamano; i++)
        {
            aux[i] = c[i];
        }

        for (int i = tamano+1; i <= tam; i++)
        {
            aux[i] = TComplejo();
        }

    }
    else
    {
        for (int i = 0; i < tam; i++)
        {
            aux[i] = c[i];
        }
    }

    delete [] c;
    c = aux;
    tamano = tam;
    return true;
}

ostream& operator<<(ostream &os, const TVectorCom &v)
{
    os << "[";
    for (int i = 1; i <= v.tamano; i++)
    {
        if (i != 1)
        {
            os << ", ";
        }
        os << "(" << i << ") " << v.c[i];
    }
    os << "]";
    return os;
}





