#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

// Panel LCD
// los pines analogicos se pueden usar como E/S digitales: https://www.arduino.cc/en/Tutorial/AnalogInputPins
const byte RS = A0;
const byte E = A1;
const byte D4 = A2;
const byte D5 = A3;
const byte D6 = A4;
const byte D7 = A5;
const byte columnas_lcd = 16;
const byte filas_lcd = 2;
LiquidCrystal panel_lcd(RS, E, D4, D5, D6, D7);

// Matriz de pulsadores
const byte columnas_pulsadores = 4;
const byte filas_pulsadores = 4;
byte pines_columnas[columnas_pulsadores] = {5, 4, 3, 2};
byte pines_filas[filas_pulsadores] = {6, 7, 8, 9};
char pulsadores[columnas_pulsadores][filas_pulsadores] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'0', 'D', 'E', 'F'}
};
Keypad matriz_pulsadores(makeKeymap(pulsadores), pines_filas, pines_columnas, filas_pulsadores, columnas_pulsadores);

// Variables globales
byte x;  // apunta a la siguiente columna en la que se escribira un char
byte y;

// Funciones
void bienvenida();

void setup() 
{
  panel_lcd.begin(columnas_lcd, filas_lcd);  // indicar tamanio

  bienvenida();
  x = 0;
  y = 0;
}

void bienvenida()
{
  panel_lcd.setCursor(3, 0);
  panel_lcd.print("Mensajeador");
  panel_lcd.setCursor(6, 1);
  panel_lcd.print("ASCII");
  delay(3000);
  panel_lcd.clear();

  panel_lcd.print("A: reset entrada");
  panel_lcd.setCursor(0, 1);
  panel_lcd.print("B: borrar char");
  delay(3000);
  panel_lcd.clear();
  panel_lcd.print("C: borrar string");
  delay(2000);
  panel_lcd.clear();
}

void loop() 
{
  static char ch;
  static byte cont;
  static byte letra_ASCII[3];
  
  cont = 0;
  letra_ASCII[0] = letra_ASCII[1] = letra_ASCII[2] = 0;
  
  while (cont < 3)
  {
    ch = matriz_pulsadores.getKey();

    if
    (
      ch == '0' ||
      ch == '1' ||
      ch == '2' ||
      ch == '3' ||
      ch == '4' ||
      ch == '5' ||  
      ch == '6' ||  
      ch == '7' ||
      ch == '8' ||
      ch == '9'
    )
    {
      letra_ASCII[cont] = (int) ch - 48;   // forma barata de "convertir" el caracter al digito
      cont++;
    }
    else if (ch == 'A')
    {
      cont = 0;
      letra_ASCII[0] = letra_ASCII[1] = letra_ASCII[2] = 0;
    }
    else if (ch == 'B')
    {
      cont = 0;
      
      if (x > 0)
      {
        x--;
        panel_lcd.setCursor(x, y);
        panel_lcd.print(" ");
      }
      else if (x == 0 && y == 1)
      {
        x = 16;
        y = 0;
        panel_lcd.setCursor(x, y);
        panel_lcd.print(" ");
      }
    }
    else if (ch == 'C')
    {
      panel_lcd.clear();
      cont = 0;
      x = 0;
      y = 0;
    }
  }

   panel_lcd.setCursor(x, y);
   panel_lcd.print(char(100 * letra_ASCII[0] + 10 * letra_ASCII[1] + 1 * letra_ASCII[2]));

   if (x < 16)
    x++;
   else if (x >= 16 && y == 0)
   {
      x = 0;
      y = 1;
   }
   else if (x >= 16 && y == 1)
   {
    panel_lcd.clear();
    panel_lcd.print("Error!");
    delay(3000);
    panel_lcd.clear();

    x = 0;
    y = 0;
   }
}
