/**********************************************************************************************
 * Arduino PID Library - Version 1.2.1
 * by Brett Beauregard <br3ttb@gmail.com> brettbeauregard.com
 *
 * This Library is licensed under the MIT License
 * Sebastia Prenna sprenna@golegioitc.edu.ar 
 * Adaptacion para clases - simplificacion para no usar punteros ni inversiones de parametros.
 * Traduccion y reescritura de comentarios y documentacion.
 **********************************************************************************************/

#include "PID_v1.h"

/*Constructor (...)*********************************************************
 *    Constructor con paso de contantes del PID, no se podrian poner
 * por defecto, porque dependen del sistema.
 ***************************************************************************/
PID::PID(double Kp, double Ki, double Kd, double setPoint)
{
   // default output limits corresponden a los limites de salida del PWM de Arduino
   PID::SetOutputLimits(0, 255);

   PID::SetTunings(Kp, Ki, Kd);

   //default Controller Sample Time is 0.1 seconds
   _SampleTime = 100;
   _setPoint = setPoint;
   _output = 0;

   _lastTime = millis() - _SampleTime;
}

/* Compute() **********************************************************************
 *     This, as they say, is where the magic happens.  this function should be called
 *   every time "void loop()" executes.  the function will decide for itself whether a new
 *   pid Output needs to be computed.  returns true when the output is computed,
 *   false when nothing has been done.
 *   Se le tiene que pasar el valor de una nueva lectura del ADC (convertida a las mismas
 *   unidades con que se configura el SetPoint).
 *   Devuelve el valor que corresponde, para setear el nuevo valor de PWM.
 **********************************************************************************/
double PID::Compute(double newInput)
{
   unsigned long now = millis();
   unsigned long timeChange = (now - _lastTime);
   if (timeChange >= _SampleTime)
   {

      // Calcula el error y el diferencial del error
      double error = _setPoint - newInput;
      double dInput = (error - _lastInput);

      // Termino "P" = Kp * error
      double _proporcional = _kp * error;

      // Termino "I" = Ki * integral del error
      // Acumulacion del termino integral
      // La sumatoria seria la integral
      _integral += (_ki * error);

      // Mantiene al termino integral dentro de
      // los limites max y min de salida
      if (_integral > _outMax)
         _integral = _outMax;
      else if (_integral < _outMin)
         _integral = _outMin;
   
      // Termino "D" = Kd * derivada del error
      double _derivativo = _kd * dInput;

      // Calcula la salida del PID
      _output = _proporcional + _integral + _derivativo;

      // y la mantiene en el rango min - max
      if (_output > _outMax)
         _output = _outMax;
      else if (_output < _outMin)
         _output = _outMin;

      // guarda el valor de entrda para la proxima ronda...
      _lastInput = error;
      // guarda el tiempo en que se ejecuto esta ronda
      _lastTime = now;
   }

   return _output;
}

/* SetTunings(...)*************************************************************
 * Para ajustes de los parametros del controlador. Se llama automaticamente
 * desde el constructor, pero se puede llamar posteriormente para cambiar los
 * valores de las constantes.
 ******************************************************************************/
void PID::SetTunings(double Kp, double Ki, double Kd)
{
   if (Kp < 0 || Ki < 0 || Kd < 0)
      return;

   _dispKp = Kp;
   _dispKi = Ki;
   _dispKd = Kd;

   double SampleTimeInSec = ((double)_SampleTime) / 1000;
   _kp = Kp;
   _ki = Ki * SampleTimeInSec;
   _kd = Kd / SampleTimeInSec;
}

/* SetSampleTime(...) *********************************************************
 * sets the period, in Milliseconds, at which the calculation is performed
 ******************************************************************************/
void PID::SetSampleTime(int NewSampleTime)
{
   if (NewSampleTime > 0)
   {
      double ratio = (double)NewSampleTime / (double)_SampleTime;
      _ki *= ratio;
      _kd /= ratio;
      _SampleTime = (unsigned long)NewSampleTime;
   }
}

void PID::SetSetPoint(double setPoint)
{
   _setPoint = setPoint;
}

/* SetOutputLimits(...)****************************************************
 *     This function will be used far more often than SetInputLimits.  while
 *  the input to the controller will generally be in the 0-1023 range (which is
 *  the default already,)  the output will be a little different.  maybe they'll
 *  be doing a time window and will need 0-8000 or something.  or maybe they'll
 *  want to clamp it from 0-125.  who knows.  at any rate, that can all be done
 *  here.
 **************************************************************************/
void PID::SetOutputLimits(double Min, double Max)
{
   if (Min >= Max)
      return;
   _outMin = Min;
   _outMax = Max;

   if (_output > _outMax)
      _output = _outMax;
   else if (_output < _outMin)
      _output = _outMin;

   if (_integral > _outMax)
      _integral = _outMax;
   else if (_integral < _outMin)
      _integral = _outMin;
}

/* Status Funcions*************************************************************
 * Just because you set the Kp=-1 doesn't mean it actually happened.  these
 * functions query the internal state of the PID.  they're here for display
 * purposes.  this are the functions the PID Front-end uses for example
 ******************************************************************************/
double PID::GetKp() { return _dispKp; }
double PID::GetKi() { return _dispKi; }
double PID::GetKd() { return _dispKd; }
double PID::GetSetPoint() { return _setPoint; }
