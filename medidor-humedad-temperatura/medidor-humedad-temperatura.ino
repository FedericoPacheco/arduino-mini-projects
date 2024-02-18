#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>

// Panel LCD
const int RS = 7;
const int E = 6;
const int D4 = 5;
const int D5 = 4;
const int D6 = 3;
const int D7 = 2;

const int columnas = 16;
const int filas = 2;

LiquidCrystal panel_lcd(RS, E, D4, D5, D6, D7);  // indicar los pines de conexion, en orden

//-------------------------------------------------------------------------------------

// Sensor de temperatura, humedad
// https://aprendiendoarduino.wordpress.com/tag/dht/

const int pin_sensor_temp_humedad = 8;

DHT sensor_temp_humedad(pin_sensor_temp_humedad, DHT11);

//-------------------------------------------------------------------------------------

void setup() 
{
  panel_lcd.begin(columnas, filas);  // indicar tamanio
  sensor_temp_humedad.begin();

  //Serial.begin(9600);
}

void loop() 
{
  static int T, H;

  T = sensor_temp_humedad.readTemperature();
  H = sensor_temp_humedad.readHumidity();
  
  panel_lcd.setCursor(0,0);
  panel_lcd.print("Temp: ");
  panel_lcd.print(T);
  panel_lcd.print(" C");
  
  panel_lcd.setCursor(0,1);
  panel_lcd.print("Hum: ");
  panel_lcd.print(H);
  panel_lcd.print(" %");

  /*
  Serial.print(T);
  Serial.print(" ");
  Serial.println(H);
  */

  delay(1000);
}
