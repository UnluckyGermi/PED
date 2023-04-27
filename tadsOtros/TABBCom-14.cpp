#include "tabbcom.h"

/*
  -Función Raiz
    1) Devolver valor de la raíz
    2) Si está vacío, TComplejo vacío

  -Recorridos

  -Altura y Nodos
*/

int main ()
{
  TComplejo a(-3, 2), b(3, -2), c(-3, -2), d(3, 2), e(1, -2), f(7, 4);
  TABBCom arbol1, arbolvacio;
  // Estructura árbol1
  arbol1.Insertar(b);
  arbol1.Insertar(c);
  arbol1.Insertar(d);
  arbol1.Insertar(f);
  arbol1.Insertar(e);
  arbol1.Insertar(a);
  // arbol1:
  //            b
  //          /   \ 
  //         c     d
  //       /   \     \ 
  //      e     a     f

  // Dato raíz de un árbol vacío
  if (arbolvacio.Raiz() == TComplejo())
  {
    cout << "OK - Dato raiz de un arbol vacio" << endl;
  }
  // Dato raíz de un árbol
  if (arbol1.Raiz() == b)
  {
    cout << "OK - Dato raiz de un arbol" << endl;
  }

  // Recorridos
  // Preorden
  cout << "Recorrido preorden : " << arbol1.Preorden() << endl;
  cout << "Recorrido preorden vacio : " << arbolvacio.Preorden() << endl;
  // Inorden
  cout << "Recorrido inorden : " << arbol1.Inorden() << endl;
  cout << "Recorrido inorden vacio : " << arbolvacio.Inorden() << endl;
  // Postorden
  cout << "Recorrido postorden : " << arbol1.Postorden() << endl;
  cout << "Recorrido postorden vacio : " << arbolvacio.Postorden() << endl;

  // Altura y Nodos
  cout << "Altura arbolvacio : " << arbolvacio.Altura() << endl;
  cout << "Nodos arbolvacio : " << arbolvacio.Nodos() << endl;
  cout << "Nodos hoja arbolvacio : " << arbolvacio.NodosHoja() << endl;

  cout << "Altura arbol : " << arbol1.Altura() << endl;
  cout << "Nodos arbol : " << arbol1.Nodos() << endl;
  cout << "Nodos hoja arbol : " << arbol1.NodosHoja() << endl;

  return 0;
}