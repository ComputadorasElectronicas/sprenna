
// .h de Header (archivo de cabecera)

#ifndef ContadorSimple_h // if no definition (si no esta definido ContadorSimple_h)
#define ContadorSimple_h // defino una etiqueta que se llama ContadorSimple_h e incluyo el codigo...
// si ya estaba definida la etiqueta, no incluyo el codigo.

// .h de Header (archivo de cabecera)

class ContadorSimple
{
private:
    int cuenta;

public:
    ContadorSimple();   // constructor
    void Inc();         // incrementa la cuenta en 1
    int CuentaActual(); // devuelve la cuenta actual
    void Reset();       // lleva la cuenta a 0
};

#endif // END del ifndef