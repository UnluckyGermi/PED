#include "tavlcom.h"


TAVLCom a;
TComplejo c5(5), c10(10), c20(20), c25(25), c30(30), c32(32), c35(35), c40(40), c42(42), c45(45), c50(50), c55(55);

void borrar();

int main ()
{
  // BORRADO CON ROTACIONES DOBLES (Se recomienda haber pasado el test de inserciones)

  cout << "- Inserción 40" << endl;
  a.Insertar(c40);
  cout << "- Inserción 30" << endl;
  a.Insertar(c30);
  cout << "- Inserción 50" << endl;
  a.Insertar(c50);
  cout << "- Inserción 20" << endl;
  a.Insertar(c20);
  cout << "- Inserción 35" << endl;
  a.Insertar(c35);
  cout << "- Inserción 45" << endl;
  a.Insertar(c45);
  cout << "- Inserción 55" << endl;
  a.Insertar(c55);
  cout << "- Inserción 10" << endl;
  a.Insertar(c10);
  cout << "- Inserción 25" << endl;
  a.Insertar(c25);
  cout << "- Inserción 32" << endl;
  a.Insertar(c32);
  cout << "- Inserción 42" << endl;
  a.Insertar(c42);
  cout << "- Inserción 5" << endl << endl;
  a.Insertar(c5);

  borrar();

  return 0;
}

void borrar()
{
  cout << "Borrado 55 :" << endl;
  a.Borrar(c55);
  cout << "+ Resultado borrado : " << a.Niveles() << endl << endl;
  cout << "Borrado 32 :" << endl;
  a.Borrar(c32);
  cout << "+ Resultado borrado : " << a.Niveles() << endl << endl;
  cout << "Borrado 40:" << endl;
  a.Borrar(c40);
  cout << "+ Resultado borrado : " << a.Niveles() << endl << endl;
  cout << "Borrado 30 :" << endl;
  a.Borrar(c30);
  cout << "+ Resultado borrado : " << a.Niveles() << endl << endl;
}