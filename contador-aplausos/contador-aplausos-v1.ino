const byte microfono = 13;  // valor analogico aprox: 525 / 530
byte cont;

/* http://www.circuitbasics.com/arduino-7-segment-display-tutorial/
     A
    ----
 F |    | B
   | G  |
    ----
 E |    | C   
   |    | 
    ----
     D   *  DP

*/
const byte A = 12;
const byte B = 11;
const byte C = 10;
const byte D = 9;
const byte E = 8;
const byte F = 7;
const byte G = 6;
const byte DP = 5;

void numero(byte);

void setup() 
{
  byte pines[] = {A, B, C, D, E, F, G, DP};
  byte i;

  for (i = 0; i < 8; i++)
    pinMode(pines[i], OUTPUT);

  pinMode(microfono, INPUT); 
  cont = 0;
  numero(cont);
}

void loop() 
{
   if (digitalRead(microfono) == HIGH)
   {
    if (cont != 9)
      cont++;
    else
      cont = 0;

    numero(cont);
    delay(100);
  }
}

void numero(byte i)
{
  static byte j;
  static byte pines[] = {A, B, C, D, E, F, G, DP};
  static boolean on_off[10][8] =
  {
    1, 1, 1, 1, 1, 1, 0, 0,  // 0
    0, 1, 1, 0, 0, 0, 0, 0,  // 1
    1, 1, 0, 1, 1, 0, 1, 0,  // 2
    1, 1, 1, 1, 0, 0, 1, 0,  // 3
    0, 1, 1, 0, 0, 1, 1, 0,  // 4
    1, 0, 1, 1, 0, 1, 1, 0,  // 5
    1, 0, 1, 1, 1, 1, 1, 0,  // 6
    1, 1, 1, 0, 0, 0, 0, 0,  // 7
    1, 1, 1, 1, 1, 1, 1, 0,  // 8
    1, 1, 1, 0, 0, 1, 1, 0   // 9
 // A, B, C, D, E, F, G, DP
  }; // leds del 7 segmentos apagados o encedidos (en orden segun pines[])

  for (j = 0; j < 8; j++)
    digitalWrite(pines[j], on_off[i][j]);   
}
