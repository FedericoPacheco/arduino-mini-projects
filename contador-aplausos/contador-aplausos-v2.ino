#include <SevenSeg.h>
#include <stdlib.h>
// https://github.com/sigvaldm/SevenSeg/blob/master/README.md

const byte microfono = 1;
int cont;
byte k;
byte digito_5;
char cont_str[10];
char buf[50];   // buffer: https://playground.arduino.cc/Code/PrintingNumbers/

const byte D1 = 6;
const byte D2 = 5;
const byte D3 = 4;
const byte D4 = 3;
const byte D5 = 2;

const byte A_4 = 7;
const byte B_4 = 8;
const byte C_4 = 9;
const byte D_4 = 10;
const byte E_4 = 11;
const byte F_4 = 12;
const byte G_4 = 13;

const byte A_1 = A0;
const byte B_1 = A1;
const byte C_1 = A2;
const byte D_1 = A3;
const byte E_1 = A4;
const byte F_1 = A5;
const byte G_1 = 0;
byte pines_led_1_dig[] = {A_1, B_1, C_1, D_1, E_1, F_1, G_1};

byte cant_digitos = 4;
int pines_digitos[] = {(int) D1, (int) D2, (int) D3, (int) D4};
SevenSeg led_4_dig((int) A_4, (int) B_4,(int) C_4,(int) D_4,(int) E_4,(int) F_4,(int) G_4);

void digito(byte);

void setup() 
{
  led_4_dig.setDigitPins((int) cant_digitos, pines_digitos);
  led_4_dig.setTimer(2);
  led_4_dig.startTimer();
  

  for (k = 0; k < 7; k++)
    pinMode (pines_led_1_dig[k], OUTPUT);
  
  pinMode(D5, OUTPUT);
  digitalWrite(D5, LOW);
  
  pinMode(microfono, INPUT);
  cont = 0;
  digito_5 = 0;
}

void loop()
{
  if (digitalRead(microfono) == HIGH)
  {
    if (digito_5 < 10)
    {
      if (cont < 9999)
        cont++;
      else if (cont > 9999)
      {
        cont = 0;
        digito_5++;

      if (digito_5 < 10)
        digito(digito_5); 
      }
  
      if (digito_5 >= 1)   // mostrar 0s a la izquierda para simular un numero bien construido
      {
        if (cont < 10)
          strcpy(cont_str, "000");
        else if (cont >= 10 && cont < 100)
          strcpy(cont_str, "00");
        else if (cont >= 100 && cont < 1000)
          strcpy(cont_str, "0");
        else
          strcpy(cont_str, "");
      
        strcat(cont_str, itoa(cont, buf, 10));

        led_4_dig.clearDisp();
        led_4_dig.write(cont_str);
      }
      else
      {
        led_4_dig.clearDisp();
        led_4_dig.write(cont);
      }

     delay(150);
    }
    else   // desbordamiento
    {
      led_4_dig.clearDisp();
      led_4_dig.write(9999);
      delay(60000);
    }
  }
}

ISR(TIMER2_COMPA_vect)  // https://github.com/sigvaldm/SevenSeg/blob/master/extras/SevenSeg.pdf  forma de evitar tener que colocar .write() en un bucle
{
  led_4_dig.interruptAction();
}

void digito(byte i)
{
  static byte j;
  static boolean on_off[10][7] =
  {
    1, 1, 1, 1, 1, 1, 0,  // 0
    0, 1, 1, 0, 0, 0, 0,  // 1
    1, 1, 0, 1, 1, 0, 1,  // 2
    1, 1, 1, 1, 0, 0, 1,  // 3
    0, 1, 1, 0, 0, 1, 1,  // 4
    1, 0, 1, 1, 0, 1, 1,  // 5
    1, 0, 1, 1, 1, 1, 1,  // 6
    1, 1, 1, 0, 0, 0, 0,  // 7
    1, 1, 1, 1, 1, 1, 1,  // 8
    1, 1, 1, 0, 0, 1, 1   // 9
 // A, B, C, D, E, F, G
  }; // leds del 7 segmentos apagados o encedidos (en orden segun pines[])

  for (j = 0; j < 7; j++)
    digitalWrite(pines_led_1_dig[j], on_off[i][j]);   
}
