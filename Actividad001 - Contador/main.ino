#include "ContadorSimple.h"

// Bienvenido GitHub a Computadoras Electronicas!!


// TODO: ver esto

#define PULSADOR_CUENTA 3
#define PULSADOR_INGRESO_SERIAL 4
#define LED_BLINK 5
#define LED_INDICADOR 6

int referencia;

boolean flagPulsadorCuenta;

boolean flagIngresandoEntero;
String cadenaDeCaracteres;

int contadorDeLoopParaImpresion;

//--------------------
#define PERIODO_DE_LA_TAREA_IMPRESION 300
unsigned long ultimaEjecucionDeLaTareaImpresion = 0;
//--------------------
#define PERIODO_DE_LA_TAREA_BLINK 100
unsigned long ultimaEjecucionDeLaTareaBlink = 0;
//--------------------

ContadorSimple contador = ContadorSimple();

void setup()
{
    Serial.begin(9600);
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);

    Serial.setTimeout(100000);

    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);

    contador.Reset();

    referencia = 0;
    flagPulsadorCuenta = false;
    flagIngresandoEntero = false;
    cadenaDeCaracteres = "";

    contadorDeLoopParaImpresion = 0;
    Serial.println("Hola VS CODE 17:19hs");
}

void loop()
{

    // Cuenta de pulsaciones sin bloqueo del programa
    // Cuenta una sola vez por pulsacion...
    if (digitalRead(PULSADOR_CUENTA) == LOW)
    {
        if (flagPulsadorCuenta == false)
        {
            contador.Inc();
            flagPulsadorCuenta = true;
        }
    }
    else
    {
        flagPulsadorCuenta = false;
    }

    //------------------------------------------------------------------------------
    // Ingresar numero cuando se pulsa el otro pulsador...
    //------------------------------------------------------------------------------
    // Primero, si no esta en el modo de ingresar, y se pulsa, inicializa todo
    // lo necesario para adquirir el numero
    // y hace true la bandera que indica que esta en el proceso de adquisicion.

    if ((digitalRead(PULSADOR_INGRESO_SERIAL) == LOW) && (flagIngresandoEntero == false))
    {
        Serial.println("Ingrese el valor de referencia: ");
        cadenaDeCaracteres = "";
        flagIngresandoEntero = true;
        while (Serial.available() > 0)
        {
            char c = Serial.read();
            c++;
        }
    }

    // Si esta en el proceso de adquisicion, mientras haya caracteres NUMERICOS
    // en Serial, los lee y va armando una cadena de caracteres.
    // Cuando se recibe algo NO numerico, hace la conversion de String a Int
    // y "apaga" el modo de adquisicion.
    
    if (flagIngresandoEntero == true)
    {
        while (Serial.available() > 0)
        {
            char c = Serial.read();
            if ((c <= '9') && (c >= '0'))
            {
                cadenaDeCaracteres = cadenaDeCaracteres + c;
            }
            else
            {
                referencia = cadenaDeCaracteres.toInt();
                flagIngresandoEntero = false;
            }
        }
    }
    //------------------------------------------------------------------------------





    unsigned long ahora = millis();
    if (ahora - ultimaEjecucionDeLaTareaImpresion >= PERIODO_DE_LA_TAREA_IMPRESION)
    {
        ultimaEjecucionDeLaTareaImpresion = ahora;
        Serial.println("Tiempo seg: " + String(ahora / 1000.0));
        Serial.println("Referencia: " + String(referencia));
        Serial.println("Cuenta: " + String(contador.CuentaActual()));
        Serial.println("-----------------");
    }


    ahora = millis();
    if (ahora - ultimaEjecucionDeLaTareaBlink >= PERIODO_DE_LA_TAREA_BLINK)
    {
        ultimaEjecucionDeLaTareaBlink = ahora;

        if (digitalRead(LED_BLINK) == HIGH)
        {
            digitalWrite(LED_BLINK, LOW);
        }
        else
        {
            digitalWrite(LED_BLINK, HIGH);
        }
    }



    if(contador.CuentaActual() > referencia){
        digitalWrite(LED_INDICADOR, HIGH);
    }else{
        digitalWrite(LED_INDICADOR, LOW);
    }


}
