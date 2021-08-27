#ifndef PID_v1_h
#define PID_v1_h
#define LIBRARY_VERSION 1.2.1

class PID
{

public:

  // Constructor. Recibe los valores de las constantes del PID.
  // Por defecto, los valores min y max de la salida con 0-255
  // y el tiempo de muestreo/calculo es de 100 ms 
  PID(double Kp, double Ki, double Kd, double setPoint);

  // Metodo de calculo/actualiacion de los valores del PID.
  // El calculo se realiza cada "SampleTime" milisegundos, pero
  // esta funcion deberia ser llamada en cada loop()
  double Compute(double newInput);

  // Metodo para cambiar los valores min y max de salida
  void SetOutputLimits(double Min, double Max);

  // Metodo para cambiar las constantes del PID
  void SetTunings(double Kp, double Ki, double Kd);

  void SetSampleTime(int NewSampleTime);

  void SetSetPoint(double setPoint);

  //Display functions ****************************************************************
  double GetKp(); // These functions query the pid for interal values.
  double GetKi(); //  they were created mainly for the pid front-end,
  double GetKd(); // where it's important to know what is actually
  double GetSetPoint();

private:
  double _dispKp; // * we'll hold on to the tuning parameters in user-entered
  double _dispKi; //   format for display purposes
  double _dispKd;

  double _kp; // * (P)roportional Tuning Parameter
  double _ki; // * (I)ntegral Tuning Parameter
  double _kd; // * (D)erivative Tuning Parameter

  double _setPoint;
  double _output;

  unsigned long _lastTime;
  double _integral;
  double _lastInput;

  unsigned long _SampleTime;
  double _outMin;
  double _outMax;
};
#endif
