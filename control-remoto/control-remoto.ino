// https://www.youtube.com/watch?v=wqZwQnh6ZtQ
// https://forum.arduino.cc/index.php?topic=453725.0
// https://forum.arduino.cc/index.php?topic=120955.0    <--- conflicto buzzer y control remoto

#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

// botones control remoto (valor hexadecimal)

// Control remoto "SONY TV RMT-TX102B" (tele casa)
const long int menos = 0xC90;    // vol-
const long int mas = 0x490;  //vol+ 
const long int uno = 0x10;  
const long int dos = 0x810;  
const long int tres = 0x410;
const long int cuatro = 0xC10;

/*
// Control remoto "Car mp3"
const long int menos = 0xFFE01F;
const long int mas = 0xFFA857;  
const long int uno = 0xFF30CF;  // R
const long int dos = 0xFF18E7;  // G
const long int tres = 0xFF7A85; // B
*/
/*
El control "car mp3" funciona a medias. Produce en muchas ocasiones distintas codificaciones para la misma tecla,
teniendo que pulsarla repetidas veces para obtener el efecto deseado.
*/

// sensor
const byte pin_sensor_infrarrojo = 4;
IRrecv sensor_infrarrojo (pin_sensor_infrarrojo);
decode_results codigo;

// pines led RGB (con PWM)
const byte pin_R = 11;
const byte pin_G = 5;
const byte pin_B = 6;

// buzzer pasivo: https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/
/*
El buzzer interfiere con los pines 3 y 11 cuando se activa, cagando el rojo en el led rgb. 
El pin 9 tambien se ve afectado por ir remote (no puede usarse, congela el arduino).
Lo mas logico es usar el pin 10, el unico restante disponible con pwm, pero tampoco funciona; de esa suerte,
el funcionamiento del circuito tiene la limitacion inicialmente descripta.
*/
const byte pin_buzzer = 12;

byte intensidad;
byte i;

void setup() 
{
  sensor_infrarrojo.enableIRIn();
  
  pinMode(pin_R, OUTPUT);
  pinMode(pin_G, OUTPUT);
  pinMode(pin_B, OUTPUT);
  pinMode(pin_buzzer, OUTPUT);

  intensidad = 0;
  i = pin_R;
  
  Serial.begin(9600);
}

void loop() 
{
  if (sensor_infrarrojo.decode(&codigo))
  {
    switch (codigo.value)
    {
      case uno:
        i = pin_R;
        intensidad = 0;
        break;
      case dos:
        i = pin_G;
        intensidad = 0;
        break;
      case tres:
        i = pin_B;
        intensidad = 0;
        break;
      case cuatro:
        i = pin_buzzer;
        intensidad = 0;
        break;
      //------------------
      case mas:
      {
        if (intensidad <= 230)
        intensidad += 25;

        if (i == pin_buzzer)
          tone(pin_buzzer, 1000 + intensidad);
        else
          analogWrite(i, intensidad);
        
        break;
      }
      case menos:
      {
        if (intensidad >= 25)
        intensidad -= 25;

        if (i == pin_buzzer)
        {
           if (intensidad == 0)
              noTone(pin_buzzer);
           else
              tone(pin_buzzer, 1000 + intensidad);
        }
        else
          analogWrite(i, intensidad);

        break;
      }
    }
    
     Serial.print("Pin: ");
     Serial.print(i);
     Serial.print(" ; intensidad: ");
     Serial.println(intensidad);
    
    //Serial.println(codigo.value, HEX);
    

    delay(100); // sony
    // delay(400); // car mp3
    sensor_infrarrojo.resume();
  }
}
