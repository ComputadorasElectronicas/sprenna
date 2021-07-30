

// definicion del tamaño del array
#define TAM_ARRAY 10

// Prototipos de funcion

float CalcularPromedioDelArray(int arr[], int tamanio);
void BorrarValoresDelArray(int arr[], int tamanio);

void BorrarVariable(int var);

void setup()
{
	Serial.begin(9600);
	Serial.println("Inicializacion Lista");
}

// declaracion de un array de 10 ELEMENTOS de tipo int
// SIN inicializacion
int notas[TAM_ARRAY];

// declaracion de un array de 10 ELEMENTOS de tipo int
// Las dos lineas son equivalentes.
// Los valores separados por comas y entre corchetes son los valores de inicializacion.
int vec2[] = {7, 7, 8, 7, 7, 7, 7, 7, 7, 10};
int vec3[TAM_ARRAY] = {7, 7, 8, 7, 7, 7, 7, 7, 7, 10};

void loop()
{

	// vacio el puerto serie, leo todo lo que haya
	while (Serial.available() != 0)
	{
		Serial.read();
	}

	// Recorro todo el array, y por cada loop del for almaceno un valor ingresado desde el serial.
	for (int i = 0; i < TAM_ARRAY; i++)
	{
		Serial.print("Ingrese la nota alumno " + String(i) + ": ");

		while (Serial.available() == 0)
		{
		}							   // Espero que se reciba algo...
		notas[i] = Serial.read() - 48; // Convierto de ASCII a numero 0-9 y guardo en la casilla "i" del array

		Serial.println(notas[i]);
	}

	Serial.println("\n\n-----------------------\n"); // Esto es un separador para que se vea mejor en el teminal
	Serial.println("Termino el ingreso de datos");
	delay(1000);
	Serial.println("-----------------------\n");
	Serial.println("Imprimo los valores del array");

	// Recorro todo el arreglo e imprimo los valores
	for (int i = 0; i < TAM_ARRAY; i++)
	{
		Serial.println("Nota[" + String(i) + "]: " + String(notas[i]));
	}

	Serial.println("\n\n-----------------------\n");
	Serial.println("Calculo de promedio");

	float promedio = CalcularPromedioDelArray(notas, TAM_ARRAY);

	Serial.println("Promedio: " + String(promedio));

	Serial.println("\n\n-----------------------\n");
	Serial.println("Cambio el valor del 6to elemento a 58");
	// Fuerzo el valor del SEXTO elemento del array
	// Se muestra el 5 entre corchetes porque el indice comienza desde CERO
	// Para mostrar que se puede acceder a un elemento cualquiera
	// como si fuese una variable int cualquiera
	notas[5] = 58;

	// Imprimo los valores del array
	for (int i = 0; i < TAM_ARRAY; i++)
	{
		Serial.println("Nota[" + String(i) + "]: " + String(notas[i]));
	}

	Serial.println("\n\n-----------------------\n\n\n");

	Serial.println("Funcion para BORRAR el array");

	BorrarValoresDelArray(notas, TAM_ARRAY); // Los arrays SE PUEDEN MODIFICAR desde dentro de la funcion

	// Imprimo los valores del array
	for (int i = 0; i < TAM_ARRAY; i++)
	{
		Serial.println("Nota[" + String(i) + "]: " + String(notas[i]));
	}

	Serial.println("\n-----------------------\n");
	int variable = 5;
	Serial.println("Var: " + String(variable));

	BorrarVariable(variable); // Este paso de parametros NO altera la variable, opera con una copia

	Serial.println("Var_post: " + String(variable));

	Serial.println("Loop\n\n\n");
	delay(1000);
}

float CalcularPromedioDelArray(int arr[], int tamanio)
{
	// Recorro todo el arreglo y voy sumando cada valor en la variable suma
	// (inicializo a cero para que sea la suma de los elementos del array)
	int suma = 0;
	for (int i = 0; i < tamanio; i++)
	{
		suma = suma + arr[i];
	}

	// El promedio de valores del arreglo es la suma dividido la cantidad de elementos
	float promedio = (float)suma / tamanio;
	return promedio;
}

void BorrarValoresDelArray(int arr[], int tamanio)
{
	for (int i = 0; i < tamanio; i++)
	{
		arr[i] = 0;
	}
}

void BorrarVariable(int var)
{
	var = 0;
}
