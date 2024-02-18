#include <Servo.h>

// https://servodatabase.com/servo/towerpro/sg90
Servo micro_servo;
const int pin_micro_servo = 2;
const int pulso_min = 500;    // en micro segundos
const int pulso_max = 2400;

const int pin_potenciometro = 5;  // entrada analogica
int angulo;

void setup() 
{
  micro_servo.attach(pin_micro_servo, pulso_min, pulso_max);  // inicializacion del servo
  /*
  //Controlar valor del angulo:
  Serial.begin(9600);
  */
}

void loop() 
{
  angulo = map(analogRead(pin_potenciometro), 0, 1023, 0, 180); // mapea el valor leido del potenciometro, desde el conjunto de partida entre 0 y 1023, al de llegada, entre 0 y 180 grados
  
  micro_servo.write(angulo);
  delay(50);

  /*
  // Controlar valor del angulo:
  Serial.println(angulo);
  delay(50);
  */
}
