#include "tavlcom.h"

int main ()
{
  // BORRADO  (Se recomienda haber pasado el test de inserciones)

  TAVLCom a;
  TComplejo c0(0), c1(1), c2(2), c3(3), c4(4), c5(5), c6(6), c7(7), c8(8), c9(9), c10(10), c11(11);

  cout << "- Inserción 5" << endl;
  a.Insertar(c5);
  cout << "- Inserción 3" << endl;
  a.Insertar(c3);
  cout << "- Inserción 8" << endl;
  a.Insertar(c8);
  cout << "- Inserción 2" << endl;
  a.Insertar(c2);
  cout << "- Inserción 4" << endl;
  a.Insertar(c4);
  cout << "- Inserción 7" << endl;
  a.Insertar(c7);
  cout << "- Inserción 10" << endl;
  a.Insertar(c10);
  cout << "- Inserción 1" << endl;
  a.Insertar(c1);
  cout << "- Inserción 6" << endl;
  a.Insertar(c6);
  cout << "- Inserción 9" << endl;
  a.Insertar(c9);
  cout << "- Inserción 11" << endl << endl;
  a.Insertar(c11);

  cout << "Borrado 4 :" << endl;
  a.Borrar(c4);
  cout << "+ Resultado borrado : " << a.Niveles() << endl << endl;
  cout << "Borrado 8 :" << endl;
  a.Borrar(c8);
  cout << "+ Resultado borrado : " << a.Niveles() << endl << endl;
  cout << "Borrado 6:" << endl;
  a.Borrar(c6);
  cout << "+ Resultado borrado : " << a.Niveles() << endl << endl;
  cout << "Borrado 5 :" << endl;
  a.Borrar(c5);
  cout << "+ Resultado borrado : " << a.Niveles() << endl << endl;
  cout << "Borrado 2 :" << endl;
  a.Borrar(c2);
  cout << "+ Resultado borrado : " << a.Niveles() << endl << endl;
  cout << "Borrado 1 :" << endl;
  a.Borrar(c1);
  cout << "+ Resultado borrado : " << a.Niveles() << endl << endl;
  cout << "Borrado 7 :" << endl;
  a.Borrar(c7);
  cout << "+ Resultado borrado : " << a.Niveles() << endl << endl;

  return 0;
}