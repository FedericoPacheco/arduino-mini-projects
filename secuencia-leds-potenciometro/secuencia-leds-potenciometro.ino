const int boton = 2;
const int led_amarillo = 9;
const int led_rojo = 10;
const int led_verde = 11;
const int potenciometro = 5;   // entrada analogica

int led_i;
int brillo_led_i;

void setup() 
{
  pinMode(led_amarillo, OUTPUT);
  pinMode(led_rojo, OUTPUT);
  pinMode(led_verde, OUTPUT);
  pinMode(boton, INPUT);

  led_i = led_amarillo;
}

void loop()
{
  while (digitalRead(boton) == LOW)
  {
    brillo_led_i = analogRead(potenciometro) / 4;    // analogRead() retorna un entero entre 0 y 1023, analogWrite() trabaja con enteros entre 0 y 255
    analogWrite(led_i, brillo_led_i);
  }
  
  if (led_i == led_amarillo)
    led_i = led_rojo;
  else if (led_i == led_rojo)
    led_i = led_verde;
  else if (led_i == led_verde)
    led_i = led_amarillo;

  while (digitalRead(boton) == HIGH) {}
}
