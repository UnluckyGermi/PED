#include "tabbcom.h"

/*
  -Operador igualdad
    Mismos elementos sin importar la estructura
  
  -Borrar
    1) No borrar un elemento que no existe
    2) Borrar en todo tipo de árboles
    3) No borrar en un árbol vacío
*/

int main ()
{
  TComplejo a(-3, 2), b(3, -2), c(-3, -2), d(3, 2), e(1, -2), f(7, 4);
  TABBCom arbol1, arbol2;
  // Estructura árbol1
  arbol1.Insertar(b);
  arbol1.Insertar(c);
  arbol1.Insertar(d);
  arbol1.Insertar(f);
  arbol1.Insertar(e);
  arbol1.Insertar(a);
  // Estructura árbol2
  arbol2.Insertar(d);
  arbol2.Insertar(e);
  arbol2.Insertar(a);
  arbol2.Insertar(b);
  arbol2.Insertar(f);
  arbol2.Insertar(c);

  if (arbol1 == arbol2)
  {
    cout << "OK - Operador igualdad" << endl;
  }

  TABBCom arbolvacio;

  if (!(arbol1 == arbolvacio))
  {
    cout << "OK - Operador igualdad con vacio" << endl;
  }

  arbol2 = arbolvacio;
  if (arbol2 == arbolvacio)
  {
    cout << "OK - Operador igualdad con ambos vacios" << endl;
  }
  
  // arbol1:
  //            b
  //          /   \ 
  //         c     d
  //       /   \     \ 
  //      e     a     f
  cout << "arbol1 : " << arbol1 << endl;
  // Borrado de nodo con un hijo (d)
  if (arbol1.Borrar(d))
  {
    cout << "OK - Borrado nodo 1 hijo -- " << arbol1 << endl;
  }
  // Borrado de nodo con dos hijos (c)
  if (arbol1.Borrar(c))
  {
    cout << "OK - Borrado nodo 2 hijos -- " << arbol1 << endl;
  }
  // Borrado de nodo hoja (a)
  if (arbol1.Borrar(a))
  {
    cout << "OK - Borrado nodo hoja -- " << arbol1 << endl;
  }
  // Borrado de la raíz de todo el árbol con 2 hijos
  if (arbol1.Borrar(b))
  {
    cout << "OK - Borrado raiz con 2 hijos -- " << arbol1 << endl;
  }
  // Borrado de la raíz de todo el árbol con 1 hijo
  if (arbol1.Borrar(e))
  {
    cout << "OK - Borrado raiz con 1 hijo -- " << arbol1 << endl;
  }
  // Borrado de un árbol hoja
  if (arbol1.Borrar(f))
  {
    cout << "OK - Borrado arbol hoja -- " << arbol1 << endl;
  }
  // Borrado árbol vacío
  if (!arbolvacio.Borrar(a))
  {
    cout << "OK - Borrado arbol vacio" << endl;
  }
  // Borrado nodo que no existe
  if (!arbol1.Borrar(d))
  {
    cout << "OK - Borrado nodo que no existe" << endl;
  }

  TABBCom arbolPrueba;
  arbolPrueba.Insertar(TComplejo(8));
  arbolPrueba.Insertar(TComplejo(3));
  arbolPrueba.Insertar(TComplejo(5));
  arbolPrueba.Insertar(TComplejo(4));
  arbolPrueba.Insertar(TComplejo(6));
  arbolPrueba.Insertar(TComplejo(7));
  arbolPrueba.Insertar(TComplejo(5.5));
  arbolPrueba.Insertar(TComplejo(6.5));
  arbolPrueba.Insertar(TComplejo(4.5));
  arbolPrueba.Insertar(TComplejo(4.1));
  arbolPrueba.Insertar(TComplejo(4.7));
  arbolPrueba.Insertar(TComplejo(4.8));
  arbolPrueba.Insertar(TComplejo(4.6));

  arbolPrueba.Borrar(TComplejo(3));
  arbolPrueba.Borrar(TComplejo(5));
  cout << "Borrado arbolPrueba : " << arbolPrueba << endl;

  return 0;
}