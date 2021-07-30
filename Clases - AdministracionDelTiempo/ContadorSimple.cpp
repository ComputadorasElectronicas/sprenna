

// *.c o *.cpp Archivos de codigo

#include "ContadorSimple.h"

ContadorSimple::ContadorSimple()
{
    cuenta = 0;
}

void ContadorSimple::Inc()
{
    cuenta = cuenta + 1;
}

int ContadorSimple::CuentaActual()
{
    return cuenta;
}

void ContadorSimple::Reset()
{
    cuenta = 0;
}