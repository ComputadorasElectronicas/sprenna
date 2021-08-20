
#include "AnalogSensor.h"

// Creo una instancia de la clase de sensores analogicos
AnalogSensor LM335 = AnalogSensor();

void setup()
{
  // La configuro (PinAnalogico, X1, Y1, X2, Y2)
  // donde "X" son los valores de salida del ADC
  // y los "Y" sus correspondientes valores en variables de ingenieria
  LM335.config(A0, 0, -273, 558, 0);
  Serial.begin(9600);
}


void loop()
{
  float temperatura;

  // Leo el sensor
  temperatura = LM335.leer();

  // Imprimo el valor leido
  Serial.println("--------------------------------");
  Serial.println("Temp: " + String(temperatura) + " *C");

  delay(500);
}