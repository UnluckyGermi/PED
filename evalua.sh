#!/bin/bash

# Historial de versiones
#
# 2.0 (17/03/2020): corregido un error que hacía que la práctica no se recompilara para algunos ficheros de prueba
#

#Si tus ficheros de prueba no comienzan por "tad", cambia "tad*.cpp" por el prefijo de tus ficheros, por ejemplo "prueba*.cpp":
for FILE in $1/*/tad*.cpp ; do 
	echo -e "\e[32mEvaluando $FILE \e[0m"
	
	cp $FILE src/tad.cpp 
        rm -f ./tad
	make
	./tad > $FILE.out
  valgrind --tool=memcheck --leak-check=full ./tad &> /dev/null
  if [ "$?" == "1" ]; then
    echo -e "\e[31mERROR DE MEMORIA\e[0m"
  fi
	diff -b -B -i $FILE.out $FILE.sal
	if [ "$?" == "0" ]; then
		echo "OK"
	else
		echo "ERROR"
	fi
done

