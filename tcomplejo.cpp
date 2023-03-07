#include "tcomplejo.h"
#include <cmath>

TComplejo::TComplejo(double r, double i)
{
    re = r;
    im = i;
}

TComplejo::TComplejo(const TComplejo &c)
{
    re = c.re;
    im = c.im;
}

TComplejo::~TComplejo()
{
    re = 0;
    im = 0;
}

double TComplejo::Re() const
{
    return re;
}

double TComplejo::Im() const
{
    return im;
}

void TComplejo::Re(double re)
{
    this -> re = re;
}

void TComplejo::Im(double im)
{
    this -> im = im;
}

double TComplejo::Arg()
{
    double aux = atan2(im, re);
    return aux;
}

double TComplejo::Mod()
{
    double aux = sqrt(pow(re, 2) + pow(im, 2));
    return aux;
}

TComplejo TComplejo::operator+(const TComplejo &c) const
{
    TComplejo aux;

    aux.re = re + c.re;
    aux.im = im + c.im;

    return aux;
}

TComplejo TComplejo::operator-(const TComplejo &c) const
{
    TComplejo aux;

    aux.re = re - c.re;
    aux.im = im - c.im;

    return aux;
}

TComplejo TComplejo::operator*(const TComplejo &c) const
{
    TComplejo aux;

    aux.re = re * c.re - im * c.im;
    aux.im = re * c.im + im * c.re;

    return aux;
}


TComplejo TComplejo::operator=(const TComplejo &c)
{
    re = c.re;
    im = c.im;

    return *this;
}

bool TComplejo::operator==(const TComplejo &c) const
{
    return (re == c.re && im == c.im);
}

bool TComplejo::operator!=(const TComplejo &c) const
{
    return (re != c.re || im != c.im);
}

ostream & operator<<(ostream &os, const TComplejo &c)
{
    os << "(" << c.re << " " << c.im << ")";
}

TComplejo operator+(double r, const TComplejo &c)
{
    TComplejo aux = TComplejo(r) + c;
    return aux;
}

TComplejo operator-(double r, const TComplejo &c)
{
    TComplejo aux = TComplejo(r) - c;
    return aux;
}

TComplejo operator*(double r, const TComplejo &c)
{
    TComplejo aux = TComplejo(r) * c;
    return aux;
}
