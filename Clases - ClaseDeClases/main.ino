
#include "ContadorSimple.h"

void setup()
 {
	Serial.begin(9600);
	pinMode(3, INPUT);
	pinMode(13, OUTPUT);

	Serial.println("Inicializacion lista.\n\n");
	Serial.println("1 -> Incrementa");
	Serial.println("2 -> Cuenta actual");
	Serial.println("3 -> Reset");
	Serial.println("--------------------");
 }


ContadorSimple cnt = ContadorSimple();

char c;
void loop()
 {

	c = Serial.read();

	switch(c){
		case '1':
			Serial.println("Incrementa");
			cnt.Inc();
		break;

		case '2':
			Serial.print("Cuenta actual: ");
			Serial.println(cnt.CuentaActual());
		break;

		case '3':
			cnt.Reset();
			Serial.println("Reset");
		break;


		default:
		break;
	}

	delay(100);
 }









