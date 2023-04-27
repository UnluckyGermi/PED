#include "tabbcom.h"

/*
  -Constructor de copia y asignación
    1) Copia y asignación de un árbol vacío
    2) Comprobar la copia exacta de un árbol
    3) Comprobar la asignación de un árbol

  -Función EsVacio()

  -Destructor (probar con valgrind)
    Comando: valgrind --tool=memcheck --leak-check=full -v [nombre_del_ejecutable]
    No se debe perder memoria en la ejecución ni haber errores de referencia
    (aunque no se comprueba en la corrección)
*/

int main ()
{
  TComplejo a(-3, 2), b(3, -2), c(-3, -2), d(3, 2), e(1, -2), f(7, 4);
  TABBCom arbolvacio;

  if (arbolvacio.EsVacio())
  {
    cout << "OK - EsVacio -- " << arbolvacio << endl;
  }

  TABBCom arbol(arbolvacio);

  if (arbol.EsVacio())
  {
    cout << "OK - Copia de un arbol vacio -- " << arbol << endl;
  }

  arbol.Insertar(f);
  if (!arbol.EsVacio())
  {
    cout << "OK - No EsVacio -- " << arbol << endl;
  }

  arbol = arbolvacio;
  if (arbol.EsVacio())
  {
    cout << "OK - Asignación de un arbol vacio -- " << arbol << endl;
  }

  // Comprobación de las estructuras
  arbol.Insertar(b);
  arbol.Insertar(c);
  arbol.Insertar(d);
  arbol.Insertar(f);
  arbol.Insertar(e);
  arbol.Insertar(a);

  arbolvacio = arbol;
  TABBCom arbol2(arbolvacio);
  
  if (arbol.Preorden() == arbolvacio.Preorden())
  {
    cout << "OK - Estructura despues de asignacion -- " << arbolvacio << endl;
  }

  if (arbol.Preorden() == arbol2.Preorden())
  {
    cout << "OK - Estructura despues de copia -- " << arbolvacio << endl;
  }

  TABBCom* arbol3 = new TABBCom(arbol);
  arbol3->~TABBCom();

  if (arbol3->EsVacio())
  {
    cout << "OK - Destructor arbol" << endl;
  }

  delete arbol3;

  return 0;
}