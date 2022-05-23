#include <Wire.h>
#include <LedControl.h>
#include <Firmata.h>

LedControl lc=LedControl(11,13,10,1);  // crea objeto

#define demora 250      // constante demora con valor de 250

byte flecha_abajo_1[8] = {   // array con primer cuadro de animacion de flecha
  B00001000,
  B00011000,
  B00110000,
  B01111111,
  B01111111,
  B00110000,
  B00011000,
  B00001000
};

byte flecha_abajo_2[8] = {   // array con segundo cuadro de animacion de flecha
  B00010000,
  B00110000,
  B01100000,
  B11111110,
  B11111110,
  B01100000,
  B00110000,
  B00010000
};

byte flecha_abajo_3[8] = {   // array con tercer cuadro de animacion de flecha
  B00100000,
  B01100000,
  B11000000,
  B11111100,
  B11111100,
  B11000000,
  B01100000,
  B00100000
};

byte flecha_abajo_4[8] = {   // array con cuarto cuadro de animacion de flecha
  B01000000,
  B11000000,
  B10000000,
  B11111001,
  B11111001,
  B10000000,
  B11000000,
  B01000000
};

byte flecha_abajo_5[8] = {   // array con cuarto cuadro de animacion de flecha
  B10000000,
  B10000000,
  B00000001,
  B11110011,
  B11110011,
  B00000001,
  B10000000,
  B10000000
};

byte flecha_abajo_6[8] = {   // array con cuarto cuadro de animacion de flecha
  B00000000,
  B00000001,
  B00000011,
  B11100111,
  B11100111,
  B00000011,
  B00000001,
  B00000000
};

byte flecha_abajo_7[8] = {   // array con cuarto cuadro de animacion de flecha
  B00000001,
  B00000011,
  B00000110,
  B11001111,
  B11001111,
  B00000110,
  B00000011,
  B00000001
};

byte flecha_abajo_8[8] = {   // array con cuarto cuadro de animacion de flecha
  B00000010,
  B00000110,
  B00001100,
  B10011111,
  B10011111,
  B00001100,
  B00000110,
  B00000010
};

byte flecha_abajo_9[8] = {   // array con cuarto cuadro de animacion de flecha
  B00000100,
  B00001100,
  B00011000,
  B00111111,
  B00111111,
  B00011000,
  B00001100,
  B00000100
};

// Flecha arriba
byte flecha_arriba_1[8] = {   // array con primer cuadro de animacion de flecha
  B00010000,
  B00011000,
  B00001100,
  B11111110,
  B11111110,
  B00001100,
  B00011000,
  B00010000};
byte flecha_arriba_2[8] = {   // array con segundo cuadro de animacion de flecha
  B00001000,
  B00001100,
  B00000110,
  B01111111,
  B01111111,
  B00000110,
  B00001100,
  B00001000};
byte flecha_arriba_3[8] = {   // array con tercer cuadro de animacion de flecha
  B00000100,
  B00000110,
  B00000011,
  B00111111,
  B00111111,
  B00000011,
  B00000110,
  B00000100};
byte flecha_arriba_4[8] = {   // array con cuarto cuadro de animacion de flecha
  B00000010,
  B00000011,
  B00000001,
  B10011111,
  B10011111,
  B00000001,
  B00000011,
  B00000010};
byte flecha_arriba_5[8] = {   // array con cuarto cuadro de animacion de flecha
  B00000001,
  B00000001,
  B10000000,
  B11001111,
  B11001111,
  B10000000,
  B00000001,
  B00000001};
byte flecha_arriba_6[8] = {   // array con cuarto cuadro de animacion de flecha
  B00000000,
  B10000000,
  B11000000,
  B11100111,
  B11100111,
  B11000000,
  B10000000,
  B00000000};
byte flecha_arriba_7[8] = {   // array con cuarto cuadro de animacion de flecha
  B10000000,
  B11000000,
  B01100000,
  B11110011,
  B11110011,
  B01100000,
  B11000000,
  B10000000};
byte flecha_arriba_8[8] = {   // array con cuarto cuadro de animacion de flecha
  B01000000,
  B01100000,
  B00110000,
  B11111001,
  B11111001,
  B00110000,
  B01100000,
  B01000000};
byte flecha_arriba_9[8] = {   // array con cuarto cuadro de animacion de flecha
  B00100000,
  B00110000,
  B00011000,
  B11111100,
  B11111100,
  B00011000,
  B00110000,
  B00100000};
  
// Igual
byte igual[8] = {   // array con cuarto cuadro de animacion de flecha
  B00001100,
  B00110000,
  B11000000,
  B00111000,
  B00111000,
  B11000000,
  B00110000,
  B00001100};

// SETUP
void setup() {
  lc.shutdown(0,false);     // enciende la matriz
  lc.setIntensity(0,4);     // establece brillo
  lc.clearDisplay(0);     // blanquea matriz
  Firmata.setFirmwareVersion( FIRMATA_MAJOR_VERSION, FIRMATA_MINOR_VERSION );
  Firmata.attach( STRING_DATA, stringDataCallback);
  Firmata.begin();  
}

void loop(){
  while ( Firmata.available() ) {
    Firmata.processInput();
  }
}

void stringDataCallback(char *stringData){
 if (*stringData == 'B'){
   mostrar_flecha_arriba();
 } else if (*stringData == 'S'){
   mostrar_flecha_abajo();
 } else if (*stringData == 'W'){
   mostrar_igual();
 }};

// FLECHA ABAJO
void mostrar_flecha_abajo(){
  mostrar_abajo_1();        // llama funcion mostrar_1
  delay(demora);      // demora
  mostrar_abajo_2();        // llama funcion mostrar_2
  delay(demora);      // demora
  mostrar_abajo_3();        // llama funcion mostrar_3
  delay(demora);      // demora
  mostrar_abajo_4();        // llama funcion mostrar_4
  delay(demora);      // demora
  mostrar_abajo_5();        // llama funcion mostrar_5
  delay(demora);      // demora
  mostrar_abajo_6();        // llama funcion mostrar_6
  delay(demora);      // demora
  mostrar_abajo_7();        // llama funcion mostrar_7
  delay(demora);      // demora
  mostrar_abajo_8();        // llama funcion mostrar_8
  delay(demora);      // demora
  mostrar_abajo_9();        // llama funcion mostrar_9
  delay(demora);      // demora
}

// FLECHA ARRIBA
void mostrar_flecha_arriba(){
  mostrar_arriba_1();        // llama funcion mostrar_1
  delay(demora);      // demora
  mostrar_arriba_2();        // llama funcion mostrar_2
  delay(demora);      // demora
  mostrar_arriba_3();        // llama funcion mostrar_3
  delay(demora);      // demora
  mostrar_arriba_4();        // llama funcion mostrar_4
  delay(demora);      // demora
  mostrar_arriba_5();        // llama funcion mostrar_5
  delay(demora);      // demora
  mostrar_arriba_6();        // llama funcion mostrar_6
  delay(demora);      // demora
  mostrar_arriba_7();        // llama funcion mostrar_7
  delay(demora);      // demora
  mostrar_arriba_8();        // llama funcion mostrar_8
  delay(demora);      // demora
  mostrar_arriba_9();        // llama funcion mostrar_9
  delay(demora);      // demora
}

// FUNCIONES FLECHA ABAJO
void mostrar_abajo_1(){     // funcion mostrar_1
  for (int i = 0; i < 8; i++)     // bucle itera 8 veces por el array
  {
    lc.setRow(0,i,flecha_abajo_1[i]);  // establece fila con valor de array flecha_abajo_1
  }}
void mostrar_abajo_2(){     // funcion mostrar_2
  for (int i = 0; i < 8; i++)     // bucle itera 8 veces por el array 
  {
    lc.setRow(0,i,flecha_abajo_2[i]);  // establece fila con valor de array flecha_abajo_2
  }}
void mostrar_abajo_3(){     // funcion mostrar_3
  for (int i = 0; i < 8; i++)     // bucle itera 8 veces por el array
  {
    lc.setRow(0,i,flecha_abajo_3[i]);  // establece fila con valor de array flecha_abajo_3
  }}
void mostrar_abajo_4(){     // funcion mostrar_4
  for (int i = 0; i < 8; i++)     // bucle itera 8 veces por el array 
  {
    lc.setRow(0,i,flecha_abajo_4[i]);  // establece fila con valor de array flecha_abajo_4
  }}
void mostrar_abajo_5(){     // funcion mostrar_5
  for (int i = 0; i < 8; i++)     // bucle itera 8 veces por el array 
  {
    lc.setRow(0,i,flecha_abajo_5[i]);  // establece fila con valor de array flecha_abajo_5
  }}
void mostrar_abajo_6(){     // funcion mostrar_6
  for (int i = 0; i < 8; i++)     // bucle itera 8 veces por el array 
  {
    lc.setRow(0,i,flecha_abajo_6[i]);  // establece fila con valor de array flecha_abajo_6
  }}
void mostrar_abajo_7(){     // funcion mostrar_7
  for (int i = 0; i < 8; i++)     // bucle itera 8 veces por el array 
  {
    lc.setRow(0,i,flecha_abajo_7[i]);  // establece fila con valor de array flecha_abajo_7
  }}
void mostrar_abajo_8(){     // funcion mostrar_8
  for (int i = 0; i < 8; i++)     // bucle itera 8 veces por el array 
  {
    lc.setRow(0,i,flecha_abajo_8[i]);  // establece fila con valor de array flecha_abajo_8
  }}
void mostrar_abajo_9(){     // funcion mostrar_9
  for (int i = 0; i < 8; i++)     // bucle itera 8 veces por el array 
  {
    lc.setRow(0,i,flecha_abajo_9[i]);  // establece fila con valor de array flecha_abajo_9
  }}

// FUNCIONES FLECHA ARRIBA
void mostrar_arriba_1(){     // funcion mostrar_1
  for (int i = 0; i < 8; i++)     // bucle itera 8 veces por el array
  {
    lc.setRow(0,i,flecha_arriba_1[i]);  // establece fila con valor de array flecha_abajo_1
  }}
void mostrar_arriba_2(){     // funcion mostrar_2
  for (int i = 0; i < 8; i++)     // bucle itera 8 veces por el array 
  {
    lc.setRow(0,i,flecha_arriba_2[i]);  // establece fila con valor de array flecha_abajo_2
  }}
void mostrar_arriba_3(){     // funcion mostrar_3
  for (int i = 0; i < 8; i++)     // bucle itera 8 veces por el array
  {
    lc.setRow(0,i,flecha_arriba_3[i]);  // establece fila con valor de array flecha_abajo_3
  }}
void mostrar_arriba_4(){     // funcion mostrar_4
  for (int i = 0; i < 8; i++)     // bucle itera 8 veces por el array 
  {
    lc.setRow(0,i,flecha_arriba_4[i]);  // establece fila con valor de array flecha_abajo_4
  }}
void mostrar_arriba_5(){     // funcion mostrar_5
  for (int i = 0; i < 8; i++)     // bucle itera 8 veces por el array 
  {
    lc.setRow(0,i,flecha_arriba_5[i]);  // establece fila con valor de array flecha_abajo_5
  }}
void mostrar_arriba_6(){     // funcion mostrar_6
  for (int i = 0; i < 8; i++)     // bucle itera 8 veces por el array 
  {
    lc.setRow(0,i,flecha_arriba_6[i]);  // establece fila con valor de array flecha_abajo_6
  }}
void mostrar_arriba_7(){     // funcion mostrar_7
  for (int i = 0; i < 8; i++)     // bucle itera 8 veces por el array 
  {
    lc.setRow(0,i,flecha_arriba_7[i]);  // establece fila con valor de array flecha_abajo_7
  }}
void mostrar_arriba_8(){     // funcion mostrar_8
  for (int i = 0; i < 8; i++)     // bucle itera 8 veces por el array 
  {
    lc.setRow(0,i,flecha_arriba_8[i]);  // establece fila con valor de array flecha_abajo_8
  }}
void mostrar_arriba_9(){     // funcion mostrar_9
  for (int i = 0; i < 8; i++)     // bucle itera 8 veces por el array 
  {
    lc.setRow(0,i,flecha_arriba_9[i]);  // establece fila con valor de array flecha_abajo_9
  }}

// Mostrar igual
void mostrar_igual(){     // funcion mostrar_9
  for (int i = 0; i < 8; i++)     // bucle itera 8 veces por el array 
  {
    lc.setRow(0,i,igual[i]);  // establece fila con valor de array flecha_abajo_9
  }}
